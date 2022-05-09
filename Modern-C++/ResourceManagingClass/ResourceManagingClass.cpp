#include<iostream>
#include<string>
#include<vector>
#include<memory>
using namespace std;

#if 0
//Person owns the string through its pointer
class Person
{
public:
    Person(string name) : pName_(new string(name)){}
    ~Person() { delete pName_;}
    //Person(const Person&) = delete; //the copy constructor is deleted

    void printName() { cout << *pName_;}
private:
    string* pName_;
};
#endif

/*
 *  C++11:
 *    1. Keyword "delete"
 *    2. emplace_back()
 *    3. shared_ptr
 *    4. unique_ptr
 *    5. move()
 */ 

class Person
{
public:
    Person(string name) : pName_(new string(name)){}
    //~Person() { }
    //Person(const Person&) = delete; //the copy constructor is deleted
    //Person(Person&&) = default;  //如果有空析构函数则编译器不会默认生成移动构造，可以通过这行代码让编译器仍然生成移动构造
    void printName() { cout << *pName_;}
private:
    unique_ptr<string> pName_;
};


int main()
{
    vector<Person> persons;
    //persons.push_back(Person("George"));
        //1. "George" is constructed
        //2. A copy of "George" is saved in the vector persons(default shallow copy)
        //3. "George" is destroyed. so the pointer in vector points to a deleted object
    //persons.emplace_back("George");  //construct the object in place(in the space allocated to the vector)
    Person p("George");
    persons.push_back(std::move(p));

    persons.back().printName();

    cout << "Goodbye" << endl;
}