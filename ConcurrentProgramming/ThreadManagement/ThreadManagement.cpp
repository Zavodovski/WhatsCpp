#include<iostream>
#include<thread>
using namespace std;

void function_1()
{
    std::cout << "Beauty is only skin-deep" << std::endl;
}

class Functor
{
public:
    // void operator()(string& msg)
    // {
    //     cout << "t1 says: " << msg << endl;
    //     // for(int i = 0; i > -100; i --)
    //     //     cout << "from t1 " << i << endl;
    //     msg = "Trust is the mother of deceit.";
    // }

    void operator()(string&& msg)
    {
        cout << "t1 says: " << msg << endl;
        // for(int i = 0; i > -100; i --)
        //     cout << "from t1 " << i << endl;
        msg = "Trust is the mother of deceit.";
    }
};

int main()
{
    string s = "Where there is no trust, there is no love.";
    cout << std::this_thread::get_id() << endl;
    //Functor fct;
    //std::thread t1(fct);  //t1 starts running
    //std::thread t1((Functor()));
    std::thread t1((Functor()), s);   //a parameter to a thread is always passed by value
    //std::thread t1((Functor()), std::ref(s)); //pass the parameter by ref 
    //std::thread t1((Functor()), std::move(s));  //move the s from the main thread to the child thread, both safe and efficient
    cout << t1.get_id() << endl;
    //std::thread t2 = t1;  //thread cannot be copied, it can only be moved
    
    //std::thread t2 = std::move(t1);  //correct way

    //using RAII
    //Wrapper w(t1)
    t1.join();
    // try
    // {
    //     cout << "from main: " <<  s << endl;
    //     // for(int i = 0; i < 100; i ++)
    //     //     cout << "from main: " << i << endl;
    // }
    // catch(...)
    // {
    //     t1.join();
    //     throw;
    // }
    cout << "from main: " << s << endl;
    //t1.join();

    //Oversubscription
    //If there are more threads running than available CPU cores, it creates a lot of context switching
    cout << std::thread::hardware_concurrency() << endl;  //Indication of how many threads can be truly running concurrently for program


    return 0;
}