#include<iostream>
#include<string>
#include<memory>

using namespace std;

class Dog
{
    //shared_ptr<Dog> m_pFriend;
    weak_ptr<Dog> m_pFriend;
public:
    string m_name;
    Dog(string name) { cout << "Dog is created: " << name << endl; m_name = name;}
    Dog() { cout << "Nameless dog created." << endl; m_name = "nameless";}
    ~Dog() { cout << "dog is destoryed: " << m_name << endl;}
    void bark() { cout << "Dog: " << m_name << " rules!" << endl;}
    void makeFriend(shared_ptr<Dog> f) { m_pFriend = f;}

    void showFriend()
    {
        if(!m_pFriend.expired()) cout << "My friend is: " << m_pFriend.lock()->m_name << endl;
        cout << " He is owned by " << m_pFriend.use_count() << " pointer. " << endl;
    }

};

int main()
{
    shared_ptr<Dog> pD(new Dog("Gunner"));
    shared_ptr<Dog> pD2(new Dog("Smokey"));
    pD->makeFriend(pD2);    
    pD2->makeFriend(pD);    //cyclic reference
    pD->showFriend();
    return 0;
}