#ifndef _STOPWATCH_H_
#define _STOPWATCH_H_

#include <sys/time.h>

#include <string>
#include <map>
#include <vector>
#include <assert.h>
#include <sstream>
#include <numeric> // accumulate

#include <time.h>
#include <iostream>

// Class accessor
#define STOPWATCH (*StopWatch::Instance())
// Clear all saved values
#define SW_CLEAR STOPWATCH.clear()
// Start measurement
#define SW_START(x) STOPWATCH.start(x)
// Stop measurement
#define SW_STOP(x) STOPWATCH.stop(x)
// Return a string full of reports
#define SW_STR_REPORT_ALL STOPWATCH.reportAll()
// Return a string of specific report
#define SW_STR_REPORT(x) STOPWATCH.report(x)

class StopWatch{
	typedef struct _Report {
		uint64_t sum;
		uint64_t count;
	} Report;


	public:
	// This is for Posix. Can make it faster by using non-posix methods...
	typedef struct timeval TimeVal;
	#define GETTIMEFUNC(ptr) gettimeofday(ptr,NULL);

	// Singleton accessor
	static StopWatch *Instance() {
		static __thread StopWatch sw;
		return &sw;
	}


	void expect(const std::string &tag, int howmanytimes);
	void start(const std::string &tag);
	void stop(const std::string &tag);
	void clear();	

	uint64_t getAverage(const std::string &tag);
	std::string report(const std::string &tag);
	std::string reportAll();

	private:
	StopWatch(){};
	uint64_t deltaSince(const TimeVal &t);
	void setToNow(TimeVal &t);

	std::map<std::string, TimeVal> pending;
	std::map<std::string, Report > reports;


};


#define FuncStopWatch StopWatchNow(__func__)

class StopWatchNow {
	std::string tag;
	StopWatchNow(const std::string &t):tag(t) {
		SW_START(tag);
	}
	~StopWatchNow() {
		SW_STOP(tag);
	};
};
#endif // _STOPWATCH_H_
