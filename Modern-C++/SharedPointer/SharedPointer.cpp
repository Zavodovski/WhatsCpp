#include<iostream>
#include<string>
#include<memory>
using namespace std;

class Dog
{
    string name_;
public:
    Dog(string name) { cout << "Dog is created: " << name << endl; name_ = name;}
    Dog() { cout << "Nameless dog created." << endl; name_ = "nameless";}
    ~Dog() { cout << "dog is destoryed: " << name_ << endl;}
    void bark() { cout << "Dog: " << name_ << " rules!" << endl;}
};
#if 0
void foo()
{
    Dog* p = new Dog("Gunner");
    //...
    //delete p;
    //...
    p->bark(); //p is a dangling pointer - undefined behavior
}// Memory leak
#endif

#if 0
void foo()
{
    shared_ptr<Dog> p1 = make_shared<Dog>("Gunner");
    shared_ptr<Dog> p2 = make_shared<Dog>("Tank");
    p1 = p2;  //Gunner is deleted
    p1 = nullptr;  //Gunner is deleted
    p1.reset();  //the pointer of p1 is reset to empty, Gunner is deleted.
}
#endif

void foo()
{
    shared_ptr<Dog> p1 = make_shared<Dog>("Gunner");  //using default deleter
    shared_ptr<Dog> p2 = shared_ptr<Dog>(new Dog("Tank"),
                [](Dog* p) { cout << "Custom deleting. " ; delete p;});  //using custom deleter

    shared_ptr<Dog> p3(new Dog[3]);  //p3 points to the first dog, 
        //when p3 goes out of the scope, only the first dog is deleted, dog[1] and dog[2] memory leak

    shared_ptr<Dog> p4(new Dog[3], [](Dog* p) { delete[] p;}); // all 3 dogs will be deleted when p4 goes out of scope

    Dog* d = p1.get(); // returns the raw pointer

    //delete d;  //bad idea; memory repeated release when p1 goes out of scope
    //shared_ptr<Dog> p5(d);  //bad idea memory repeated release when p1 and p5 goes out of scope

}

void foosptr()
{
    shared_ptr<Dog> p(new Dog("Gunner"));  //Count = 1\
        //1. "Gunner" is created; 2. p is created
        //what if 1 successful but 2 falied(maybe because memory allocation failure)
        // -> "Gunner" will not be managed by a shared pointer therefore it will not be deleted and its memory will be leaked. 
    {
        shared_ptr<Dog> p2 = p;  //Count = 2
        p2->bark();
        cout << p.use_count() << endl;
    }
    //count = 1
    p->bark();
}//Count = 0

int main()
{
    {
    foosptr();
    }
    {
    foo();
    }
    //An object should be assigned to a smart pointer as soon as it is created. Raw pointer should not be used.
    //Dog* d = new Dog("Tank");  //Bad idea
    //shared_ptr<Dog> p(d);  //p.use_count == 1
    //shared_ptr<Dog> p2(d); //p2.use_count == 1
    //when p is destroyed, d is delete; when p2 is destoryed, d is delete again and thus undefined behavior.
    
    //shared_ptr<Dog> p = make_shared<Dog>("Tank");  //faster and safer

    //(*p).bark();
    //static_pointer_cast
    //dynamic_pointer_cast
    //const_pointer_cast

    return 0;
}