BloomSearch
===========
An example of using a bloom filter to provide string searching. This example uses PostgreSQL since it has a nice bit field data type to work with.

Setup Database
--------------
	$> sudo -u postgres createuser -DRS <username>
	$> sudo -u postgres createdb -O <username> <username>
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
	$> ./search <term>
