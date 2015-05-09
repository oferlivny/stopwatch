#include "stopwatch.h"
#include <unistd.h>
#include <iostream>
using std::cout;
#define TimeVal StopWatch::TimeVal

#define swassert(X) \
	if (!(X)) { \
		std::cout << "Test " << #X << " failed!" << std::endl; \
	}

// Basic test structure
class TestHelper {
	public:
	TestHelper(int s, int i, std::string t): sleep(s),iter(i),tag(t){};
	int sleep;
	int iter;
	std::string tag;
};

// Simple iterate
void testBase(int usleep_ms, int iterations, std::string &tag) {
	for (int i=0;i<iterations;i++) {
		SW_START(tag);
		usleep(usleep_ms*1000);
		SW_STOP(tag);
	}
}

#define MIN(x,y) ((x)>(y)) ? (y) : (x) 
#define MAX(x,y) ((y)>(x)) ? (y) : (x)

// Helper for assertions
bool check_helper(TestHelper h) {
#if ( _OPTIMIZE_ == 0) 
	double allowed_perc = 0.02;
	uint64_t allowed_ms = 10;
#else 
	double allowed_perc = 0.01;
	uint64_t allowed_ms = 1;
#endif
	uint64_t dt = STOPWATCH.getAverage(h.tag);
	uint64_t low_boundary = MIN ( h.sleep - allowed_perc * h.sleep, h.sleep - allowed_ms );
	uint64_t high_boundary = MAX ( h.sleep + allowed_perc * h.sleep, h.sleep + allowed_ms );
	bool res = (dt <= high_boundary && dt >= low_boundary);
	if (!res) 
		std::cout << "Warning. Expected " << h.sleep << " but got " << dt << std::endl;
	return res;
}

// Simple test for basic usecase
void testA(int usleep_ms, int iterations) {
	SW_CLEAR;
	std::string tag = "Test";
	testBase(usleep_ms,iterations,tag);
	swassert(check_helper(TestHelper(usleep_ms,iterations,tag)));
};


void testB(std::vector<TestHelper> tests) {
	SW_CLEAR;
	SW_START("testB");
	for (size_t i=0; i<tests.size(); i++) {
		testBase(tests[i].sleep, tests[i].iter, tests[i].tag);
	}
	for (size_t i=0; i<tests.size(); i++) {
		swassert(check_helper(tests[i]));
	}
	SW_STOP("testB");
	std::cout << SW_STR_REPORT << std::endl;
};

int main() {
	std::cout << "TestA" << std::endl;
	testA(200,10);

	std::vector<TestHelper> tests = { { 10, 100, "Ten" } , { 100, 20, "Houndred" } , { 1000, 3, "Thousand" }};
	std::cout << "TestB" << std::endl;
	testB(tests);
	
	std::cout << "Done";
	return 0;
}
