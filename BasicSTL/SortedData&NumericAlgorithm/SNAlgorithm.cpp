#include<iostream>
#include<vector>
#include<algorithm>
#include<numeric>
using namespace std;
/*
 *  Sorted Data Algorithms
 *      -Algorithms that require data being pre-sorted
 *      -Binary search, merge, set operations
 */

//Note: Every sorted data algorithm has a generalized form with a same name

int main()
{
    vector<int> vec = {8, 9, 9, 9, 45, 87, 90};
    //1. Binary Search
    cout << "---------------BinarySearch---------------" << endl;
    //Search elements
    bool found = binary_search(vec.begin(), vec.end(), 9);  //check if 9 is in vec
    cout << found << endl;
    vector<int> s = {9, 45, 66};
    found = includes(vec.begin(), vec.end(),  //Range #1
                    s.begin(), s.end());      //Range #2
    cout << found << endl;
    //Return true if all elements of s is included in vec
    //both vec and s must be sorted

    //search position
    auto itr = lower_bound(vec.begin(), vec.end(), 9); //vec[1]
        //find the first position where 9 could be inserted and still keep the sorting
    cout << *itr << endl;
    itr = upper_bound(vec.begin(), vec.end(), 9);   //vec[4]
        //find the last position where 9 could be inserted and still keep the sorting
    cout << *itr << endl;
    auto pair_of_itr = equal_range(vec.begin(), vec.end(), 9);
        //returns both first and last position
    cout << *(pair_of_itr.first) << " " << *(pair_of_itr.second) << endl;
    
    //2. Merge
    cout << "---------------Merge---------------" << endl;
    vec = {8, 9, 9, 10};
    vector<int> vec2 = {7, 9, 10};
    vector<int> vec_out = {0, 0, 0, 0, 0, 0, 0};
    merge(vec.begin(), vec.end(),       //Input Range #1
            vec2.begin(), vec2.end(),   //Input Range #2
            vec_out.begin());           //Output               
        //Both vec and vec2 should be sorted (same for the set operation)
        //Nothing is dropped, all duplicates are kept.
        //vec_out: {7, 8, 9, 9, 9, 10, 10}
    for(auto it = vec_out.begin(); it != vec_out.end(); it ++)
        cout << *it << " ";
    cout << endl;
    vec = {1, 2, 3, 4, 1, 2, 3, 4, 5};  //Both part of vec are already sorted
    inplace_merge(vec.begin(), vec.begin() + 4, vec.end());
        //vec: {1, 1, 2, 2, 3, 3, 4, 4, 5} - One step of merge sort
    for(auto it = vec.begin(); it != vec.end(); it ++)
        cout << *it << " ";
    cout << endl;

    //3. Set operations
    //  - Both vec and vec3 should be sorted
    //  - The resulted data is also sorted
    cout << "---------------Set operations---------------" << endl;
    vec = {8, 9, 9, 10};
    vec2 = {7, 9, 10};
    vec_out = {0, 0, 0, 0, 0, 0, 0};
    set_union(vec.begin(), vec.end(),       //Input Range #1
                vec2.begin(), vec2.end(),   //Input Range #2
                vec_out.begin());          //Output
    //if X  is in both vec and vec2, only one X is kept in vec_outs
    //vec_out: {7, 8, 9, 9, 10}
    for(auto it = vec_out.begin(); it != vec_out.end(); it ++)
        cout << *it << " ";
    cout << endl;
    
    vec_out = {0, 0, 0, 0, 0, 0, 0};
    set_intersection(vec.begin(), vec.end(),       //Input Range #1
                vec2.begin(), vec2.end(),   //Input Range #2
                vec_out.begin());          //Output
    //Only the items that are in both vec and vec2 are saved in vec_out
    //vec_out: {9, 10, 0, 0, 0}
    for(auto it = vec_out.begin(); it != vec_out.end(); it ++)
        cout << *it << " ";
    cout << endl;

    vec = {8, 9, 9, 10};
    vec2 = {7, 9, 10};
    vec_out = {0, 0, 0, 0, 0, 0, 0};
    set_difference(vec.begin(), vec.end(),       //Input Range #1
                vec2.begin(), vec2.end(),   //Input Range #2
                vec_out.begin());          //Output
    //Only the items that are in vec but not in vec2 are saved in vec_out
    //vec_out: {8, 9, 0, 0, 0}
    for(auto it = vec_out.begin(); it != vec_out.end(); it ++)
        cout << *it << " ";
    cout << endl;
    vec = {8, 9, 9, 10};
    vec2 = {7, 9, 10};
    vec_out = {0, 0, 0, 0, 0, 0, 0};
    set_symmetric_difference(vec.begin(), vec.end(),       //Input Range #1
                vec2.begin(), vec2.end(),   //Input Range #2
                vec_out.begin());          //Output
    //vec_out has items from either vec or vec2, but not from both
    //vec_out: {7, 8, 9, 0, 0}
    for(auto it = vec_out.begin(); it != vec_out.end(); it ++)
        cout << *it << " ";
    cout << endl;

    /*
     *  Numeric Algorithms (in <numeric>)
     *      -Accumulate, inner product, partial sum, adjacent difference
     */

    //1. Accumulate
    cout << "---------------Accumulate---------------" << endl;
    int x = accumulate(vec.begin(), vec.end(), 10);
    cout << x << endl;
    //10 + vec[0] + vec[1] + vec[2] + ...
    x = accumulate(vec.begin(), vec.end(), 10, multiplies<int>());
    //10 * vec[0] * vec[1] * vec[2] * ...
    cout << x << endl;

    //2. Inner Product
    vec = {9, 60, 70, 8, 45, 87, 90};
    vec2 = {0, 0, 0, 0, 0, 0, 0};
    x = inner_product(vec.begin(), vec.begin() + 3,    //Range #1 
                        vec.end() - 3,                 //Range #2
                        10);                           //Init Value
    //10 + vec[0]*vec[4] + vec[2]*vec[5] + vec[3]*vec[6]
    cout << x << endl;
    x = inner_product(vec.begin(), vec.begin() + 3,    //Range #1 
                        vec.end() - 3,                 //Range #2
                        10,                            //Init Value
                        multiplies<int>(),
                        plus<int>());
    cout << x << endl;
    //10 * (vec[0]+vec[4]) * (vec[2]+vec[5]) * (vec[3]+vec[6])
    //3. Partial Sum
    cout << "---------------Partial Sum---------------" << endl;
    partial_sum(vec.begin(), vec.end(), vec2.begin());
    //vec2[0] = vec[0]
    //vec2[1] = vec[0] + vec[1]
    //vec2[2] = vec[0] + vec[1] + vec[2]
    //vec2[3] = vec[0] + vec[1] + vec[2] + vec[3]
    for(auto it = vec2.begin(); it != vec2.end(); it ++)
        cout << *it << " ";
    cout << endl;
    partial_sum(vec.begin(), vec.end(), vec2.begin(), multiplies<int>());
    //vec2[0] = vec[0]
    //vec2[1] = vec[0] * vec[1]
    //vec2[2] = vec[0] * vec[1] * vec[2]
    //vec2[3] = vec[0] * vec[1] * vec[2] * vec[3]
    for(auto it = vec2.begin(); it != vec2.end(); it ++)
        cout << *it << " ";
    cout << endl;
    //4. Adjacent difference
    cout << "---------------Adjacent difference---------------" << endl;
    adjacent_difference(vec.begin(), vec.end(), vec2.begin());
    //vec2[0] = vec[0]
    //vec2[1] = vec[1] - vec[0]
    //vec2[2] = vec[2] - vec[1]
    //vec2[3] = vec[3] - vec[2]
    for(auto it = vec2.begin(); it != vec2.end(); it ++)
        cout << *it << " ";
    cout << endl;
    adjacent_difference(vec.begin(), vec.end(), vec2.begin(), plus<int>());
    for(auto it = vec2.begin(); it != vec2.end(); it ++)
        cout << *it << " ";
    cout << endl;
    return 0;
}

