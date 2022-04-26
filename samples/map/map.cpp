#include<iostream>
#include<map>
#include<unordered_map>

using namespace std;

int main()
{
    //map底层采用红黑树实现，内部元素有序，默认按key从小到大排序，插入，删除查找复杂度均为logn
    //map<int, char> m;

    //unordered_map底层采用哈希表实现，内部元素无序，插入删除查找复杂度均为常数级
    unordered_map<int, char> m;
    m[10] = 'a';
    m[99] = '-';
    m[-100] = '0';

    cout << m.size() << endl;
    //count方法返回map内元素的数量
    if(m.count(99) == 1)    //find方法也可以用来判断元素是否存在，但返回类型为迭代器，判断迭代器！= end()
    {
        cout << m[99] << endl;
    }

    m.erase(99);
    if(m.count(99) == 0) cout << "not find" << endl;
    cout << m.size() << endl;

    m[6] = '/';
    m[-5] = 'I';
    for(auto it = m.begin(); it != m.end(); it ++)
    {
        cout << it->first << " " << it->second << endl;
    }

    cout << endl;

    return 0;
}