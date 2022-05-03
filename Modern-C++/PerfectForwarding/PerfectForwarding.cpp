#include<iostream>
using namespace std;

class boVector
{
    int size;
    double* arr_; //a big array
public:
    boVector(const boVector&  rhs)  //Copy constructor
    {
        size = rhs.size;
        arr_ = new double[size];
        for(int i = 0; i < size; i ++) arr_[i] = rhs.arr_[i]; 
    }

    boVector(boVector&& rhs)  //Move constructor
    {
        size = rhs.size;
        arr_ = rhs.arr_;
        rhs.arr_ = nullptr;
    }
    ~boVector() { delete[] arr_;}
};

void foo(boVector arg);
//boVector has both move constructor and copy constructor

// template<typename T>
// void relay(T arg)
// {
//     foo(arg);
// }

boVector createBoVector();  //Creates a boVector

int main()
{
    boVector reusable = createBoVector();
    relay(reusable);
    //...;
    relay(createBoVector());

    return 0;
}

/*
 *  1. No costly and unnecessary copy construction of boVector is made.
 *  2. rvalue is forward as a rvalue, and lvalue is forwarded as a lvalue.
 * 
 */

//Solution:
template<typename T>
void relay(T&& arg)
{
    foo(std::forward<T> (arg));
}

//Note: this will work because type T is a template type.

/*
 *  Reference Collapsing Rules(C++ 11):
 *  1. T& & ==> T&
 *  2. T& && ==> T&
 *  3. T&& & ==> T&
 *  4. T&& && ==> T&&
 */
#if 0

template<class T>
struct remove_reference;  //It removes reference on type T

//T is int&
//remove_reference<int&>::type i;  //int i;
//remove_reference<int>::type i; //int i;

/*
 *  rvalue reference is specified with type&&.
 *
 *  type&& is rvalue reference?
 */

//T&& variable is initialized with rvalue => rvalue reference
relay(9); //=>  T = int && => T&& = int&& && = int &&

//T&& variable is initialized with lvalue => lvalue reference
relay(x); => T = int& => T&& = int& && = int&

//T&& is universal Reference: rvalue, lvalue, const, non-const, etc...;
//Conditions:
//1. T is a template type.
//2. Type deduction(reference collapsing) happens to T.
//  - T is a function template type, not class template type.


//Complete Solution for Perfect Forwarding
template<typename T>
void relay(T&& arg)
{
    foo(std::forward<T>(arg));
}
//Implementation of std::forward()
template<class T>
T&& forward(typename remove_reference<T>::type& arg)
{
    return static_cast<T&&>(arg);
}

//std::move() vs std::forward()
std::move<T>(arg);  //Turn arg into an r value type
std::forward<T>(arg); //Turn arg to type of T&&
#endif