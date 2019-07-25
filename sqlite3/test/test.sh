#!/bin/bash
uname -sr
cat /proc/cpuinfo | grep "cpu MHz"
echo ----- 10000 in memory ----
./test ":memory:" 0 1 10000
./test ":memory:" 1 1 10000
./test ":memory:" 0 0 10000
./test ":memory:" 1 0 10000
echo ---- 100000 in memory ----
./test ":memory:" 0 1 100000
./test ":memory:" 1 1 100000
./test ":memory:" 0 0 100000
./test ":memory:" 1 0 100000
echo ---- 200000 in memory ----
./test ":memory:" 0 1 200000
./test ":memory:" 1 1 200000
./test ":memory:" 0 0 200000
./test ":memory:" 1 0 200000
echo --- 1000000 in memory ----
./test ":memory:" 0 1 1000000
./test ":memory:" 1 1 1000000

echo " "
echo " "
echo ------ 1000 in disk ----
rm test.db
./test "test.db" 0 1 1000
rm "test.db"
./test "test.db" 1 1 1000
rm "test.db"
./test "test.db" 0 0 1000
rm "test.db"
./test "test.db" 1 0 1000
rm "test.db"
echo ------ 2000 in disk ----
./test "test.db" 0 1 2000
rm "test.db"
./test "test.db" 1 1 2000
rm "test.db"
./test "test.db" 0 0 2000
rm "test.db"
./test "test.db" 1 0 2000
rm "test.db"

echo ----- 10000 in disk ----
./test "test.db" 0 1 10000
rm "test.db"
./test "test.db" 1 1 10000
rm "test.db"
echo ---- 100000 in disk ----
./test "test.db" 0 1 100000
rm "test.db"
./test "test.db" 1 1 100000
rm "test.db"
echo --- 1000000 in disk ----
./test "test.db" 0 1 1000000
rm "test.db"
./test "test.db" 1 1 1000000
rm "test.db"

