#include <algorithm>
#include <cctype>
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
	std::string lowerSearchTerm;
	lowerSearchTerm.resize(searchTerm.length());
	std::transform(searchTerm.begin(), searchTerm.end(), lowerSearchTerm.begin(), ::tolower);

	connection conn; // defaults to dbname=<username>
	read_transaction txn(conn, "Select transaction");

	result r = txn.exec("SELECT * FROM users WHERE "
			"lower(first) LIKE '%" + lowerSearchTerm + "%' OR "
			"lower(last) LIKE '%"  + lowerSearchTerm + "%'"
			);

	for(auto row : r) {
		std::cout
			<< row["first"] << "\t"
			<< row["last"]
			<< std::endl;
	}

	return 0;
}
