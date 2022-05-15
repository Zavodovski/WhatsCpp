#include<iostream>
#include<deque>
using namespace std;

class Dog
{
public:
    virtual void bark() { cout << "I don't have a name." << endl;}
};

class YellowDog : public Dog
{
    string m_name;
public:
    YellowDog(string name):m_name(name) {}
    void bark() { cout << "My name is " << m_name << endl;}
};

int main()
{
    // deque<Dog> d;
    // YellowDog y("Gunner");
    // d.push_front(y);  //take y as a parameter and copy construct a dog(not yellowdog) and push that new constructed dog into deque d 
    // d[0].bark();      //thus d[0] is a dog, object slicing happens

    deque<Dog*> d;
    YellowDog y("Gunner");
    d.push_front(&y);
    d[0]->bark();


    //other situations that object slicing happens
    //Dog d2 = y; //d2 created from y by slicing some of its members off
    //void foo(Dog d){}
    //foo(y)  //y is sliced to create a dog and then pass to the function foo 
    
    return 0;
}