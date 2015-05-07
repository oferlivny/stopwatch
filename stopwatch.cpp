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

void StopWatch::clear() {
	pending.clear();
	reports.clear();
}

Delta subtract(TimeVal a, TimeVal b) {
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
		Delta dt = res.tv_sec * 1000 + res.tv_usec / 1000;
		return dt;
}

Delta StopWatch::deltaSince(const TimeVal &t) {
	TimeVal now;
	setToNow(now);
	Delta dt = subtract(now,t);
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
       Delta dt = deltaSince(pending[tag]);
	reports[tag].push_back(dt);
	pending.erase(tag);
};

Delta StopWatch::getAverage(const std::string &tag) {
	assert(reports.find(tag)!=reports.end());
	ReportsVec &v=reports[tag];
	int count = v.size();
	Delta avg = std::accumulate(v.begin(),v.end(), 0) / count;
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
