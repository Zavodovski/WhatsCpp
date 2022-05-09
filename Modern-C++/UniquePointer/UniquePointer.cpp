#include<iostream>
#include<string>
#include<memory>
using namespace std;

//Unique Pointers: exclusive ownership, light weight smart pointer

class Dog
{

public:
    string m_name;
    Dog(string name) { cout << "Dog is created: " << name << endl; m_name = name;}
    Dog() { cout << "Nameless dog created." << endl; m_name = "nameless";}
    ~Dog() { cout << "dog is destoryed: " << m_name << endl;}
    void bark() { cout << "Dog: " << m_name << " rules!" << endl;}

};

#if 0
void test()
{
    Dog* pD = new Dog("Gunner");

    pD->bark();
    //pD does a bunch of different things

    delete pD;  //if test returns to the main prematurely(for example throw an exception), this line will not run and thus memory leak;
}
#endif

#if 0
void test()
{
    unique_ptr<Dog> pD(new Dog("Gunner"));

    pD->bark();
    //pD does a bunch of different things

    //Dog* p = pD.release();  //pD gives up its ownership of the dog  therefore nobody owns the dog anymore and nobody will automatically delete the dog
    //pD.reset(new Dog("Smokey"));  //the original object Gunner will be destroyed
    pD.reset(); // pD = nullptr
    if(!pD)
        cout << "pD is empty.\n";
    else 
        cout << "pD is not empty.\n"; 
}
#endif

#if 0

void test()
{
    unique_ptr<Dog> pD(new Dog("Gunner"));
    unique_ptr<Dog> pD2(new Dog("Smokey"));
    pD2->bark();
    pD2 = move(pD);
    //1. Smokey is destroyed
    //2. pD becomes empty
    //3. pD2 owns Gunner
    pD2->bark();
}

#endif

void f(unique_ptr<Dog> p)
{
    p->bark();
}

unique_ptr<Dog> getDog()
{
    unique_ptr<Dog> p(new Dog("Smokey"));
    return p;   //return by value so will automatically use the move semantics
}

void test()
{
    unique_ptr<Dog> pD(new Dog("Gunner"));
    f(move(pD));
    if(!pD) cout << "pD is empty.\n";

    unique_ptr<Dog> pD2 = getDog();

    unique_ptr<Dog[]> dogs(new Dog[3]);  //unique_ptr is partial specialized for array

}

int main()
{
    test();
    return 0;
}