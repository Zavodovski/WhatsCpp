#include<iostream>
#include<string>
#include<tuple>
#include<vector>
#include<functional>
#include<map>
#include<unordered_map>
using namespace std;


tuple<string, int> getNameAge();

int main()
{
    std::pair<int, string> p = make_pair(23, "hello");
    cout << p.first << " " << p.second << endl;

    tuple<int, string, char> t(32, "Penny wise", 'a');
    cout << get<0>(t) << endl;
    cout << get<1>(t) << endl;
    cout << get<2>(t) << endl;

    get<1>(t) = "Pound foolish";
    string& s = get<1>(t);
    s = "Patience is virtue";  //also changes t
    //get<3>(t);  //out of range

    vector<int> v(3);
    v[1] = 3;
    
    int i = 1;
    //get<i>(t);  //i must be compile time constant

    tuple<int, string, char> t2;  //every member is constructed with default constructor
    t2 = tuple<int, string, char>(12, "Curiosty kills the cat", 'd');
    t2 = make_tuple(12, "Curiosty kills the cat", 'd');

    if(t > t2)  //lexicographical comparison
    {
        cout << "t is larger than t2" << endl;
        t = t2;  //member by member copying
    }

    //Tuple can store references
    string st = "In for a penny";
    tuple<string&> t3(st);
    t3 = make_tuple(ref(st));
    get<0>(t3) = "In for a pound"; //st contains "In for a pound"
    t2 = make_tuple(12, "Curiosity kills the cat", 'd');
    int x;
    string y;
    char z;
    make_tuple(ref(x), ref(y), ref(z)) = t2;
    std::tie(x, y, z) = t2; //Doing the same thing as the last line
    //std::tie(x, std::ignore, z) = t2;  //ignore the value y
    
    auto t4 = std::tuple_cat(t2, t3);  //t4 is a tuple<int, string, char, string>

    //type traits
    cout << std::tuple_size<decltype(t4)>::value << endl;  //4
    std::tuple_element<1, decltype(t4)>::type d; //d is a string
    
    


    //when to use tuple?
    struct person { string name; int age; } pers;
    tuple<string, int> t5;

    cout << pers.name << " " << pers.age << endl;
    cout << get<0>(t5) << " " << get<1>(t5) << endl;

    //As a one-time only structure to transfer a group of data 
    string name;
    int age;
    tie(name, age) = getNameAge();


    //Comparison of tuples
    tuple<int, int, int> time1, time2; //hours, minutes, seconds
    if(time1 > time2)
        cout << "time1 is a later time" << endl;
    
    //multi index map
    map<tuple<int, char, float>, string> m;
    m[make_tuple(2, 'a', 2.3)] = "Faith will move mountains";
    //unordered_map<tuple<int, char, float>, string> ht;  //need a user defined function for tuple

    //a trick for shift values
    //int a, b, c;
    //tie(b, c, a) = make_tuple(a, b, c);

    int a = 1, b = 2;
    tie(b, a) = make_tuple(a, b);

    cout << a << " " << b << endl;
    return 0;
}

tuple<string, int> getNameAge()
{
    //...
    return make_tuple("Bob", 34);
}