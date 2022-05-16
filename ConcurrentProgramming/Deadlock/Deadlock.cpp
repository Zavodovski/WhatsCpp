#include<iostream>
#include<string>
#include<thread>
#include<mutex>
#include<fstream>
using namespace std;

std::mutex mu;

/*
 *  Avoiding deadlock
 *  1. Prefer locking single mutex
 *  2. Avoid locking a mutex and then calling a user provided function
 *  3. Use std::lock() to lock more than one mutex
 *  4. lock the mutex in same order
 * 
 */

/*
 *  Locking Granularity
 *  Fine-grained lock: protects small amout of data
 *      program becomes tricky and more exposed to deadlocks
 *  coarse-grained lock: protects big amout of data
 *      losing big opportunity of parallel computing because many threads will spend a lot of time waiting for the resources
 */

class LogFile
{
    std::mutex m_mutex;
    std::mutex m_mutex2;
    ofstream f;
public:
    LogFile()
    {
        f.open("log.txt");
    }//need destructor to close file
    void shared_print(string id, int value)
    {
        // std::lock_guard<mutex> locker(m_mutex);
        // std::lock_guard<mutex> locker2(m_mutex2);
        
        std::lock(m_mutex, m_mutex2);  //std::lock can lock arbitrary number of lockable objects such as mutex using certain deadlock avoidance algorithm
        std::lock_guard<mutex> locker(m_mutex, std::adopt_lock);  //std::adopt_lock adopy to the ownership of that mutex
        std::lock_guard<mutex> locker2(m_mutex2, std::adopt_lock);
        cout << "From: " << id << ": " << value << endl;
    }

    void shared_print2(string id, int value)
    {
        //std::lock_guard<mutex> locker2(m_mutex2);
        //std::lock_guard<mutex> locker(m_mutex);    
            //to avoid deadlock, make sure lock the mutexes in the same order
        //std::lock_guard<mutex> locker2(m_mutex2);


        std::lock(m_mutex, m_mutex2);  //std::lock can lock arbitrary number of lockable objects such as mutex using certain deadlock avoidance algorithm
        std::lock_guard<mutex> locker(m_mutex, std::adopt_lock);  //std::adopt_lock adopy to the ownership of that mutex
        std::lock_guard<mutex> locker2(m_mutex2, std::adopt_lock);

        cout << "From: " << id << ": " << value << endl;
    }
};

void function_1(LogFile& log)
{
    for(int i = 0; i > -100; i --)
        log.shared_print2(string("From t1: "), i);
}




int main()
{
    LogFile log;
    std::thread t1(function_1, std::ref(log));
    
    
    //std::thread t1(function_1);

    for(int i = 0; i < 100; i ++)
        log.shared_print(string("From main: "), i);
    t1.join();

    return 0;
}