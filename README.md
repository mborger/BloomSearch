BloomSearch
===========
An example of using a bloom filter to provide string searching.

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
	$> while read line; do ./insert $line; done < ../sampleNames.csv

Search Database
---------------
	$> ./search <term>
