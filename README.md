BloomSearch
===========

An example of using a bloom filter to provide string searching.

Setup Database
--------------
	$> sudo -u postgres createdb -O <username> <username>

Build Code
----------
	$> mdkir build && cd build
	$> cmake ..
	$> make

Populate Database
-----------------
	$> while read l; do ./insert $l; done < ../sampleNames.csv

Search Database
---------------
	$> ./search <term>
