#include<iostream>
#include<chrono>
using namespace std;

/*  Introduce to <chrono>
 *  -- A precision-neutral library for time and date
 *  
 *  Clock:
 *      std::chrono::system_clock: current time according to the system - is not steady
 *      std::chrono::steady_clock: goes at a uniform rate
 *      std::chrono:high_resolution_clock: provides smallest possible tick period.
 * 
 *  duration:
 *      std::chrono::duration<>: represents time duration
 *          2 hours (a number and a unit)
 *      duration<int, ratio<1, 1>>  //number of seconds stored in a int
 *      duration<double, ratio<60, 1>> //number of minutes stored in a double
 *       other predefined duration types: nanoseconds, microseconds, milliseconds, seconds, minutes, hours
 *      system_clock::duration  --  duration<T, system_clock::period>
 *  
 *  time_point
 *      std::chrono::time_point<>: represents a point of time
 *          00:00  January 1, 1970 (Corordinated Universal Time - UTC)  -- epoch of a clock
 *      time_point<system_clock, milliseconds>: according to system_clock, the elapsed time since epoch in milliseconds
 * 
 *      system_clock::time_point -- time_point<system_clock, system_clock::duration>
 *      steady_clock::time_point -- time_point<steady_clock, steady_clock::duration>
 *  
 */

int main()
{
    std::ratio<1, 10> r;  //  1/10
    cout << r.num << "\\" << r.den << endl;

    cout << chrono::system_clock::period::num << "\\" << chrono::system_clock::period::den << endl;

    chrono::microseconds mi(2700);   // 2700 microseconds
    cout << mi.count() << endl;  //2700
    chrono::nanoseconds na = mi;     // 2700000 nanoseconds  lower resolution to higher resolution (don't need duration_cast) 
    cout << na.count() << endl;  //2700000
    chrono::milliseconds mill = chrono::duration_cast<chrono::milliseconds>(mi);  //2 milliseconds  higher resolution to lower resolution(need duration_cast)
    cout << mill.count() << endl;
    mi = mill + mi;  //2000 + 2700 = 4700;
    cout << mi.count() << endl;


    chrono::system_clock::time_point tp = chrono::system_clock::now();  //current time of system clock
    cout << tp.time_since_epoch().count() << endl;
    tp = tp + chrono::seconds(2);
    cout << tp.time_since_epoch().count() << endl;

    chrono::steady_clock::time_point start = chrono::steady_clock::now();
    cout << "I am bored" << endl;
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    chrono::steady_clock::duration d = end - start;
    if(d == chrono::steady_clock::duration::zero())
        cout << "no time elapsed" << endl;
    cout << chrono::duration_cast<chrono::microseconds>(d).count() << endl;


    return 0;
}