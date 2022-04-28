#include<iostream>
#include"node.h"
#include<queue>
using namespace std;

/*  Container Adadptor
 *  provide a restricted interface to meet special needs
 *  implemented with fundamental container classes
 *  1. stack: LIFO, push(), pop(), top()
 *  2. queue: FIFO, push(), pop(), front(), back()
 *  3. priority_queue: first item always has the greatest priority push(), pop(), top() 
 */

int main()
{
    //priority_queue默认为大顶堆，即priority_queue<int,vector<int>,less<int>>第三个参数默认为less<int>
    //当优先队列定义为priority_queue<int, vector<int>, greater<int>>时，为小顶堆
    //priority_queue<int> que;
    priority_queue<int, vector<int>, greater<int>> que;
    que.push(7);
    que.push(5);
    que.push(-2);
    que.push(1);
    que.push(6);
    
    //自定义类型使用优先队列，需要对<进行重载, 且只能重载小于号，重载大于号无效
    priority_queue<node> nodes;
    nodes.push((node){1, 5});
    nodes.push((node){2, 3});
    nodes.push((node){9, 4});
    nodes.push((node){-5, 5});


    cout << que.size() << endl;
    while(!que.empty())
    {
        cout << que.top() << " ";
        que.pop();
    }
    cout << endl;

    cout << nodes.size() << endl;
    while(!nodes.empty())
    {
        cout << nodes.top().x << " ";
        nodes.pop();
    }
    cout << endl;

    return 0;
}