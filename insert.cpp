#include <iostream>
#include <pqxx/pqxx>
#include <string>
#include "util.h"

using namespace pqxx;

int
main(int argc, char* argv[])
{
	if(argc != 3) {
		std::cerr << "Usage: " << argv[0] << " FIRST_NAME LAST_NAME" << std::endl;
	}

	const std::string firstName {argv[1]};
	const std::string lastName {argv[2]};

	std::bitset<BLOOM_SIZE> firstNameBloom, lastNameBloom;
	for(const auto substr : listSubStrings(firstName)) {
		firstNameBloom |= generateBloom(substr);
	}
	for(const auto substr : listSubStrings(lastName)) {
		lastNameBloom |= generateBloom(substr);
	}

	connection conn; // defaults to dbname=<username>
	work txn(conn, "Insert transaction");

	txn.exec("INSERT INTO users(first,first_bloom,last,last_bloom) VALUES("
			"'" + firstName + "',"
			"b'" + firstNameBloom.to_string() + "',"
			"'" + lastName + "',"
			"b'" + lastNameBloom.to_string() + "'"
			")");
	txn.commit();

	return 0;
}
