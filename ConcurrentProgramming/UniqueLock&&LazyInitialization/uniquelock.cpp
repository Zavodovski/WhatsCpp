#include<iostream>
#include<string>
#include<thread>
#include<mutex>
#include<fstream>
using namespace std;

std::mutex mu;


class LogFile
{
    std::mutex _mu;
    ofstream _f;
public:
    LogFile()
    {
        _f.open("log.txt");
    }//need destructor to close file
    void shared_print(string id, int value)
    {
        //std::lock_guard<mutex> locker(_mu);
        //std::unique_lock<mutex> locker(_mu);

        std::unique_lock<mutex> locker(_mu, std::defer_lock);
            //both lock_guard and unique_lock cannot be copied
        //do something else
        
        locker.lock();
        _f << "From: " << id << ": " << value << endl;
        locker.unlock();
        //...do other things

        locker.lock();  //lock the mutex again

        std::unique_lock<mutex> locker2 = std::move(locker); //move the ownership of mutex from locker to locker2
            //Note: lock_guard can never be moved
    }

};


//Lazy initialization
class LogFile
{
    std::mutex _mu;
    std::mutex _mu_open;
    ofstream _f;
public:
    LogFile() { }
    void shared_print(string id, int value)
    {

        {
            std::unique_lock<mutex> locker2(_mu_open);
            if(!_f.is_open())
            {
                _f.open("log.text");
            }
        }        
        std::unique_lock<mutex> locker(_mu, std::defer_lock);
        _f << "From " << id <<  ": " << value << endl;

    }
};



class LogFile
{
    std::mutex _mu;
    std::once_flag _flag;
    ofstream _f;
public:
    LogFile() { }
    void shared_print(string id, int value)
    {

        // {
        //     std::unique_lock<mutex> locker2(_mu_open);
        //     if(!_f.is_open())
        //     {
        //         _f.open("log.text");
        //     }
        // }        

        std::call_once(_flag, [&](){ _f.open("log.txt");});  //file will be opened only once by one thread

        std::unique_lock<mutex> locker(_mu, std::defer_lock);
        _f << "From " << id <<  ": " << value << endl;

    }
};



