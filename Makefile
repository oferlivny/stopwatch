all: 	test_stopwatch
PHONY: test_stopwatch

CFLAGS := -O2 -g

test_stopwatch: stopwatch.h stopwatch.cpp test_stopwatch.cpp
	g++ -std=c++11 test_stopwatch.cpp stopwatch.cpp -o test_stopwatch $(CFLAGS)


clean:
	rm test_stopwatch

