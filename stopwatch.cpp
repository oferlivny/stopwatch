#include <sys/time.h>

#include <string>
#include <map>
#include <vector>
#include <assert.h>
#include <sstream>
#include <numeric> // accumulate

#include <time.h>
#include <iostream>

#include "stopwatch.h"

#define TimeVal StopWatch::TimeVal

void StopWatch::clear() {
	pending.clear();
	reports.clear();
}

uint64_t subtract(TimeVal a, TimeVal b) {
	// returns a-b
	  /* Perform the carry for the later subtraction by updating y. */
	TimeVal tempb=b;
	  if (a.tv_usec < tempb.tv_usec) {
		      int nsec = (tempb.tv_usec - a.tv_usec) / 1000000 + 1;
		          tempb.tv_usec -= 1000000 * nsec;
			      tempb.tv_sec += nsec;
			        }
	    if (a.tv_usec - tempb.tv_usec > 1000000) {
		        int nsec = (a.tv_usec - tempb.tv_usec) / 1000000;
			    tempb.tv_usec += 1000000 * nsec;
			        tempb.tv_sec -= nsec;
				  }

	      /* Compute the time remaining to wait.
	       *      tv_usec is certainly positive. */
	    TimeVal res;
	      res.tv_sec = a.tv_sec - tempb.tv_sec;
	        res.tv_usec = a.tv_usec - tempb.tv_usec;

		  /* Return 1 if result is negative. */
		uint64_t dt = res.tv_sec * 1000 + res.tv_usec / 1000;
		return dt;
}

uint64_t StopWatch::deltaSince(const TimeVal &t) {
	TimeVal now;
	setToNow(now);
	uint64_t dt = subtract(now,t);
	return dt;
};

void StopWatch::setToNow(TimeVal &t) {
	int res = GETTIMEFUNC(&t);
	assert(res==0);
};

void StopWatch::start(const std::string &tag) {
	assert(pending.find(tag)==pending.end());
	setToNow(pending[tag]);
}

void StopWatch::stop(const std::string &tag) {
       assert(pending.find(tag)!=pending.end());
       uint64_t dt = deltaSince(pending[tag]);
	reports[tag].push_back(dt);
	pending.erase(tag);
};

uint64_t StopWatch::getAverage(const std::string &tag) {
	assert(reports.find(tag)!=reports.end());
	ReportsVec &v=reports[tag];
	int count = v.size();
	uint64_t avg = std::accumulate(v.begin(),v.end(), 0) / count;
	return avg;
}

std::string StopWatch::report(const std::string &tag) {
	assert(reports.find(tag)!=reports.end());
	std::stringstream str;
	ReportsVec &v=reports[tag];
	int count = v.size();
	str << "Tag " << tag << " average " << getAverage(tag) << "ms count " << count;
	return str.str();
}
