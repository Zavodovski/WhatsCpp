#include<iostream>
#include<thread>
#include<future>
#include<mutex>
using namespace std;


//std::mutex mu;
//std::condition_variable cond;


// void factorial(int N)
// {
//     int res = 1;
//     for(int i = N; i > 1; i --)
//         res *= i;
//     cout << "Result is: " << res << endl;
// }

// int factorial(int N)
// {
//     int res = 1;
//     for(int i = N; i > 1; i --)
//         res *= i;
//     cout << "Result is: " << res << endl;
//     return res;
// }

// int factorial(std::future<int>& f)
// {
//     int res = 1;
//     int N = f.get();    //exception: std::future_errc::broken_promise
//     for(int i = N; i > 1; i --)
//         res *= i;
//     cout << "Result is: " << res << endl;
//     return res;
// }

int factorial(std::shared_future<int> f)  //shared_future can be copied and thus pass by value
{
    int res = 1;
    int N = f.get();    //exception: std::future_errc::broken_promise
    for(int i = N; i > 1; i --)
        res *= i;
    cout << "Result is: " << res << endl;
    return res;
}


#if 0
int main()
{
    //std::thread t1(factorial, 4);

    //t1.join();

    int x;


    std::future<int> fu  = std::async(factorial, 4); 
        //future is a channel where we can get the return result from the child thread
    x = fu.get();   //a future object can only call the get function only once otherwise crash
        //get function will wait until the child thread finish and then return the value from the child thread
   
    std::future<int> fu = std::async(std::launch::deferred, factorial, 4);
        //std::launch::deferred: the async function will not create a thread, it will actually defer the execution of factorial until later on when the get function is called
        //when get function is called, factorial will be executed in the same thread
    
    std::future<int> fu = std::async(std::launch::async, factorial, 4);
        //std::launch::async: will create another thread

    std::future<int> fu = std::async(std::launch::deferred | std::launch::async, factorial, 4);
        //std::launch::deferred | std::launch::async: default value for this parameter
        //whether the async function will create another thread or not will detemined by the implementation
    return 0;
}
#endif

//neither promise nor future can be copied, they can only be moved
//std::promise<int> p2 = std::move(p)

#if 0
int main()
{
    int x;

    std::promise<int> p;
    std::future<int> f = p.get_future();

    std::future<int> fu = std::async(std::launch::async, factorial, std::ref(f));

    //...do something else
    std::this_thread::sleep_for(chrono::milliseconds(20));
    p.set_value(4);  

    //p.set_exception(std::make_exception_ptr(std::runtime_error("To err is human")));
    x = fu.get();

    cout << "Get from child: " << x << endl;
    return 0;
}
#endif

int main()
{
    int x;

    std::promise<int> p;
    std::future<int> f = p.get_future();
    std::shared_future<int> sf = f.share();

    std::future<int> fu = std::async(std::launch::async, factorial, sf);
    std::future<int> fu2 = std::async(std::launch::async, factorial, sf);
    std::future<int> fu3 = std::async(std::launch::async, factorial, sf);
    //...10 threads

    p.set_value(4); //all child threads will get the value 4
        //it's very convenient for a broadcast kind of communication model

    return 0;
}