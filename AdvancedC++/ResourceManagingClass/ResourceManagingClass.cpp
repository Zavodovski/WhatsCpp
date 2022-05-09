#include<iostream>
#include<string>
#include<vector>
using namespace std;
#if 0
//Person owns the string through its pointer
class Person
{
public:
    Person(string name) { pName_ = new string(name);}
    ~Person() { delete pName_;}

    void printName() { cout << *pName_;}
private:
    string* pName_;
};
#endif

#if 0
//Solution 1: Define copy constructor and copy assignment operator for deep copy
class Person
{
public:
    Person(string name) { pName_ = new string(name);}
    ~Person() { delete pName_;}

    Person(const Person& rhs)
    {
        pName_ = new string(*(rhs.pName()));
    }
    Person& operator=(const Person& rhs); //deep copying
    void printName() { cout << *pName_;}
    string* pName() const { return pName_;}
private:
    string* pName_;
};
#endif

//Solution 2: Delete copy constructor and copy assignment operator, define clone().
class Person
{
public:
    Person(string name) { pName_ = new string(name);}
    ~Person() { delete pName_;}

    
    void printName() { cout << *pName_;}
    string* pName() const { return pName_;}

    Person* clone()
    {
        return (new Person(*(pName_)));
    }
private:
    Person(const Person& rhs);

    Person& operator=(const Person& rhs); //deep copying
    string* pName_;
};

int main()
{
    vector<Person*> persons;
    persons.push_back(new Person("George"));
        //1. "George" is constructed
        //2. A copy of "George" is saved in the vector persons(default shallow copy)
        //3. "George" is destroyed. so the pointer in vector points to a deleted object
    
    persons.back()->printName();

    cout << "Goodbye" << endl;
}
#if 0
//for the original class definition and solution one
int main()
{
    vector<Person> persons;
    persons.push_back(Person("George"));
        //1. "George" is constructed
        //2. A copy of "George" is saved in the vector persons(default shallow copy)
        //3. "George" is destroyed. so the pointer in vector points to a deleted object
    
    persons.back().printName();

    cout << "Goodbye" << endl;
}
#endif