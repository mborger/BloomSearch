#pragma once

#include <bitset>
#include <string>
#include <vector>

#define BLOOM_SIZE 256

int summationSeries(const int n);
std::vector<std::string> listSubStrings(const std::string str);
std::bitset<BLOOM_SIZE> generateBloom(const std::string str);
