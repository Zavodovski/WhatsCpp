#include<iostream>
#include<thread>
#include<mutex>
#include<future>
using namespace std;


class A
{
public:
    void f(int x, char c) { }
    long g(double x) { return 0; }
    int operator()(int N) { return 0;}
};

//callable objects
//std::thread t1(a, 6)
//std::async(std::launch::async, a, 6);
//std::bind(a, 6)
//std::call_once(once_flag, a, 6)

void foo(int x) { }

int main()
{
    A a;
    std::thread t1(a, 6);   //copy_of_a() in a different thread
    std::thread t2(std::ref(a), 6);  //a() in a different thread
    std::thread t8(std::move(a), 6); //a is no longer usable in main thread
    std::thread t3(A(), 6);  //temp A; temporary a is moved into the thread object and then create a thread
    std::thread t4([](int x){ return x * x; }, 6);  //lambda function
    std::thread t5(foo, 7);

    std::thread t6(&A::f, a, 8, 'w');  //copy_of_a and invoke a.f(8, 'w') in a different thread
    std::thread t7(&A::f, &a, 8, 'w');  //a.f(8, 'w') in a different thread

    //std::bind(); std::async(); std::call_once()

    return 0;
}