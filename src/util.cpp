#include <algorithm>
#include <cctype>
#include "util.h"
#include <cmath>
#include <cstring>
#include "hash/fastfnv64a.h"
#include "hash/MurmurHash3.h"
#include "hash/SpookyV2.h"

int
summationSeries(const int n)
{
	return static_cast<int>((std::pow(n, 2) + n) / 2);
}

std::vector<std::string>
listSubStrings(const std::string str)
{
	const size_t vectorLength = summationSeries(str.length());
	std::vector<std::string> result;
	result.reserve(vectorLength);
	for(size_t i = 0; i < str.length(); i++) {
		for(size_t j = 1; j <= str.length()-i; j++) {
			result.push_back(str.substr(i,j));
		}
	}
	return result;
}

std::bitset<BLOOM_SIZE>
generateBloom(const std::string str)
{
	std::bitset<BLOOM_SIZE> bloom;

	// Arbitrarily chosen seed value
	const int seed {42};

	// Transform the string to lower case
	std::string lowerStr;
	lowerStr.resize(str.length());
	std::transform(str.begin(), str.end(), lowerStr.begin(), ::tolower);

	for(const auto subStr : listSubStrings(lowerStr)) {
		unsigned int murmurHash;
		MurmurHash3_x86_32(subStr.c_str(), subStr.length(), seed, &murmurHash);
		bloom.set(murmurHash % BLOOM_SIZE);

		unsigned int spookyHash = SpookyHash::Hash32(subStr.c_str(), subStr.length(), seed);
		bloom.set(spookyHash % BLOOM_SIZE);

		char* buf = (char*) calloc(subStr.length(), sizeof(char));
		std::strncpy(buf, subStr.c_str(), subStr.length());
		unsigned long long fnvHash = fnv64a(reinterpret_cast<unsigned char*>(buf), (uint64_t)subStr.length());
		bloom.set(fnvHash % BLOOM_SIZE);
		delete buf;
	}

	return bloom;
}
