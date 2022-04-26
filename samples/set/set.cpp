#include<iostream>
#include<set>
#include<unordered_set>
using namespace std;
int main()
{
    //set底层采用红黑树实现，内部元素有序，插入，删除查找复杂度均为logn
    //set<int> s;

    //unordered_set底层采用哈希表实现，内部元素无序，插入删除查找复杂度均为常数级
    unordered_set<int> s;
    s.insert(9);
    s.insert(10);
    s.insert(5);
    s.insert(-2);
    s.insert(99999);

    cout << s.size() << endl;
    //count方法返回集合内元素的数量
    if(s.count(5) == 0)    //find方法也可以用来判断元素是否存在，但返回类型为迭代器，判断迭代器！= end()
    {
        cout << "not find 5" << endl;
    }
    else cout << "find 5" << endl;

    s.erase(5);
    if(s.count(5) == 0) cout << "not find 5" << endl;
    cout << s.size() << endl;

    for(auto it = s.begin(); it != s.end(); it ++)
    {
        cout << *it << " ";
    }

    cout << endl;

    return 0;
}