#include <iostream>
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

	return 0;
}
