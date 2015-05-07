#include <sys/time.h>

#include <string>
#include <map>
#include <vector>
#include <assert.h>
#include <sstream>
#include <numeric> // accumulate

#include <time.h>
#include <iostream>

#define POSIX
//#define LINUX

#ifdef LINUX
typedef struct timespec TimeVal;
#define GETTIMEFUNC(ptr) clock_gettime(CLOCK_THREAD_CPUTIME_ID,ptr);
#endif

#ifdef POSIX
typedef struct timeval TimeVal;
#define GETTIMEFUNC(ptr) gettimeofday(ptr,NULL);
#endif

typedef double Perc;
typedef uint64_t Delta;
typedef std::vector<Delta> ReportsVec;

class StopWatch {
	public:
	void expect(const std::string &tag, int howmanytimes);
	void start(const std::string &tag);
	void stop(const std::string &tag);
	void clear();	

	Delta getAverage(const std::string &tag);
	std::string report(const std::string &tag);

	private:
	Delta deltaSince(const TimeVal &t);
	void setToNow(TimeVal &t);

	std::map<std::string,TimeVal> pending;
	std::map<std::string,ReportsVec > reports;
};

