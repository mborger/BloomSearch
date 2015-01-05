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

	// I'm purposely setting the seeds to 0
	const int seed {0};

	unsigned int murmurHash;
	MurmurHash3_x86_32(str.c_str(), str.length(), seed, &murmurHash);
	bloom.set(murmurHash % BLOOM_SIZE);

	unsigned int spookyHash = SpookyHash::Hash32(str.c_str(), str.length(), seed);
	bloom.set(spookyHash % BLOOM_SIZE);

	char* buf = (char*) calloc(str.length(), sizeof(char));
	std::strncpy(buf, str.c_str(), str.length());
	unsigned long long fnvHash = fnv64a(reinterpret_cast<unsigned char*>(buf), (uint64_t)str.length());
	bloom.set(fnvHash % BLOOM_SIZE);

	return bloom;
}
