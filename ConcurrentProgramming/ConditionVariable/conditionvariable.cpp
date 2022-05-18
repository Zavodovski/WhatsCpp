#include<iostream>
#include<deque>
#include<thread>
#include<mutex>
#include<condition_variable>
using namespace std;

std::deque<int> q;
std::mutex mu;
std::condition_variable cond;

void function_1()
{
    int count = 10;
    while(count > 0)
    {
        std::unique_lock<mutex> locker(mu);
        q.push_front(count);
        locker.unlock();

        cond.notify_one();  //Notify one waiting thread, if there is one.
            //cond.notify_all()
        std::this_thread::sleep_for(chrono::seconds(1));
        count --;
    }
}

void function_2()
{
    int data = 0;
    while(data != 1)
    {
        std::unique_lock<mutex> locker(mu);
        if(!q.empty())
        {
            data = q.back();
            q.pop_back();
            locker.unlock();
            cout << "t2 got a variable from t1: " << data << endl;
        }
        else
        {
            locker.unlock();

            std::this_thread::sleep_for(chrono::milliseconds(10)); //to solve the busy-waiting problem
        }
    }
}

void function_2()
{
    int data = 0;
    while(data != 1)
    {
        std::unique_lock<mutex> locker(mu);

        cond.wait(locker); //put thread 2 into sleep until being notified by thread 1

        cond.wait(locker, [](){ return !q.empty();});  //spurious wake

        data = q.back();
        q.pop_back();
        locker.unlock();
        cout << "t2 got a variable from t1: " << data << endl;

    }
}

int main()
{
    std::thread t1(function_1);
    std::thread t2(function_2);
    t1.join();
    t2.join();

    return 0;
}

/* Summary
 *  3 ways to get a future:
 *  - promise::get_future()
 *  - packaged_task::get_future()
 *  - async() returns a future
 */