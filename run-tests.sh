#!/bin/bash

mysql -uroot < tests/testdb-struct.sql

hhvm `which phpunit` --bootstrap tests/bootstrap.php tests

