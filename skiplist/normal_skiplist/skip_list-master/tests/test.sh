echo "Running unit tests..."
g++ -g test_random_access_equ.cpp -I. -I.. && ./a.out && echo "Tests passed"

#echo "Running benchmarks..."
#g++ benchmark.cpp -I.. -I. -DBENCHMARK_WITH_MAIN && ./a.out; rm a.out
