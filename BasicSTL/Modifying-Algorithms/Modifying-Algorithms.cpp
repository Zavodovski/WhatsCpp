#include<iostream>
#include<vector>
#include<algorithm>
#include<random>
using namespace std;
/*
 *  Algorithm Walkthrough:
 *      Value-changing Algorithm - Changes the element values
 *      copy, move, transform, swap, fill, replace, remove
 */

int main()
{
    vector<int> vec = {9, 60, 70, 8, 45, 87, 90};   //7 items
    vector<int> vec2 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};  //11 items
    vector<int>::iterator itr, itr2;
    pair<vector<int>::iterator, vector<int>::iterator> pair_of_itr;
    //1. Copy
    cout << "----------------copy----------------" << endl;
    //need to make true vec2 at least as big as vec otherwise undefined behavior
    copy(vec.begin(), vec.end(),    //Source
            vec2.begin());          //Destination
    for(auto it = vec2.begin(); it != vec2.end(); it ++)  
        cout << *it << " ";
    cout << endl;
    copy_if(vec.begin(), vec.end(), //Source 
            vec2.begin(),             //Destination
            [](int x){ return x > 80;}); //Condition
        //vec2: {87, 90, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    for(auto it = vec2.begin(); it != vec2.end(); it ++)  
        cout << *it << " ";
    cout << endl;
    copy_n(vec.begin(), 4, vec2.begin());
        //vec2: {9, 60, 70, 8, 0, 0, 0, 0, 0, 0, 0}
    for(auto it = vec2.begin(); it != vec2.end(); it ++)  
        cout << *it << " ";
    cout << endl;
    copy_backward(vec.begin(), vec.end(),   //Source 
            vec2.end());                    //Destination
        //vec2: {0, 0, 0, 0, 9, 60, 70, 8, 45, 87, 90}
    for(auto it = vec2.begin(); it != vec2.end(); it ++)  
        cout << *it << " ";
    cout << endl;

    //2. Move
    cout << "----------------move----------------" << endl;
    vector<string> vecs = {"apple", "orange", "pear", "grape"};  //4 items
    vector<string> vecs2 = {"", "", "", "", "", ""};    // 6 items
    move(vecs.begin(), vecs.end(), vecs2.begin());
    //vecs: {"", "", "", ""}   //Undefined
    //vecs2" {"apple", "orange", "pear", "grape", "", ""};
    for(auto it = vecs.begin(); it != vecs.end(); it ++)
        cout << *it << " ";
    cout << endl;
    for(auto it = vecs2.begin(); it != vecs2.end(); it ++)
        cout << *it << " ";
    cout << endl;
    //If move semantics are defined for the element type, elements are moved over, 
    //otherwise they are copied over with copy constructor, just like copy().
    //for example for int type move is the same as copy
    vecs = {"apple", "orange", "pear", "grape"};  //4 items
    vecs2 = {"", "", "", "", "", ""};    // 6 items
    move_backward(vecs.begin(), vecs.end(), vecs2.end());
    //vecs2: {"", "", "apple", "orange", "pear", "grape"};
    for(auto it = vecs2.begin(); it != vecs2.end(); it ++)
        cout << *it << " ";
    cout << endl;

    //3. Transform
    cout << "---------------transform---------------" << endl;
    vec = {9, 60, 70, 8, 45, 87, 90};    //7 items
    vec2 = {9, 60, 70, 8, 54, 78, 90};    //7 items
    vector<int> vec3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};   //11 items

    transform(vec.begin(), vec.end(),    //Source
                vec3.begin(),            //Destination
                [](int x){ return x - 1;});  //Operation
    for(auto it = vec3.begin(); it != vec3.end(); it ++)
        cout << *it << " ";
    cout << endl;
    transform(vec.begin(), vec.end(),    //Source #1
                vec2.begin(),            //Source #2
                vec3.begin(),            //Destination
                [](int x, int y){ return x + y;});  //Operation
                //Add items from vec and vec2 and save in vec3
                //vec3[0] = vec[0] + vec2[0]
                //vec3[1] = vec[1] + vec2[1]
                // ...
    for(auto it = vec3.begin(); it != vec3.end(); it ++)
        cout << *it << " ";
    cout << endl;
    //4. Swap - two way copying
    cout << "---------------Swap---------------" << endl;
    swap_ranges(vec.begin(), vec.end(), vec2.begin());
    for(auto it = vec.begin(); it != vec.end(); it ++)
        cout << *it << " ";
    cout << endl;
    for(auto it = vec2.begin(); it != vec2.end(); it ++)
        cout << *it << " ";
    cout << endl;

    //5. Fill
    cout << "---------------Fill---------------" << endl;
    vec = {0, 0, 0, 0, 0};
    fill(vec.begin(), vec.end(), 9);   //vec: {9, 9, 9, 9, 9}
    for(auto it = vec.begin(); it != vec.end(); it ++)
        cout << *it << " ";
    cout << endl;
    vec = {0, 0, 0, 0, 0};
    fill_n(vec.begin(), 3, 9);         //vec: {9, 9, 9, 0, 0}
    for(auto it = vec.begin(); it != vec.end(); it ++)
        cout << *it << " ";
    cout << endl;
    vec = {0, 0, 0, 0, 0};
    generate(vec.begin(), vec.end(), rand);
    for(auto it = vec.begin(); it != vec.end(); it ++)
        cout << *it << " ";
    cout << endl;
    vec = {0, 0, 0, 0, 0};
    generate_n(vec.begin(), 3, rand);
    for(auto it = vec.begin(); it != vec.end(); it ++)
        cout << *it << " ";
    cout << endl;

    //6. Replace
    cout << "---------------Replace---------------" << endl;
    vec = {9, 9, 9, 9, 6, 6, 6, 87, 45, 7, 90};
    replace(vec.begin(), vec.end(),     //Data Range
            6,                          //Old value condition
            9);
    for(auto it = vec.begin(); it != vec.end(); it ++)
        cout << *it << " ";
    cout << endl;
    replace_if(vec.begin(), vec.end(),  //Data Range 
            [](int x){ return x > 80;}, //Old value condition
            9);                         //new value
    for(auto it = vec.begin(); it != vec.end(); it ++)
        cout << *it << " ";
    cout << endl;
    vec = {9, 9, 9, 9, 6, 6, 6, 87, 45, 7, 90};
    replace_copy(vec.begin(), vec.end(),//Source 
            vec3.begin(),               //Destination
            6,                          //Old value condition
            9);                         //new value
    for(auto it = vec3.begin(); it != vec3.end(); it ++)
        cout << *it << " ";
    cout << endl;
    //Generalized form: replace_copy_if()

    //7. Remove
    cout << "---------------Remove---------------" << endl;
    vec = {9, 9, 9, 9, 3, 3, 3, 87, 45, 7, 90};
    remove(vec.begin(), vec.end(), 3);    //Remove all 3
    for(auto it = vec.begin(); it != vec.end(); it ++)
        cout << *it << " ";
    cout << endl;
    remove_if(vec.begin(), vec.end(), [](int x){ return x > 80;});
        //Remove items bigger than 80
    for(auto it = vec.begin(); it != vec.end(); it ++)
        cout << *it << " ";
    cout << endl;
    vec = {9, 9, 9, 9, 3, 3, 3, 87, 45, 7, 90};
    remove_copy(vec.begin(), vec.end(),     //Source
                vec3.begin(),               //Destination
                3);                         //Condition
    for(auto it = vec3.begin(); it != vec3.end(); it ++)
        cout << *it << " ";
    cout << endl;
    //Remove all 3 and the remains items to vec2
    //Generalized form: remove_copy_if()
    vec = {9, 9, 9, 9, 3, 3, 3, 87, 45, 7, 90};
    unique(vec.begin(), vec.end());         //Remove consecutive equal elements
    for(auto it = vec.begin(); it != vec.end(); it ++)
        cout << *it << " ";
    cout << endl;
    vec = {9, 9, 9, 9, 3, 3, 3, 87, 45, 7, 90};
    unique(vec.begin(), vec.end(), less<int>());
    for(auto it = vec.begin(); it != vec.end(); it ++)
        cout << *it << " ";
    cout << endl;
        //Remove elements whose previous element is less than itself
    vec = {9, 9, 9, 9, 3, 3, 3, 87, 45, 7, 90};
    unique_copy(vec.begin(), vec.end(), vec3.begin());
        //Remove consecutive equal elements, and then copy the uniquified items to vec2
    for(auto it = vec3.begin(); it != vec3.end(); it ++)
        cout << *it << " ";
    cout << endl;

    /*
     *  Order-Changing Algorithms:
     *      -reverse, rotate, permute, shuffle
     * 
     *  They changes the order of elements in container, but not necessarily the elements themselves
     * 
     */

    vec = {9, 60, 70, 8, 45, 87, 90};   //7 items
    vec2 = {0, 0, 0, 0, 0, 0, 0};       //7 items
    //1. Reverse
    cout << "---------------Reverse---------------" << endl;
    //vec: {9, 87, 45, 8, 70, 60, 90};  //7 items
    reverse(vec.begin() + 1, vec.end() - 1);
    for(auto it = vec.begin(); it != vec.end(); it ++)
        cout << *it << " ";
    cout << endl;
    //vec2: {87, 45,  8, 70, 60, 0, 0}
    reverse_copy(vec.begin() + 1, vec.end() - 1, vec2.begin());
        //copy the vec to vec2 in reverse order
        //vec is unchanged
    for(auto it = vec.begin(); it != vec.end(); it ++)
        cout << *it << " ";
    cout << endl;
    for(auto it = vec2.begin(); it != vec2.end(); it ++)
        cout << *it << " ";
    cout << endl;
    //2. Rotate
    cout << "---------------Rotate---------------" << endl;
    vec = {9, 60, 70, 8, 45, 87, 90};   //7 items
    vec2 = {0, 0, 0, 0, 0, 0, 0};       //7 items
    //vec: {8, 45, 87, 90, 9, 60, 70}
    //rotate the vec until vec.begin() + 3 becomes the first item
    rotate(vec.begin(), vec.begin() + 3, vec.end());
    for(auto it = vec.begin(); it != vec.end(); it ++)
        cout << *it << " ";
    cout << endl;
    rotate_copy(vec.begin(), vec.begin() + 3, vec.end(),    //Source
                vec2.begin());                              //Destination
        //copy the vec to vec2 in rotated order
        //vec is unchanged
    for(auto it = vec.begin(); it != vec.end(); it ++)
        cout << *it << " ";
    cout << endl;
    for(auto it = vec2.begin(); it != vec2.end(); it ++)
        cout << *it << " ";
    cout << endl;

    //3. Permute
    cout << "---------------Permute---------------" << endl;
    vec = {9, 60, 70, 8, 45, 87, 90};   //7 items
    next_permutation(vec.begin(), vec.end());
        //Lexicographically next greater permutation
    for(auto it = vec.begin(); it != vec.end(); it ++)
        cout << *it << " ";
    cout << endl;
    vec = {9, 60, 70, 8, 45, 87, 90};
    prev_permutation(vec.begin(), vec.end());
        //Lexicographically next smaller permutation
    for(auto it = vec.begin(); it != vec.end(); it ++)
        cout << *it << " ";
    cout << endl;
        
    //Lexicographically order
    // {1, 2, 3, 5} < {1, 2, 4, 4}
    //{1, 2} < {1, 2, 3}
    //sorted in ascending order: {8, 9, 45, 60, 70, 87, 90} -Lexicographically smallest
    //sorted in descending order: {90, 87, 70, 60, 45, 9, 8} -Lexicographically greatest
    //Generalized form: next_permutation(), prev_permutation()
    
    //4. Shuffle
    //  rearrange the elements randomly
    // (swap each element with a randomly selected element)
    cout << "---------------Shuffle---------------" << endl;
    random_shuffle(vec.begin(), vec.end());
    for(auto it = vec.begin(); it != vec.end(); it ++)
        cout << *it << " ";
    cout << endl;
    // random_shuffle(vec.begin(), vec.end(), rand());
    // for(auto it = vec.begin(); it != vec.end(); it ++)
    //     cout << *it << " ";
    // cout << endl;
    //C++ 11
    shuffle(vec.begin(), vec.end(), default_random_engine());
        //Better random number generation
    for(auto it = vec.begin(); it != vec.end(); it ++)
        cout << *it << " ";
    cout << endl;
    return 0;
}