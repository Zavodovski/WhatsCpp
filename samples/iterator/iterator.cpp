#if 0
/* 
 *  Iterators
 */ 
//1. Random Access Iterator: vector, deque, array
vector<int> itr;
itr = itr + 5;  //advance itr by 5
itr = itr - 4;
if(itr2 > itr1) ...
++itr;     //faster than itr++
--itr;

//2. Bidirectional Iterator: list, set/multiset, map/multimap
list<int> itr;  //no add/subtract or compare
++itr;
--itr;

//3. Forward Iterator: forward_list
forward_list<int> itr;  
++itr;   //can only be incremented

//Unordered containers provide "at least" forward iterators, some provide bidirectional iterator depends on the implementation of STL;

//4. Input Iterator: read and process values while iterating forward
int x = *itr;

//5. Output Iterator: output values while iterating forward
*itr = 100;
//both Input Iterator and Output Iterator can only move forward, can't move backward

//Every container has a iterator and a const_iterator
set<int>::iterator itr;
set<int>::const_iterator citr;   //Read-only access to container elements

set<int> myset = {2, 4, 5, 1, 9};
for(auto citr = myset.begin(), citr != myset.end(); ++citr)
{
    cout << *citr << endl;
    //*citr = 3      //Error, cannot write data with const_iterator
}
//cbegin(), cend() -> const_iterator
for_each(myset.cbegin(), myset.cend(), MyFunction);  //Only in C++ 11

//Iterator Functions:
advance(itr, 5);     //Move itr forward 5 spots.  for random access iterator it's equal to itr += 5
distance(itr1, itr2) //Measure the distance between itr1 and itr2


#endif

/* 
 *  Iterator Adaptor (Predefined Iterator)
 *  - A special, more powerful iterator
 *  1. Insert iterator
 *  2. Stream iterator
 *  3. Reverse iterator
 *  4. Move iterator (C++ 11)
 */ 
#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<iterator>
using namespace std;

bool isOdd(int i);

int main()
{
    //1. Insert Iterator:
    vector<int> vec1 = {4, 5};
    vector<int> vec2 = {12, 14, 16, 18};
    vector<int>::iterator it = find(vec2.begin(), vec2.end(), 16);
    insert_iterator<vector<int>> i_itr(vec2, it);  //i_itr points to it
    copy(vec1.begin(), vec1.end(),   //source 
        i_itr);                      //destination
        //vec2: {12, 14, 4, 5, 16, 18}
    //other insert iterators: back_insert_iterator, front_insert_iterator
    for(auto it = vec2.begin(); it != vec2.end(); it ++)
        cout << *it << " ";
    cout << endl;

    //2. Stream Iterator
    vector<string> vecs;
    //istream_iterator<string>(cin) -> iterate through the data that comes in from standard input
    //istream_iterator<string>() -> default constructor of istream_iterator represents the end of a stream
    //back_inserter: a function that returns a back_insert_iterator of vec4
    copy(istream_iterator<string>(cin), istream_iterator<string>(), 
            back_inserter(vecs));  //copy everything from standard input and back insert into vec4
    //copy everything inside vec4 to ostream_iterator of standard output and each element is separated with space
    copy(vecs.begin(), vecs.end(), ostream_iterator<string>(cout, " "));

    //Make it one statement
    copy(istream_iterator<string>(cin), istream_iterator<string>(), ostream_iterator<string>(cout, " "));
    cout << endl;
    //3. Reverse Iterator (to traverse a container in reverse order)
    vector<int> vec0 = {4, 5, 6, 7};
    reverse_iterator<vector<int>::iterator> ritr;
    //rbegin points to the last element of the container
    //rend() points to the element before the first element in the container 
    for(auto ritr = vec0.rbegin(); ritr != vec0.rend(); ritr ++)
        cout << *ritr << " ";  //prints: 7, 6, 5, 4
    cout << endl;

/* 
 *  Algorithms
 *  - mostly loops
 */ 
    vector<int> vec = {4, 2, 5, 1, 3, 9};
    vector<int>::iterator itr = min_element(vec.begin(), vec.end()); //itr -> 1
    //Note 1: Algorithm always process ranges in a half-open way: [begin, end)
    sort(vec.begin(), itr);   //vec: {2, 4, 5, 1, 3, 9}

    for(auto it = vec.begin(); it != vec.end(); it ++)
        cout << *it << " ";
    cout << endl;

    reverse(itr, vec.end());  //vec: {2, 4, 5, 9, 3, 1} itr -> 9

    for(auto it = vec.begin(); it != vec.end(); it ++)
        cout << *it << " ";
    cout << endl;

    //Note 2:
    vector<int> vect(3);
    copy(itr, vec.end(),    //Source 
            vect.begin());  //Destination
            //vect needs to have at least space for 3 elements
            //otherwise the result is undefined behavior(this is an example that the STL sacrifice safety in favor of efficiency and flexibility)
            //so we need to be careful when using this kind of function
    //to overcome the safety issue, STL provides insert iterator
    
    //Note 3:
    vector<int> vec3;
    copy(itr, vec.end(), back_inserter(vec3));  //Inserting instead of overwriting, insert the item between itr and end one by one
                        //back_insert_iterator  //safe but not efficient because only insert one item at a time
    
    vec3.insert(vec3.end(), itr, vec.end());    //efficient and safe because it only inserts once
    
    //Note 4: Algorithm with function
    vector<int> vec4 = {2, 4, 5, 9, 2};
    vector<int>::iterator itr_odd = find_if(vec.begin(), vec.end(), isOdd); //itr -> 5
    cout << *itr_odd << endl;
    //Note 5: Algorithm with native C++ array
    int arr[4] = {6, 3, 7, 4};
    sort(arr, arr + 4);
    return 0;                       
}

bool isOdd(int i)
{
    return i % 2;
}