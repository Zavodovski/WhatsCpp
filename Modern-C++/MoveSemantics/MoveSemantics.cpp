//C++ 11: Rvalue Reference
//
// 1. Moving Semantics
// 2. Perfect Forwarding
//
//Prerequisite: understanding rvalue and lvalue

/*  Move Constructor/Move Assignment Operator:
 *  Purpose: conveniently avoid costly and unnecessary deep copying.
 *  
 *  1. They are particularly powerful where passing by reference and passing by value are both used.
 *  2. They give you final control of which part of your object to be moved.
 */

#include<iostream>
using namespace std;
void printInt(int& i) { cout << "lvalue reference: " << i << endl;}
void printInt(int&& i) { cout << "rvalue reference: " << i << endl;}

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

void foo(boVector v);

boVector createBoVector();  //Creates a boVector

void foo_by_value(boVector v);
void foo_by_ref(boVector& v);

int main()
{
    //What is rvalue reference?
    int a = 5; //a is lvalue;
    //int& b = a; //b is a lvalue reference(reference)
    //int&& c; //c is a rvalue reference

    printInt(a); //Call printInt(int& i) because a is lvalue
    printInt(6); //Call printInt(int&& i) because 6 is rvalue


    boVector reusable = createBoVector();
    foo(reusable);  //invoke copy constructor to make a copy of reusable and pass it to the function
                    //deep copy is expensive but for reusable resources it's deserved
    foo(createBoVector()); //if there is no move constructor it also invokes copy constructor 
                        //but createBoVector() returns a rvalue(a temporary that will be destroyed momentarily) why do we make a copy of it rather than use this already created object and pass it to foo directly
    
    
    
    foo_by_ref(reusable);  //call no constructor
    foo(reusable);  //call copy constructor
    foo(createBoVector()); //invoke move constructor(inexpensive, flexible and efficient)
    foo(std::move(reusable));  //call move constructor, move the object of reusable to the foo function
        //reusable is destoryed here, reusable.arr_ == nullptr
    foo_by_value(reusable);

    
    
    
    return 0;
}

#if 0
/*
 *  Note 1: the most useful place for rvalue reference is overloading copy constructor and copy assignment opoerator, to achieve move semantics.
 */

X& X::operator=(X const& rhs);
X& X::operator=(X&& rhs);


/*
 *  Note 2: MOve semantics is implemented for all STL containers, which means
 *  1. move to C++ 11, your code will be faster without changing a thing
 *  2. passing-by-value can always be used for STL containers
 */

vector<int> foo()
{
    //...
    return myvector;
}
void hoo(string s);

bool goo(vector<int>& arg);  //pass by reference if you use arg to carry data back from goo()
#endif