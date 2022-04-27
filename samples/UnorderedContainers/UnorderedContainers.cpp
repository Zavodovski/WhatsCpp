#include<iostream>
#include<vector>
#include<unordered_set>
#include<unordered_map>
using namespace std;

/*  properties of unordered containers
 *  1. fastest search/insert at any place: O(1)
 *     Associative container takes O(log(n))
 *     vector, deque takes O(n)
 *     list takes O(1) to insert, O(n) to search
 *  2. Unordered set/multiset: element value cannot be changed
 *     Unordered map/multimap: element key cannot be changed
 *     unordered multiset: unordered set that allows duplicated elements
       unordered map: unordered set of pairs
       unordered multimap: unordered map that allows duplicated keys
 */

int main()
{
/*
 *  unordered_set
 */
    cout << "---------unordered_set-------------" << endl;
    unordered_set<string> myset = {"red", "green", "blue"};
    unordered_set<string>::const_iterator itr = myset.find("green"); // amortized O(1)
    if(itr != myset.end())    //Important check
         cout << *itr << endl;
    myset.insert("yellow");   //O(1)
    //use with other containers
    vector<string> vec = {"purple", "pink"};
    myset.insert(vec.begin(), vec.end());

    //Hash table specific APIs:
    cout << "load_factor = " << myset.load_factor() << endl;
    string x = "red";
    cout << x << "is in bucket #" << myset.bucket(x) << endl;
    cout << "Total bucket #" << myset.bucket_count() << endl;
    //hash collision -> performance degrade

/*
 *  Assocaitive array
 *  map and unordered_map
 */
/*
 *  Notes about Assocaitive array
 *  1. Search time: unordered_map, O(1); map, O(log(n));
 *  2. unordered_map may degrade to O(n), while map is stable(guaranteed O(log(n))), which is important for real-time system 
 *  3. can't use multimap and unordered_multimap, they don't have [] operator
 */

    cout << "---------unordered_map-------------" << endl;
    unordered_map<char, string> day = {{'S', "Sunday"}, {'M', "Monday"}};

    cout << day['S'] << endl;   //No range check
    cout << day.at('S') << endl; //had range check

    vector<int> vec1 = {1, 2, 3};
    //vec[5] = 5;  //Compile Error
    day['W'] = "Wednesday";  //insert {'W', "Wednesday"}
    day.insert(make_pair('F', "Friday"));  //insert {'F', "Friday"}    
    //insert function cannot modify the existing element while the operator [] can
    //operator [] provide write access to the container, see the function below
    day.insert(make_pair('M', "MONDAY"));  //fail to modify, it's an unordered_map
    day['M'] = "MONDAY";     //Succeed to modify


    /*  Another way of categorizing containers:
 *  1. Array based containers: vector, deque
 *        
 *     
 *  2. Node based containers invalidates pointers
 *     - Native pointers, iterators, references
 *     
 */
    vector<int> myvec = {1, 2, 3, 4};
    int* p = &myvec[2];  //p points to 3
    myvec.insert(myvec.begin(), 0);
    cout << *p << endl;    //2, or ?

    return 0;
}

void foo(const unordered_map<char, string>& m)
{
    //cout << m['S'] << endl; //when the compiler see [], it assume you modify the map and thus CE
    //m['S'] = "Sunday"; //operator may modify the element and thus compiler error
    //Correct Way to print m['S']
    auto itr = m.find('S');
    if(itr != m.end())
        cout << (*itr).first << " " << (*itr).second << endl;

}

