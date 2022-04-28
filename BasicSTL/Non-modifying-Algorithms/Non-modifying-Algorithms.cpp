#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
/*
 *  STL Algorithm Walkthrough:
 *      Non-modifying Algorithms
 *      count, min and max, compare, linear search, attribute
 */

#if 0
//C++ 11 Lambda Function:
num = count_if(vec.begin(), vec.end(), [](int x){ return x < 10;});
//lambda function's effect is equal to the following function
bool lessthan10(int x)
{
    return x < 10;
}

vector<int> vec = {9, 60, 90, 8, 45, 87, 90, 69, 69, 55, 7};
vector<int> vec2 = {9,  60, 70, 8, 45, 87};
vector<int>::iterator itr, itr2;
pair<vector<int>::iterator, vector<int>::iterator> pair_of_itr;
//if you use C++ 03, some algorithms can be found in tr1 or boost

#endif



int main()
{
    vector<int> vec = {9, 60, 90, 8, 45, 87, 90, 69, 69, 55, 7};
    //1. Counting
    //    Algorithm        Data         Operation
    cout << "-----------Counting----------" << endl;
    int n = count(vec.begin(), vec.end(), 69);  //2
    int a = count(vec.begin() + 2, vec.end() - 3, 69);  //1
    int m = count_if(vec.begin(), vec.end(), [](int x){ return x == 69;}); //2
    int b = count_if(vec.begin(), vec.end(), [](int x){ return x < 10;});   //3
    cout << n << " " << a << " " << m << " " << b << " " << endl;
    //2. Min and Max
    cout << "-----------Min and Max---------" << endl;
    auto itr = max_element(vec.begin() + 2, vec.end());    //90
    //It returns the first max value
    auto itr1 = max_element(vec.begin(), vec.end(),
                    [](int x, int y){ return (x % 10) < (y % 10);});  //9
    cout << *itr << " " << *itr1 << endl;
    //Most algorithms have a simple form and generalized form

    auto itr2 = min_element(vec.begin(), vec.end());   //7
    //min_element also have generalized form, no need to present a example again

    auto pair_of_itr = minmax_element(vec.begin(), vec.end(),
                    [](int x, int y){ return (x % 10) < (y % 10);}); //{60, 69}
    //returns a pair, which contains first of min and last of max
    cout << *itr2 << endl;
    cout << *(pair_of_itr.first) << " " << *(pair_of_itr.second) << endl;

    //3. Linear Searching (used when data is not sorted)
    cout << "------------Linear Searching---------" << endl;
    //Returns the first match
    auto itr3 = find(vec.begin(), vec.end(), 55);
    auto itr4 = find_if(vec.begin(), vec.end(), [](int x){ return x > 80;});
    auto itr5 = find_if_not(vec.begin(), vec.end(), [](int x){ return x > 80;});
    auto itr6 = search_n(vec.begin(), vec.end(), 2, 69);  //Consecutive 2 items of 69
    //Generalized form: search_n()
    cout << *itr3 << " " << *itr4 << " " << *itr5 << " " << *itr6 << endl;
    vector<int> sub = {45, 87, 90};
    //search first subrange
    auto itr7 = search(vec.begin(), vec.end(), sub.begin(), sub.end());
    //search last subrange
    auto itr8 = find_end(vec.begin(), vec.end(), sub.begin(), sub.end());
    //Generalized form : search(), find_end()
    cout << *itr7 << " " << * itr8 << endl;

    //Searching any_of
    vector<int> items = {87, 69};
    //Search any one of the item in items
    auto itr9 = find_first_of(vec.begin(), vec.end(), items.begin(), items.end());
    //Search any one of the item in items that satisfy: x == y * 4
    auto itr10 = find_first_of(vec.begin(), vec.end(), items.begin(), items.end(),
                            [](int x, int y){ return x == y + 3;});
    // auto itr10 = find_first_of(vec.begin(), vec.end(), items.begin(), items.end(),
    //                         [](int x, int y){ return x == y * 4;});
    if(itr9 != vec.end()) cout << *itr9 << endl;
    else cout << " not found" << endl;
    if(itr10 != vec.end()) cout << *itr10 << endl;
    else cout << " not found" << endl;
    //Search Adjacent
    auto itr11 = adjacent_find(vec.begin(), vec.end());   //find two adjacent items that are same
    auto itr12 = adjacent_find(vec.begin(), vec.end(), [](int x, int y){ return x == y - 3;}); //find two adjacent items that satisfy: x == y * 4
    //auto itr12 = adjacent_find(vec.begin(), vec.end(), [](int x, int y){ return x == y * 4;});
    if(itr11 != vec.end()) cout << *itr11 << endl;
    else cout << " not found" << endl;
    if(itr12 != vec.end()) cout << *itr12 << endl;
    else cout << " not found" << endl;

    //4. Comparing Ranges
    cout << "------------Comparing Ranges---------" << endl;
    vector<int> vec2 = {9, 90, 60, 45, 8, 90, 87, 69, 69, 7, 55};
    //vector<int> vec2 = {9, 60, 90, 8, 45, 87, 90, 69, 69, 55, 7};
    if(equal(vec.begin(), vec.end(), vec2.begin()))
    {
        cout << "vec and vec2 are same.\n";
    }

    if(is_permutation(vec.begin(), vec.end(), vec2.begin()))
    {
        cout << "vec and vec2 have same items, but in different order.\n";
    }
    //find first difference
    //pair_of_itr.first is an iterator of vec
    //pair_of_itr.second is an iterator of vec2
    auto pair_of_itr1 = mismatch(vec.begin(), vec.end(), vec2.begin());
    cout << *(pair_of_itr1.first) << " " << *(pair_of_itr1.second) << endl;
    //lexicographical comparison: one-by-one comparison with "less than"
    //{1, 2, 3, 5} < {1, 2, 4, 5}
    //{1, 2} < {1, 2, 3}
    cout << lexicographical_compare(vec.begin(), vec.end(), vec2.begin(), vec2.end()) << endl;
    //Generalized forms: equal(), is_permutation, mismatch(), lexicograpgical_compare()
    
    //5. Check Attributes
    cout << "------------Check Attributes---------" << endl;
    cout << is_sorted(vec.begin(), vec.end()) << endl; //Check if vec is sorted
    //itr13 points to first place to where elements are no longer sorted
    //Generalized forms: is_sorted(), is_sorted_until() 
    auto itr13 = is_sorted_until(vec.begin(), vec.end());
    cout << *itr13 << endl;
    //Check if vec is partitioned according to the condition of (x > 80)
    cout << is_partitioned(vec.begin(), vec.end(), [](int x){ return x > 80;}) << endl;
    
    cout << is_heap(vec.begin(), vec.end()) << endl;  //Check if vec is a heap
    //find the first place where it is no longer a heap
    auto itr14 = is_heap_until(vec.begin(), vec.end());
    cout << *itr14 << endl;
    //Generalized forms: is_heap(), is_heap_until()
    
    //6. All, any, none
    //If all of vec is bigger than 80
    cout << all_of(vec.begin(), vec.end(), [](int x){ return x > 80;}) << endl;
    //If any of vec is bigger than 80
    cout << any_of(vec.begin(), vec.end(), [](int x){ return x > 80;}) << endl;
    //If none of vec is bigger than 80
    cout << none_of(vec.begin(), vec.end(), [](int x){ return x > 80;}) << endl;
    

    return 0;
}