#include<iostream>
#include<thread>
using namespace std;

void function_1()
{
    cout << "Beauty is only skin-deep" << endl;
}

int main()
{
    //function_1();
    std::thread t1(function_1); //t1 starts running
    //t1.join();   //main thread waits for t1 to finish

    t1.detach();  //t1 will freely on its own -- daewon process

    if(t1.joinable()) t1.join();
        //Note: a thread can only be joined or detached once otherwise crashed 
    return 0;
}