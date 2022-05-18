#include<iostream>
#include<algorithm>
#include<functional>
#include<mutex>
#include<thread>
#include<future>
#include<deque>
using namespace std;

int factorial(int N)
{
    int res = 1;
    for(int i = N; i > 1; i --)
        res *= i;
    cout << "Result is: " << res << endl;
    return res;
}

std::deque<std::packaged_task<int()>> task_q;
std::mutex mu;
std::condition_variable cond;

void thread_1()
{
    std::packaged_task<int()> t;
    {
        std::unique_lock<std::mutex> locker(mu);
        cond.wait(locker, [](){ return !task_q.empty();});
        t = std::move(task_q.front());
        task_q.pop_front();
    }
    t();
}
int main()
{
    std::thread t1(thread_1);  
    //std::packaged_task<int(int)> t(factorial); // a package of tasks that can be transported to different place in the program and being executed over there
    std::packaged_task<int()> t(std::bind(factorial, 6));

    //...

    std::future<int> fu = t.get_future();
    {
        std::lock_guard<std::mutex> locker(mu);
        task_q.push_back(std::move(t));
    }

    cond.notify_one();

    cout << fu.get() << endl;
    //t(6);  //can execute in a different context
    //int x = t.get_future().get();  //get the return value from the factorial function

    t1.join();

    
    return 0;
}