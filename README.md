BloomSearch
===========
An example of using a Bloom filter to provide substring searching.

I wrote up a walkthrough of the code [here](https://borgernet.com/2015/01/05/SubstringSearching.html).

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
Names can be inserted individually by using the `insert` program. One name per line.

	$> ./insert

You can also utilize a list of sample names.

	$> cat ../sampleNames.txt | ./insert

Search Database
---------------
Search by string using LIKE operator.

	$> ./searchName <term>

Search by Bloom filter using bitwise AND operator.

	$> ./searchBloom <term>
