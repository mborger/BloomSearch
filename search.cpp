#include <iostream>
#include "MurmurHash3.h"
#include <pqxx/pqxx>
#include "util.h"

using namespace pqxx;

int
main(int argc, char* argv[])
{
	connection conn; // defaults to dbname=<username>
	read_transaction txn(conn, "Select transaction");

	result r = txn.exec("SELECT * FROM users");

	for(auto row : r) {
		std::cout
			<< row["first"] << "\t"
			<< row["last"] << "\t"
			<< row["bloom"]
			<< std::endl;
	}

	auto subStrings = listSubStrings("dog");
	for(auto s : subStrings) {
		unsigned int hash;
		std::bitset<256> filter;
		MurmurHash3_x86_32(s.c_str(), s.length(), 0, &hash);
		filter.set(hash % 256);
		//std::cout << s << "\t" << filter << std::endl;
	}

	return 0;
}
