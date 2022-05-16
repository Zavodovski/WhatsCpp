#include<iostream>
#include<string>
#include<thread>
#include<mutex>
#include<fstream>
using namespace std;

std::mutex mu;

void shared_print(string msg, int id)
{
    std::lock_guard<std::mutex> guard(mu);  //RAII
    //mu.lock();
    cout << msg << id << endl; //if an exception was throwed, mui will end up being locked forever, so it's bad
                               //thus it's not recommended to use lock and unlock function directly
                               //cout is not completely under the protection of the mutex mu, because cout is a global variable so other thread can still access cout directly without going through lock
    //mu.unlock();
}




//a more realistic example(protect the resource completely)
class LogFile
{
    std::mutex m_mutex;
    ofstream f;
public:
    LogFile()
    {
        f.open("log.txt");
    }//need destructor to close file
    void shared_print(string id, int value)
    {
        std::lock_guard<mutex> locker(m_mutex);
        f << "From: " << id << ": " << value << endl;
    }
    //should never return f to the outside world
    //ofstream& getStream() { return f;}
    //should never pass f as an argument to user provided function
    // void processf(void fun(ofstream&)){ fun(f)}
};

void function_1(LogFile& log)
{
    for(int i = 0; i > -100; i --)
        log.shared_print(string("From t1: "), i);
}

/*
class stack
{
    int* _data;
    std::mutex _mu;
public:
    int& pop();  //pops off the item on top of the stack
    int& top();  //returns the item on top
    //...
};

void function_1(stack& st)
{
    int v = st.pop();
    //st.pop();
    //process(v);
}
*/

/*
 *  Avoiding Data Race:
 *  1. Use mutex to synchronize data to access
 *  2. never leak a handle of data to outside
 *  3. Design interface appropriately 
 */


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