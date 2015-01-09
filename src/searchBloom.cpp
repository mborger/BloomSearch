#include <iostream>
#include <pqxx/pqxx>
#include <string>
#include "util.h"

using namespace pqxx;

int
main(int argc, char* argv[])
{
	if(argc != 2) {
		std::cerr << "Usage: " << argv[0] << " SEARCH_TERM" << std::endl;
	}

	const std::string searchTerm {argv[1]};
	const auto searchTermBloom = generateBloom(searchTerm);

	connection conn; // defaults to dbname=<username>
	read_transaction txn(conn, "Select transaction");

	result r = txn.exec("SELECT * FROM users WHERE "
			"first_bloom & b'" + searchTermBloom.to_string() + "' = b'" + searchTermBloom.to_string() + "' OR "
			"last_bloom & b'"  + searchTermBloom.to_string() + "' = b'" + searchTermBloom.to_string() + "'"
			);

	for(auto row : r) {
		std::cout
			<< row["first"] << "\t"
			<< row["last"]
			<< std::endl;
	}

	return 0;
}
