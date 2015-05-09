# stopwatch
cpp threadsafe runtime performance measurement helper.

(because sometimes statistics are just not enough...)

###Usage:

1. Include the header file: #include "stopwatch.h"
2. Add the cpp file to your project (stopwatch.cpp)
3. Profile your code by calling **SW_START(tag)** and **SW_STOP(tag)** before and after your code
4. Call **SW_STR_REPORT_ALL** to get a string with formatted report of your code runtime

###Example:
``` 
#include "stopwatch.h"

void small_function() {
 SW_START("small_function");
 // some code
 SW_STOP("small_function");
}
void big_function() {
 SW_START("big_function_first_part");
 // some code
 for (int i=0;i<100;i++) small_function();
 // some code
 SW_STOP("big_function_first_part");
 SW_START("big_function_second_part");
 // some code
 SW_STOP("big_function_second_part");
}
int main() {
 SW_START("main");
 for (int i=0;i<10;i++) big_function();
 SW_STOP("main");
 cout << SW_STR_REPORT("main"); << endl;
 cout << SW_STR_REPORT_ALL << endl;
}
``` 

### Output example:
```
0x7fff7ac92300                   TestWrapper (         1x) :      6077 ms (100%-100%)
0x7fff7ac92300                expecting100ms (        20x) :       100 ms (100%-104%)
0x7fff7ac92300                 expecting10ms (       100x) :        10 ms (100%-120%)
0x7fff7ac92300              expencting1000ms (         3x) :      1001 ms (100%-100%)
```
