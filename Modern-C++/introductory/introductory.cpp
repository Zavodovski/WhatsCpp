#include<vector>
using namespace std;
#if 0
/*
 *  Learn C++11
 */

/*
 *  1. Initializer List
 */

//C++ 03 initializer list:
int arr[4] = {3, 2, 4, 5};
vector<int> v;
v.push_back(3);
v.push_back(2);
v.push_back(4);
v.push_back(5);

//C++ 11 extended the support
vector<int> v = {3, 4, 1, 9};  //Calling initializer_list constructor

//All the relevant STL containers have been updated to accept initializer_list.

//Define your own initializer_list constructor
#include<initializer_list>
class boVector
{
    vector<int> m_vec;
public:
    boVector(const initializer_list<int>& v)
    {
        for(initializer_list<int>::iterator itr = v.begin(); itr != v.end(); itr ++)
        {
            m_vec.push_back(*itr);
        }
    }
};

boVector v = {0, 2, 3, 4};
boVector v{0, 2, 3, 4};  //effectively the same

/*
 *  2.Uniform Initialization
 */

//C++ 03
class dog  //Aggregate class or struct
{
public:
    int age;
    string name;
};

dog d1 = {5, "Henry"};   //Aggregate Initialization

//C++ 11 extended the scope of curly brace initialization
class dog
{
public:
    dog(int age, string name) {...};
};
dog d1 = {5, "Henry"};

/*  Uniform Initialization Search Order:
 *  1. Initializer_list constructor
 *  2. Regular constructor that takes the appropriate parameters
 *  3. Aggregate initializer
 */

dog a1{3};

class dog
{
public:
    int age;                                    //3rd choice

    dog(int a) { age = a;}                      //2nd choice

    dog(const initializer_list<int>& vec)       //1st choice
    {
        age = *(vec.begin());
    }
};

/*
 *  3. auto type
 */

vector<int> vec = {2, 3, 4, 5};
//C++ 03
for(vector<int>::iterator it = vec.begin(); it != vec.end(); it ++)
    m_vec.push_back(*it);


//C++ 11: use auto type
for(auto it = vec.begin(); it != vec.end(); it ++)
    m_vec.push_back(*it);

auto a = 6;  //a is an integer
auto b = 9.6; //b is a double
auto c = a;  //a is an integer

/*
 * 4.foreach
 */

//C++ 03:
for(vector<int>::iterator itr = v.begin(); itr != v.end(); itr ++)
    cout << (*itr);

//C++ 11:
for(auto i : v) //read-only access
{
    cout << i; //works on any class that has begin() and end()
}

for(auto& i : v) i++; //changes the values in v

/*
 *  5. nullptr
 *
 *  To replace NULL in C++ 03  NULL -- 0
 */

void foo(int i) { cout << "foo_int" << endl;}
void foo(char* pc) { cout << "foo_char*" << endl;}

int main()
{
    foo(NULL);   //Ambiguity  NULL is a int 0 or char* ?

    //C++ 11
    foo(nullptr); //call foo(char*)  nullptr is dedicated to represent null pointer
}


/*
 *  6. enum class
 */

//C++ 03
enum apple {greean_a, red_a};
enum orange {big_o, small_o};
apple a = green_a;
orange o = big_o;

if(a == o)
    cout << "green apple and big orange are the same\n";
else
    cout << "green apple and big orange are not the same\n";

//C++ 11
enum class apple {green, red};
enum class orange {big, small};
apple  a = apple::green;
orange o = orange::big;

if(a == o)
    cout << "green apple and big orange are the same\n";
else
    cout << "green apple and big orange are not the same\n";
//complie fails because we haven't define ==(apple, orange)

/*
 *  7. static_assert
 */
//run-time assert
assert(myPointer != NULL)

//compile time assert(C++ 11)
static_assert(sizeof(int) == 4)

/*
 *  8. Delegating Constructor
 */

class dog
{
public:
    dog() {...}
    dog(int a) { dog(), doOtherThings(a);}
};//works in Java, won't work in C++, will create two dog objects

//C++ 03:
class dog
{
    init(){ ... }
public:
    dog() {init();}
    dog(int a) { init(); doOtherThings();}
};
/*  Cons:
 *      1. Cumbersome code
 *     2. init() could be invoked by other functions
 */

//C++ 11
class dog
{
    int age = 9;
public:
    dog() {...}
    dog(int a) : dog() { doOtherThings();}
};
//Limitation: dog() has to be called first

/*
 *  9.override (for virtual function)
 *
 *  To avoid inadvertently create new function in derived class
 */
//C++ 03

class dog
{
    virtual void A(int);
    virtual void B() const;
};

class yellowdog : public dog
{
    virtual void A(float);  //Created a new function
    virtual void B();  //Created a new function
};

//C++ 11
class  dog
{
public:
    virtual void A(int);
    virtual void B() const;
    void C();
};

class yellowdog : public dog
{
public:
    virtual void A(float) override; //Error: no function to override
    virtual void B() override;      //Error: no function to override
    void C() override;              //Error: no function to override, C() is not a virtual function
};

/*
 *  10. final (for virtual function and for class)
 */

class dog final     //no class can be derived from dog
{
    ...
};

class dog
{
    virtual void bark() final;  //no class can override bark()
};

/*
 *  11. Complier Generated Default Constructor
 */

class dog
{
    dog(int age) {...}
};

dog d1;   //Error: complier will not generate the default constructor

//C++ 11
class dog
{
    dog(int age);
    dog() = default;  //Force complier to generate the default constructor
};


/*
 *  12. delete
 */

class dog
{
    dog(int age) {...}
};

dog a(2); 
dog b(3.0);  //3.0 is converted from double to int
a = b;  //complier generated assignment operator

//C++ 11:
class dog
{
    dog(int age) {...}
    dog(double ) = delete;
    dog& operator = (const dog&) = delete;
}

/*
 *  13. constexpr
 */

int arr[6];  //OK
int A() { return 3;}
int arr[A() + 3];  //Complie Error

//C++ 11
constexpr int A() { return 3;}  //Forces the computation to happen at compile time.
int arr[A() + 3];  //Create an array of size 6

//Write faster program with constexpr
constexpr int cubed(int x) { return x * x * x;}
int y = cubed(1789);  //computed at compile time

/*
 *  14. New String Literals
 */

//C++ 03:
char* a = "string";

//C++ 11:
char* a = u8"string";  //to define an UTF-8 string.
char16_t* b = u"string";    //to define an UTF-16 string.
char32_t* c = U"string";    //to define an UTF-32 string.
char* d = R"(String \\)";     //to define raw string. will have two \\ because the first won't be seen as escaped character anymore.

/*
 *  15. lambda function
 */

cout << [](int x, int y) { return x + y;}(3, 4) << endl;  //output: 7
auto f = [](int x, int y) { return x + y;};
cout << f(3, 4) << endl;  //output: 7

template<typename func>
void filter(func f, vector<int> arr)
{
    for(auto i : arr)
    {
        if(f(i)) cout << i << " ";
    }
}

int main()
{
    vector<int> v = {1, 2, 3, 4, 5, 6};
    filter([](int x){ return (x > 3);}, v);  //output: 4 5 6
    filter([](int x){ return (x > 2 && x < 5);}, v); //output: 3 4

    int y = 4;
    filter([&](int x) { return (x > y);}, v);  //output: 5 6
    //Note: [&] tells complier that we want varriable capture
}

#endif