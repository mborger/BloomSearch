#include "util.h"
#include <cmath>
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

	unsigned int murmurHash;
	MurmurHash3_x86_32(str.c_str(), str.length(), 0, &murmurHash);
	bloom.set(murmurHash % BLOOM_SIZE);

	unsigned int spookyHash = SpookyHash::Hash32(str.c_str(), str.length(), 0);
	bloom.set(spookyHash & BLOOM_SIZE);

	return bloom;
}
