#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<algorithm>
#include<functional>
#include<math.h>
#include<deque>
using namespace std;
/*
 *  Function Objects (functors)
 *  Benefits of functor 
 *  1. Smart function: capabilities beyond operator()
 *      It can have member data to remember its own functor state, so two different instance of a same functor may behave differently
 *  2. It can have its own type, while regular function's type is decided by its function signature
 *      Functors can be of different type even if they have the exact same function signature 
 *  Example:
 */

class X
{
public:
    //functor overloads the parenthesis and functor is different from type conversion function in syntax
    void operator() (string str)   //type before operator
    {
        cout << "Calling functor X with parameter " << str << endl;
    }
    operator string() const { return "X";}   //type conversion function(type after operator)

};

/*
 *  Parameterized Function
 *  so we can call functor like this Y(8)("Hi")
 */
class Y
{
public:
    Y(int i) {}
    void operator() (string str)
    {
        cout << "Calling functor Y with parameter " << str << endl;
    }
};

//why do we need Parameterized function, why do we just create a function with a int parameter and a string parameter
//look the following example
void add2(int i)  //hard coding a number into a function and its name thus not extendable
{
    cout << i + 2 << endl;
}

//Solution one
//disadvantage: val is decided in compile-time, so you can use it like this
//int x = 2;   //have to change it to (const int x = 2)
//for_each(vec.begin(), vec.end(), addVal<x>);
template<int val>
void addValue(int i)
{
    cout << val + i << endl;
}

void addVal(int i, int val)
{
    cout << i + val << endl;
}
//Solution two(most flexible solution)
class AddValue
{
private:
    int val;
public:
    AddValue(int j) : val(j) {}
    void operator()(int i)
    {
        cout << i + val << endl;
    }
};

/*
 *  STL already provides some built-in functors
 *  less greater greater_equal less_equal not_equal_to
 *  logical_and logical_not logical_or 
 *  multiplies minus plus divide modulus negate
 */
//int x = multiplies<int>()(3, 4);  // x = 3 * 4
// if(not_equal_to<int>()(x, 10))   //if(x != 10)
//     cout << x << endl;

//Convert a regular function to a functor
double Pow(double x, double y)
{
    return pow(x,  y);
}

bool needCopy(int x)
{
    return (x > 20) || (x < 5);
}
//won't work because lsb_less is a funtion or function pointer but not a funtion type(functor)
bool lsb_less(int x, int y)
{
    return (x % 10) < (y % 10);
}

class Lsb_less
{
public:
    bool operator()(int x, int y)
    {
        return (x % 10) < (y % 10);
    }
};

/*
 *  Predicate 
 *
 *  A functor or function that:
 *  1. Returns a boolean
 *  2.Does not modify data
 */

class NeedCopy
{
    //pass by value so there is no way to modify the data
public:
    bool operator()(int x)
    {
        return (x > 20) || (x < 5);
    }
};

int main()
{
    cout << "-------class X-------------" << endl;
    X fooX;
    fooX("Hi");  //Calling functor X with parameter Hi

    cout << "-------class Y-------------" << endl;
    Y(8)("Hi");
    
    cout << "-------Parameterized function-------------" << endl;
    vector<int> vec = {2, 3, 4, 5};
    for_each(vec.begin(), vec.end(), add2);  //print out {4, 5, 6, 7}
    for_each(vec.begin(), vec.end(), addValue<2>);
    int x = 2;
    for_each(vec.begin(), vec.end(), AddValue(x));

    cout << "-------bulit-in functors-------------" << endl;
    int var = multiplies<int>()(3, 4);  // var = 3 * 4
    if(not_equal_to<int>()(var, 10))      //if(var != 10)
        cout << var << endl;

    /*
     *  Parameter Binding
     */
    cout << "-------Parameter Binding-------------" << endl;
    set<int> myset = {2, 3, 4, 5};
    vector<int> vec1;
    //Multiply myset's elements by 10 and save in vec:
    transform(myset.begin(), myset.end(),     //source 
                back_inserter(vec1),           //destination
                bind(multiplies<int>(), placeholders::_1, 10)); //functor
                //placeholders::_1 means the first parameter of multiplies<int>() is substituted with myset's element
                //vec: {20, 30, 40, 50}
    for(auto it = vec1.begin(); it != vec1.end(); it ++)
        cout << *it << " ";
    cout << endl;

    //we also can use parameter binding to solve the previous problem
    for_each(vec1.begin(), vec1.end(), bind(addVal, placeholders::_1, 2));

    //Convert a regular function to a functor
    cout << "-------Convert function-------------" << endl;
    set<int> myset1 = {3, 1, 15, 7, 12};
    deque<int> d;
    auto f = function<double (double, double)>(Pow);  //C++ 11
    transform(myset1.begin(), myset1.end(),    //source 
            back_inserter(d),                  //destination
            bind(f, placeholders::_1, 2));     //functor
            //d: {1, 9, 49, 144, 625}
    for(auto it = myset1.begin(); it != myset1.end(); it ++)
        cout << *it << " ";
    cout << endl;
    for(auto it = d.begin(); it != d.end(); it ++)
        cout << *it << " ";
    cout << endl;

    deque<int> d1;
    //when x > 20 || x < 5, copy from myset1 to d1
    transform(myset1.begin(), myset1.end(),     //source
            back_inserter(d1),                  //destination
            bind(logical_or<  bool>(), 
            bind(greater<int>(), placeholders::_1, 20),
            bind(less<int>(), placeholders::_1, 5)));
    
    //another ways to do this        
    //transform(myset1.begin(), myset1.end(), back_inserter(d1), needCopy);
    //lambda function
    // transform(myset1.begin(), myset1.end(), back_inserter(d1),
    //         [](int x){return (x > 20) || (x < 5);});

    for(auto it = d1.begin(); it != d1.end(); it ++)
        cout << *it << " ";
    cout << endl;


    //why do we need functor in STL?
    //set<int> myset2 = {3, 1, 25, 7, 12};   //myset2 = {1, 3, 7, 12, 25}
    //set can take two template parameters, the second is comparison functot(default: less<int>)
    //same as
    set<int, less<int>> myset2 = {3, 1, 25, 7, 12};

    //sort by a different order
    //set<int, lsb_less> myset3 = {3, 1, 25, 7, 12};  //myset3 = {1, 12, 3, 25, 7}
    set<int, Lsb_less> myset3 = {3, 1, 25, 7, 12};  //myset3 = {1, 12, 3, 25, 7}
    
    for(auto it = myset3.begin(); it != myset3.end(); it ++)
        cout << *it << " ";
    cout << endl;

    //Predicate
    //Predicate is used for comparison or condition check
    cout << "-------Predicate-------------" << endl;
    set<int> myset4 = {3, 1, 25, 7, 12};
    deque<int> d2;
    transform(myset4.begin(), myset4.end(), back_inserter(d2), NeedCopy());
    
    for(auto it = d2.begin(); it != d2.end(); it ++)
        cout << *it << " ";
    cout << endl;
    return 0;
}