#include<iostream>
using namespace std;

//class Dog {};  equivalent to the following class

class Dog
{
    //C++ 03:
    Dog();    //default constructor
    Dog(const Dog&);     //copy constructor
    Dog& operator=(const Dog&);  //copy assignment operator
    ~Dog();   //destructor

    //C++ 11:
    Dog(Dog&&);   //move constructor
    Dog& operator=(Dog&&);  //move assignment operator
};

/*
 *  C++ 03:
 *  1. default constructor (generated only if no constructor is declared by user)
 *  2. copy constructor (generated only if no 5, 6 declared by user)  //C++ 11: (generated only if no 3, 4, 5, 6 declared by user)
 *  3. copy assignment operator (generated only if no 5, 6 declared by user)  //C++ 11: (generated only if no 2, 4, 5, 6 declared by user)
 *  4. destructor
 * 
 *  C++ 11:
 *  5. move constructor(generated only if 2, 3, 4, 6 not declared by user)
 *  6. move assignment operator(generated only if 2, 3, 4, 5 not declared by user)
 */


class Cat  
{
    Cat(const Cat&) { }  //copy constructor
};  //Compiler will generate 3, 4 (3 is deprecated in C++ 11)

class Duck
{
    Duck(Duck&&) { }  //move constructor
}; //Compiler will generate 4

class Frog
{
    Frog(Frog&&, int = 0) { } //move constructor
    Frog(int = 0) { }  //default constructor
    Frog(const Frog&, int = 0) { } //copy constructor
}; //Compiler will generate 4

class Fish
{
    ~Fish() { }
}; //Compiler will generate 1, 2, 3  (2, 3 are deprecated in C++ 11)

class Cow
{
    Cow& operator=(const Cow&) = delete;  //still counted as the copy assignment operator declared by user
    //Cow(const Cow&) = default; //bring back the copy constructor in C++ 11
}; //Compiler will generate 1, 2, 4  (2 is deprecated in C++ 11)
