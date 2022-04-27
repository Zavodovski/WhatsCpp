#include<iostream>
#include<set>   //set && multiset
#include<map>   //map && multimap
using namespace std;
/*
 * Associative containers
 * always sorted, default criteria is <
 * no push_back(), push_front()
 */

int main()
{
/*
 *  Set/Multiset
 *  Properties of Set
 *  1. fast insert/search : O(log(n))
 *  2. set no duplicates but multiset allows duplicates
 *  3. traversing is low (compared to vector & deque)
 *  4. no random access, no [] operator
 *  
 */
    cout << "---------set && multiset-------------" << endl;
    set<int> myset;
    myset.insert(3);     //myset: {3}
    myset.insert(1);     //myset: {1, 3}
    myset.insert(7);     //myset: {1, 3, 7}, O(log(n))

    set<int>::iterator setit;
    setit = myset.find(7);   // O(log(n)), it points to 7
                          //Sequence containers don't even have find member function
    //insert function also have a return parameter, its type is pair
    //the first element is iterator points the insert element whether the insertion is successful or failed  
    //the second is a boolean which is true if the insertion is successful(the element not exists in the set) or false if the insertion is failed(the element already exists in the set)
    pair<set<int>::iterator, bool> ret;
    ret = myset.insert(3);//no element inserted
    if(ret.second == false)
        setit = ret.first;   //it now points to element 3
    //insert function has a iterator parameter but not means insert the element in front of the iterator
    //it use as a hint to find the location where 9 needs to be inserted
    myset.insert(setit, 9);  //myset: {1, 3, 7, 9}  if the hint is good enough then O(log(n))->O(1)
                          //it points to 3
    //erase can take either the iterator or the element value as parameter
    //none of the sequence containers provide this kind of erase
    myset.erase(setit);      //myset: {1, 7, 9}
    myset.erase(7);       //myset: {1, 9}

    //traversing
    for(auto it = myset.begin(); it != myset.end(); it ++)
        cout << (*it) << " ";
    cout << endl;

    //multiset is a set that allows duplicated items
    multiset<int> mymultiset;
    //set/multiset: value of the elements cannot be modified
    set<int>::iterator it = myset.find(9);
    //*it = 10; //*it is read-only

/*
 *  Map/Multismap
 *  Properties of Map
 *  1. fast insert/search : O(log(n))
 *  2. map no duplicated key but multimap allows duplicated key
 *  3. traversing is low (compared to vector & deque)
 *  4. map have [] but multimap no random access, no [] operator
 *  
 */
    cout << "---------map && multimap-------------" << endl;
    map<char, int> mymap;
    mymap.insert(pair<char, int>('a', 100));
    mymap.insert(make_pair('z', 200)); //convenient function make_pair
    map<char, int>::iterator mapit = mymap.begin();
    mymap.insert(mapit, pair<char, int>('b', 300));  //"it" is a hint
    mapit = mymap.find('z');  //O(log(n))

    //traversing
    for(auto it = mymap.begin(); it != mymap.end(); it ++)
        cout << (*it).first << "=>" << (*it).second <<endl;
    //multimap is a map that allows duplicated keys
    multimap<char, int> mymultimap;
    //map/multimap --keys cannot be modified, actual type of *it: pair<const char, int>
    //(*mapit).first = 'd';  //Error
    return 0;
}
