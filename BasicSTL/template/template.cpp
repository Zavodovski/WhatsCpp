#include<iostream>
using namespace std;
//可以使用function template统一不同参数类型的函数，使代码更整洁
//但本质上它们仍属于不同的函数，占用独立的空间，每一个的具体参数类型都会生成一份对应的代码
//如果使用的类型过多，会造成代码膨胀
template<typename T>
T square(T x)
{
    return x * x;
}

/*
int square(int x)
{
    return x * x;
}

double square(double x)
{
    return x * x;
}
*/

//class template的使用方法
template<typename T>
class BoVector
{
private:
    T arr[100];
    int size;
public:
    BoVector() : size(0) {}
    void push(T x)
    {
        arr[size] = x;
        size ++;
    }
    void print() const
    {
        for(int i = 0; i < size; i ++) cout << arr[i] << " ";
        cout << endl;
    }
    T get(int i) const { return arr[i]; }
    int getsize() const { return size; }
};

//class template与function template结合使用
template<typename T>
BoVector<T> operator* (const BoVector<T>& lhs, const BoVector<T>& rhs)
{
    BoVector<T> ret;
    for(int i = 0; i < lhs.getsize(); i ++)
    {
        ret.push(lhs.get(i) * rhs.get(i));
    }
    return ret;
}



int main()
{
    //函数模板不需要显式地指定模板参数，编译器可以根据参数类型自动推导
    cout << square(5) << endl;
    //cout << square(5.5) << endl;
    //类模板需要自己显式地指定模板参数
    BoVector<int> bv;
    bv.push(2);
    bv.push(5);
    bv.push(8);
    bv.push(9);
    bv.print();
    cout << "Print Squared bv: " << endl;
    bv = square(bv);
    bv.print();
    return 0;
}