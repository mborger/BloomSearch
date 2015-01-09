BloomSearch
===========
An example of using a Bloom filter to provide substring searching.

Requirements
------------
* A C++11 compliant compiler
* CMake
* PostgreSQL
* Libpqxx

Setup Database
--------------
	$> sudo -u postgres createuser -DRS $USER
	$> sudo -u postgres createdb -O $USER
	$> psql
	=> create table users(first varchar(50), first_bloom bit(256), last varchar(50), last_bloom bit(256));

Build Code
----------
	$> mdkir build && cd build
	$> cmake ..
	$> make

Populate Database
-----------------
Names can be inserted individually by using the `insert` program.

	$> ./insert FIRST_NAME LAST_NAME

You can also utilize a list of sample names.

	$> while read line; do ./insert $line; done < ../sampleNames.txt

Search Database
---------------
Search by string using LIKE operator.

	$> ./searchName <term>

Search by Bloom filter using bitwise AND operator.

	$> ./searchBloom <term>
