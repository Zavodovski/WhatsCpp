#include<iostream>
#include<vector>
#include<list>
#include<algorithm>
#include<functional>
#include<set>
using namespace std;

//Print contents of a container
template<class T>
void print(T t, string msg)
{
    cout << msg << " { ";
    for(typename T::iterator it = t.begin(); it != t.end(); it ++)
    {
        cout << *it << ",";
    }
    cout << " } " << endl;
}


// bool equalOne(int e)
// {
//     if(e == 1)
//     {
//         cout << e << " will be removed" << endl;
//         return true;
//     }
//     return false;
// }

bool equalOne(int e, int q)
{
    if(e == q)
    {
        cout << e << " will be removed" << endl;
        return true;
    }
    return false;
}


int main()
{
    vector<int> c = {1, 4, 6, 1, 1, 1, 1, 12, 18, 16}; //Remove 1's
    print(c, "Original:");

    // for(vector<int>::iterator itr = c.begin(); itr != c.end(); itr ++)
    // {
    //     if(*itr == 1)
    //     {
    //         itr = c.erase(itr);
    //     }
    //     else
    //     {
    //         itr ++;
    //     }
    // }//Complexity: O(n * m) every time a element is, all the items after that are moved one item forward toward the front
    // print(c, "After erase:");

    // remove(c.begin(), c.end(), 1);  //Complexity: O(n)
    // print(c, "After remove():");

    auto itr = remove(c.begin(), c.end(), 1);
    c.erase(itr, c.end());
    print(c, "After remove():");

    //c.shrink_to_fit();  //C++ 11 released unused memory => size = capacity
    vector<int>(c).swap(c); //the same as last line, old C++ standatd
    cout << "capacity(): " << c.capacity() << endl;
    
    //Remove elements from a list
    list<int> l = {1, 4, 6, 1, 1, 1, 1, 12, 18, 16};
    print(l, "Original:");

    //auto itrl = remove(l.begin(), l.end(), 1);  //Complexity: O(n)
    // l.erase(itrl, l.end());
    // print(l, "after erase():");

    l.remove(1);  //efficient way
    print(l, "after remove():");

    //Remove elements from an associative container or unordered container
    multiset<int> s = {1, 4, 5, 1, 1, 1, 1, 12, 18, 16};  //Remove 1's
    print(s, "Original:");

    //auto itrs = remove(s.begin(), s.end(), 1);  //Complexity: O(n) compile error
    // s.erase(itrs, s.end());
    // print(s, "after erase():");
    s.erase(1);  //O(log(n))
    print(s, "after erase():");

    /*
 *  Summary of Removing Elements:
 *      1. Vector or Deque: algorithm remove() followed by erase()
 *      2. List: member function remove()
 *      3. Associative Container or Unordered container: erase()
 */
    //Remove and do something else?
    //Print a message whenever an item is removed.
    multiset<int> m = {1, 4, 6, 1, 1, 1, 1, 12, 18, 16};

    // for(multiset<int>::iterator itrm = m.begin(); itrm != m.end(); itrm ++)
    // {
    //     if(*itrm == 1)
    //     {
    //         m.erase(itrm);
    //         cout << "Erased one item of " << *itrm << endl;
    //     }
    // }
    // print(m, "after erase:");


    for(multiset<int>::iterator itrm = m.begin(); itrm != m.end(); )
    {
        if(*itrm == 1)
        {
            cout << "Erased one item of " << *itrm << endl;
            m.erase(itrm ++);
        }
        else
            itrm ++;
    }
    print(m, "after erase:");

    vector<int> v = {1, 4, 6, 1, 1, 1, 1, 12, 18, 16};

    for(vector<int>::iterator itrv = v.begin(); itrv != v.end(); )
    {
        if(*itrv == 1)
        {
            cout << "Erased one item of " << *itrv << endl;
            itrv = v.erase(itrv);
        }
        else
            itrv ++;
    }
    print(v, "after erase:");

/*
 *  Summary:
 *      Sequence container and unordered container: itr = c.erase(itr);
 *      Associative container:  c.erase(itr ++)
 */

    vector<int> o = {1, 4, 6, 1, 1, 1, 1, 12, 18, 16};
    //auto itro = remove_if(o.begin(), o.end(), equalOne);

    //auto itro = remove_if(o.begin(), o.end(), bind(equalOne, placeholders::_1, 12));
    
    auto itro = remove_if(o.begin(), o.end(),
                [](int e)
                {
                    if(e == 12)
                    {
                        cout << e << " will be removed" << endl;
                        return true;
                    }
                    else return false;
                });
    
    o.erase(itro, o.end());

    

    return 0;
}

