#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;


bool lsb_less(int x, int y)
{
    return (x % 10) < (y % 10);
}

bool lessthan10(int i)
{
    return (i < 10);
}
int main()
{
    /*
     *  Sortings in STL
     */
    //Sorting algorithms requires random access iterators:
    //  vector, deque, container, array, native array
    vector<int> vec = {9, 1, 10, 2, 45, 3, 90, 4, 9, 5, 8};
    
    sort(vec.begin(), vec.end()); //sort with operator <
        //vec: 1, 2, 3, 4, 5, 8, 9, 9, 10, 45, 90
    for(auto it = vec.begin(); it != vec.end(); it ++)
        cout << *it << " ";
    cout << endl;
    sort(vec.begin(), vec.end(), lsb_less); //sort with lsb_less()
        //vec: 10, 90, 1, 2, 3, 4, 45, 5, 8, 9, 9
    for(auto it = vec.begin(); it != vec.end(); it ++)
        cout << *it << " ";
    cout << endl;

    //sometime we don't need complete sorting

    //Problem #1: Finding top 5 students according to the test scores.
    //
    // -partial sort
    cout <<"---------------Problem #1---------------"<< endl;
    vec = {9, 60, 70, 8, 45, 87, 90,69, 69, 55, 7};

    partial_sort(vec.begin(), vec.begin() + 5, vec.end(), greater<int>());
    //vec : 90 87 70 69 69 8 9 45 60 55 7
    //partial_sort(vec.begin(), vec.begin() + 5, vec.end());
    for(auto it = vec.begin(); it != vec.end(); it ++)
        cout << *it << " ";
    cout << endl;

    //Problem 2： Finding top 5 students according to their score, but I don't care their order
    cout <<"---------------Problem #2---------------"<< endl;
    vec = {9, 60, 70, 8, 45, 87, 90,69, 69, 55, 7};
    nth_element(vec.begin(), vec.begin() + 5, vec.end(), greater<int>());
    for(auto it = vec.begin(); it != vec.end(); it ++)
        cout << *it << " ";
    cout << endl;

    //Problem #3: Move the students whose score is less than 10 to the front
    cout <<"---------------Problem #3---------------"<< endl;
    vec = {9, 60, 70, 8, 45, 87, 90,69, 69, 55, 7};

    partition(vec.begin(), vec.end(), lessthan10);
    for(auto it = vec.begin(); it != vec.end(); it ++)
        cout << *it << " ";
    cout << endl;
        //vec: 8 7 9 90 69 60 55 45 70 87 69
    //To preserve the original order within each partition
    vec = {9, 60, 70, 8, 45, 87, 90,69, 69, 55, 7};
    stable_partition(vec.begin(), vec.end(), lessthan10);
    for(auto it = vec.begin(); it != vec.end(); it ++)
        cout << *it << " ";
    cout << endl;

    //Heap Algorithms
    //
    //Heap
    //1. first element is always the largest
    //2. add/remove takes O(log(n)) time
    cout <<"---------------Heap Algorithm---------------"<< endl;
    vec = {9, 1, 10, 2, 45, 3, 90, 4, 9, 5, 8};
    make_heap(vec.begin(), vec.end());
        //vec: 90 45 10 9 8 3 9 4 2 5 1
    for(auto it = vec.begin(); it != vec.end(); it ++)
        cout << *it << " ";
    cout << endl;
    //Remove the largest element
    pop_heap(vec.begin(), vec.end()); //1. swap vec[0] with last item vec[size - 1]
                                      //2. heapify [vec.begin(), vec.end() - 1]
        //vec: 45 9 10 4 8 3 9 1 2  5 90
    for(auto it = vec.begin(); it != vec.end(); it ++)
        cout << *it << " ";
    cout << endl;
    vec.pop_back();   //Remove the last item(the largest one)
        //vec: 45 9 10 4 8 3 9 1 2 5
    for(auto it = vec.begin(); it != vec.end(); it ++)
        cout << *it << " ";
    cout << endl;
    //add a new element:
    vec.push_back(100);
    push_heap(vec.begin(), vec.end());  //heapify the last item in vec
        //vec: 100 45 10 4 9 3 9 1 2 5 8
    for(auto it = vec.begin(); it != vec.end(); it ++)
        cout << *it << " ";
    cout << endl;

    //Heap Sorting
    vec = {9, 1, 10, 2, 45, 3, 90, 4, 9, 5, 8};
    make_heap(vec.begin(), vec.end());
    sort_heap(vec.begin(), vec.end());
        //vec: 1 2 3 4 5 8 9 9 10 45 100
        //Note: sort_heap can only work on a heap, so the vec has to be a heap first
    for(auto it = vec.begin(); it != vec.end(); it ++)
        cout << *it << " ";
    cout << endl;
    return 0;
}