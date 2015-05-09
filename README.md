# stopwatch
cpp runtime performance measurement helper.
it is not thread safe. yet.


Usage:

1. include the header file: #include "stopwatch.h"
2. add the cpp file to your project (stopwatch.cpp)
3. profile your code:

StopWatch sw;

void small_function() {
 g_sw.start("small_function");
 // some code
 g_sw.stop("small_function");
}
void big_function() {
 g_sw.start("big_function_first_part");
 // some code
 for (int i=0;i<100;i++) small_function();
 // some code
 g_sw.stop("big_function_first_part");
 g_sw.start("big_function_second_part");
 // some code
 g_sw.stop("big_function_second_part");
}
int main() {
 g_sw.start("main");
 for (int i=0;i<10;i++) big_function();
 g_sw.stop("main");
 cout << g_sw.getReport("main"); << endl;
 // cout << g_sw.getAllReports() << endl;
 
}

