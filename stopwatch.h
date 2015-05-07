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

class StopWatch {
	typedef std::vector<uint64_t> ReportsVec;

	public:
	// This is for Posix. Can make it faster by using non-posix methods...
	typedef struct timeval TimeVal;
	#define GETTIMEFUNC(ptr) gettimeofday(ptr,NULL);

	void expect(const std::string &tag, int howmanytimes);
	void start(const std::string &tag);
	void stop(const std::string &tag);
	void clear();	

	uint64_t getAverage(const std::string &tag);
	std::string report(const std::string &tag);

	private:
	uint64_t deltaSince(const TimeVal &t);
	void setToNow(TimeVal &t);

	std::map<std::string,TimeVal> pending;
	std::map<std::string,ReportsVec > reports;


};
#endif // _STOPWATCH_H_
