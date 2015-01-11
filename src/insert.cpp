#include <iostream>
#include <pqxx/pqxx>
#include <string>
#include "util.h"

using namespace pqxx;

int
main(int argc, char* argv[])
{
	connection conn; // defaults to dbname=<username>
	work txn(conn, "Insert transaction");

	while(std::cin.good()) {
		std::string firstName, lastName;
		std::cin >> firstName >> lastName;

		const auto firstNameBloom = generateBloom(firstName);
		const auto lastNameBloom = generateBloom(lastName);

		txn.exec("INSERT INTO users(first,first_bloom,last,last_bloom) VALUES("
				"'"  + firstName                  + "',"
				"b'" + firstNameBloom.to_string() + "',"
				"'"  + lastName                   + "',"
				"b'" + lastNameBloom.to_string()  + "'"
				")");
	}

	txn.commit();

	return 0;
}
