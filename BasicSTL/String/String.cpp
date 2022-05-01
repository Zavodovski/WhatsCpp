#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
int main()
{
    //Constructor
    string s1("Hello");
    cout << s1 << endl;
    string s2("Hello", 3);   //s2: Hel
    cout << s2 << endl;
    string s3(s1, 2);  //s3: llo
    cout << s3 << endl;
    string s4(s1, 2, 2); //s4: ll  , the first 2 is the start position, the second is the length from the start position
    cout << s4 << endl;
    string s5(5, 'a');  //s5: "aaaaa"
    cout << s5 << endl;
    string s6({'a', 'b', 'c'});  //s6:"abc"
    cout << s6 << endl;
    
    //Size
    s1 = "Goodbye";
    cout << s1.size() << " " << s1.length() << endl;  //Synonymous, both returns 7
    cout << s1.capacity() << endl; //size of storage space currently allocated to s1
    s1.reserve(100);  //100 chars
    cout << s1.size() << " " << s1.length() << " " << s1.capacity() << endl;
    s1.reserve(5);    //s1: Goodbye s1.size() == 7 s1.capacity() == 7
        //reserve doesn't change the content of the string
    cout << s1.size() << " " << s1.length() << " " << s1.capacity() << endl;
    s1.shrink_to_fit();  //shrink the capacity to hold the content
    cout << s1.size() << " " << s1.length() << " " << s1.capacity() << endl;
    s1.resize(9);   //s1: Goodbye\0\0
    cout << s1 << endl;
    cout << s1.size() << " " << s1.length() << " " << s1.capacity() << endl;
    s1.resize(12, 'x');   //s1: Goodbye\0\0xxx  s1.size() == 12
    cout << s1 << endl;
    cout << s1.size() << " " << s1.length() << " " << s1.capacity() << endl;
    s1.resize(3);   //s1: Goo    
    cout << s1 << endl;
    cout << s1.size() << " " << s1.length() << " " << s1.capacity() << endl;
    
    //Single Element Access
    s1 = "Goodbye";
    cout << s1[2] << endl;  //'o'
    s1[2] = 'x';   //Goxdbye
    cout << s1 << endl;
    s1.at(2) = 'y';//Goydbye
    cout << s1 << endl;  
    //s1.at(20)  throw exception of out of range
    //s1[20]     undefined behavior

    cout << s1.front() << endl;  //'G'
    cout << s1.back() << endl;    //'e'
    s1.push_back('z'); 
    cout << s1 << endl;
    s1.pop_back();
    cout << s1 << endl;
    //s1.begin(), s1.end()
    cout << *(s1.begin()) << endl;
    //like vector, string doesn't have push_front() and pop_front()
    string s7(s1.begin(), s1.begin() + 3);
    cout << s7 << endl;
    
    //Ranged Access
    //assign, append, insert, replace
    s2 = "Dragon Land";
    s1.assign(s2); //s1 = s2
    cout << s1 << endl;
    s1.assign(s2, 2, 4); //s1:agon
    cout << s1 << endl;
    s1.assign("Wisdom");  //s1: Wisdom
    cout << s1 << endl;
    s1.assign("Wisdom", 3);  //s1: Wis
    cout << s1 << endl;
    s1.assign(s2, 3);// So if the first parameter is a C string, the second parameter is the length
                    //if the first parameter is a C++ string, the second parameter is the start position of the string , and the third is the length(and it's default to the end of the string)
    cout << s1 << endl;
    s1.assign(3, 'x');
    cout << s1 << endl;
    s1.assign({'a','b','c'});  //s1:  abc
    cout << s1 << endl;

    s1.append(" def");
    cout << s1 << endl;
    s1.insert(2, "mountain", 4);  //s1:abmounc def
    cout << s1 << endl;
    s1.replace(2, 5, s2, 3, 3);   //s1: abgon def
            //start Pos, length, another string, start pos, length
    cout << s1 << endl;
    s1.erase(1, 4);  //s1: a def
        //start pos, length
    cout << s1 << endl;
    cout << s2.substr(2, 4) << endl;   //agon
        //start pos, length
    

    s1 = "abc";
    cout << s1.c_str() << endl; //"abc\0" same as .data() after C++ 11

    s1.swap(s2);
    cout << s1 << endl;
    cout << s2 << endl;


    //Member Function Algorithms: copy, find, compare
    s1 = "abcdefg";
    char buf[20];
    size_t len = s1.copy(buf, 3); //copy the s1's 3 characters to buf and return a value that the number of characters that indeed be copied
        //buf: abc len == 3
    //cout << buf << " " << len << endl;
    //len = s1.copy(buf, 4, 2);     //buf:cdef  len == 4
        //buf, length, start pos  !attention: copy function is only exceptional case that first length second position
    //cout << buf << " " << len << endl;
    s1 = "If a job is worth doing, it's worth doing well";
    size_t found = s1.find("doing"); //return the first pos where doing is found,  found == 17
    cout << found  << endl;
    found = s1.find("doing", 20);  //find doing with the start pos 20,  found == 35
    cout << found << endl;
    found = s1.find("doing well", 0);  //found == 35
    cout << found << endl;
    found = s1.find("doing well", 0, 5);  //search from the start pos 0, and looks at the first 5 characters of doing well , found == 17
    cout << found << endl;

    found = s1.find_first_of("doing"); //find the first character of s1 that appears in doing , found == 6(find the first 'o')
    cout << found << endl;
    found = s1.find_first_of("doing", 10);    //search from the start pos 10, find the second 'o' in s1, found == 12
    cout << found << endl;
    found = s1.find_first_of("doing", 10, 1);    //search from the start pos 10, and only looks at the first character in doing ,find the first 'd' in s1, found == 17
    cout << found << endl;
    
    found = s1.find_last_of("doing"); //search from the end, find the last 'g', found == 39
    cout << found << endl;
    found = s1.find_first_not_of("doing");  //find the first character not appear in the doing, find the first 'I', found == 0
    cout << found << endl;
    found = s1.find_last_not_of("doing");  //find the last character that not appears in the doing , find the last 'l', found == 44
    cout << found << endl;
    
    cout << s1.compare(s2) << endl;
        //return positive if(s1 > s2); negative if(s1 < s2); 0 if(s1 == s2)
    //if(s1 > s2) {}  same as if(s1.compare(s2))
    cout << s1.compare(3, 2, s2) << endl;
        //start pos, length, string
    //concatenate, very expensive when the size of string is very big
    string ss = s1 + s2;
    cout << ss << endl;

    s1 = "abc";
    s2 = "aba";
    cout << s1.compare(s2) << endl;

    #if 0
    //Non-member functions
    cout << s1 << endl;
    cin >> s1;
    getline(cin, s1);  //default delimeter of '\n'
    getline(cin, s1, ';') //delimeter is ';'

    s1 = to_string(8); convert a number to a string

    #endif
    s1 = to_string(8);  
    cout << s1 << endl; 
    s1 = to_string(2.3e7); 
    cout << s1 << endl;
    s1 = to_string(0xa4);
    cout << s1 << endl;
    s1 = to_string(034);
    cout << s1 << endl;

    s1 = "190";
    int i = stoi(s1); //i: 190
    cout << i << endl; 

    s1 = "190 monkeys";
    size_t pos;
    i = stoi(s1, &pos); //i: 190 pos==3
    cout << i << endl; 
    s1 = "a monkey";
    //i = stoi(s1, &pos);  //exception of invalid_argument, can't find a number in s1
    //cout << i << endl; 
    i = stoi(s1, &pos, 16);  //i == 10, extract a hexadecimal number in s1 which is 'a'
    cout << i << endl; 
    //stol, stod, stof, etc

    //stringstream
    //lexical_cast()

    s1 = "Variety is the spice of life";
    //how many 'e' appears
    int num = count(s1.begin(), s1.end(), 'e'); //4
    cout << num << endl;
    num = count_if(s1.begin(), s1.end(), [](char c) { return c <= 'e' && c >= 'a'; }); //6
    cout << num << endl;
    
    s1 = "Goodness is better than beauty";
    //search the consecutive two s
    string::iterator itr = search_n(s1.begin(), s1.begin() + 20, 2, 's');  //itr -> first 's'
    cout << *itr << endl;
    s1.erase(itr, itr + 5);
    cout << s1 << endl;
    cout << *(itr+1) << endl;
    s1.insert(itr, 3, 'x');
    cout << s1 << endl;
    cout << *(itr+1) << endl;
    s1.replace(itr, itr + 3, 3, 'y');  //replacing substr
    cout << s1 << endl;
    cout << *(itr+1) << endl;
    cout << is_permutation(s1.begin(), s1.end(), s2.begin()) << endl;
    replace(s1.begin(), s1.end(), 'e', ' '); //replacing characters
    cout << s1 << endl;
    cout << *(itr+1) << endl;
    s2.resize(50);
    transform(s1.begin(), s1.end(), s2.begin(),
                [](char c)
                {
                    if(c < 'n') return 'a';
                    else return 'z';
                });
    
    cout << s2 << endl;
    s1 = "abcdefg";
    rotate(s1.begin(), s1.begin() + 3, s1.end()); //s1: defgabc
    cout << s1 << endl;

    //string s
    //u16string s1; //string char16_t
    //u32string s1; //string char32_t
    //wstring s1; //string wchar_t(wide character)
    //to_wstring
    return 0;
}