#include<iostream>
#include<vector>
#include<deque>
#include<list>
#include<algorithm>
#include<array>
using namespace std;

int main()
{
/*
 *  Vector
 *  Properties of Vector
 *  1. fast insert/remove at the end: O(1)
 *  2. slow insert/remove at the beginning or in the middle: O(n)
 *  3. slow search: O(n)
 */
    cout << "---------vector-------------" << endl;
    vector<int> vec;    //vec.size() == 0
    vec.push_back(4);
    vec.push_back(1);
    vec.push_back(8);   //vec.size() == 3

    //Vector specific operations
    cout << vec[2] << endl; //8 (no range check)
    cout << vec.at(2) << endl; //8 (throw range_error exception of out of range)

    //different ways of traversing a vector

    for(int i = 0; i < vec.size(); i ++)  cout << vec[i] << " ";
    cout << endl;

    for(vector<int>::iterator itr = vec.begin(); itr != vec.end(); ++itr)
        cout << *itr << " ";
    cout << endl;

    for(auto it : vec) // C++11
        cout << it << " ";
    cout << endl;

    //Vector is a dynamically allocated contiguous array in memory
    int* p = &vec[0];  //not recommend

    //Common member functions of all containers
    //vec: {4, 1, 8}
    if(vec.empty()) { cout << "Empty" << endl;}

    cout << vec.size() << endl;  //3
    vector<int> vec2(vec);  //Copy constructor, vec2: {4, 1, 8}
    vec.clear();      //Remove all items in vec; vec.size() == 0
    vec2.swap(vec);    //Swap the content of two vectors, vec2 become empty, and vec has three items.
    cout << vec.size() << " " << vec2.size() << endl;

/*
 *  Deque
 *  Properties of Deque
 *  1. fast insert/remove at the beginning and the end: O(1)
 *  2. slow insert/remove in the middle: O(n)
 *  3. slow search: O(n)
 */
    cout << "---------deque-------------" << endl;
    deque<int> deq = {4, 6, 7};
    deq.push_front(2);   //deq: {2, 4, 6, 7}
    deq.push_back(3);    //deq: {2, 4, 6, 7, 3}
    //Deque has similar interface with vector
    cout << deq[1] << endl;  //4
    for(deque<int>::iterator itr = deq.begin(); itr != deq.end(); ++ itr)
        cout << *itr << " ";
    cout << endl;

/*
 *  List(double linked list)
 *  Properties of List
 *  1. fast insert/remove at any place: O(1)
 *  2. slow search: O(n) slower than vector because memory access
 *      vector memory is contiguous and thus more cache hits
 *      however list memory is dispersed and thus more cache misses -> need to swap data in and out of cache
 *  3. no random access, no [] operator.
 */
    cout << "---------list-------------" << endl;
    list<int> mylist = {5, 2, 9};
    mylist.push_back(6);   //mylist: {5, 2, 9, 6}
    mylist.push_front(4);  //mylist: {4, 5, 2, 9, 6}

    list<int>::iterator itr = find(mylist.begin(), mylist.end(), 2);  //itr -> 2
    mylist.insert(itr, 8); //mylist: {4, 5, 8, 2, 9, 6} insert in front of itr
                           //O(1), faster than vector/deque
    itr ++;                //itr -> 9
    mylist.erase(itr);     //mylist: {4, 5, 8, 2, 6} O(1)
    for(list<int>::iterator itr = mylist.begin(); itr != mylist.end(); ++itr)
        cout << *itr << " ";
    cout << endl;

    //Key advantage -> function splice
    //mylist1.splice(itr, mylist2, itr_a, itr_b);  O(1) no matter how big list2 is
    list<int>::iterator itr1 = find(mylist.begin(), mylist.end(), 2);  //itr -> 2
    list<int> mylist2 = {6, 10, 8};

    mylist.splice(itr1, mylist2, ++mylist2.begin(), mylist2.end());
    if(mylist2.empty())                    // true
        cout<< "list2 is empty" <<endl;

    for(list<int>::iterator itr = mylist.begin(); itr != mylist.end(); ++itr)
        cout << *itr << " ";
    cout << endl;

/*
 *  Array
 *  limitations of Array
 *  1. the size of array cannot be changed
 *  2. a and b is actually different types, so a function can take a as parameter cannot take b as parameter
 */
    cout << "---------array-------------" << endl;
    array<int, 3> a = {3, 4, 5};
    array<int, 4> b = {3, 4, 5};
    return 0;
}

