#include<iostream>
#include<complex>
#include<bitset>
#include<fstream>
#include<iomanip>
using namespace std;
int main()
{
    //C++ Input/Output Library -- Stream
    cout << "Hello" << endl;
    //cout: a global object of stream(typedef basic_ostream<char> ostream)
    //<<: ostream& ostream::operator<< (string V);
    //endl:'\n' + flush

    //What is stream? Serial IO Interface to external to external devices(file, stdin/stdout, network, etc.)
    string s("Hello");
    s[3] = 't'; //Random access
    //cout[3] = 't'; //Error
    {
        ofstream of("MyLog.txt"); //Creates a new file for write, if the file didn't exist
        of << "Experience is the mother of wisdom" << endl;
        of << 234 << endl;
        of << 2.3 << endl;

        of << bitset<8>(14) << endl;  //00001110
        of << complex<int>(2, 3) << endl; //(2, 3)
    }  //RAII
    //IO Operation
    //formatting the data <------> communicating the data with external devices

    //Software Engineer Principle: Low Coupling -> Reusabilit
    {
        //ofstream of("MyLog.txt");  //Open file for write, clear the content of the file
        ofstream of("MyLog.txt", ofstream::app);  //won't clear the content, move the output pointer to the end of the file
        of << "Honesty is the best policy." << endl;
    }

    //write sth in the middle of the file
    {
        ofstream of("MyLog.txt", ofstream::in | ofstream::out);
        of.seekp(10, ios::beg); //Move the output pointer 10 chars after beginning
        of << "12345"; //overwrite 5 chars
        of.seekp(-5, ios::end); //Move the output pointer 5 chars before end
        of << "Nothing ventured, nothing gained." << endl;
        of.seekp(-5, ios::cur); //Move the output pointer 5 chars before current position
    }
    //Read, Input
    ifstream inf("MyLog.txt");
    int i;
    inf >> i; //read one word from the file and pass it as an int and save it into i
        //in this case, the first word is "Experience" but not an int, so this operation will fail.
    //Error status: goodbit, badbit, failbit, eofbit;
    inf.good();  //Everything is OK(goodbit == 1)
    inf.bad(); //Non-recoverable error(badbit == 1)
    inf.fail(); //failed stream operation(logic error generally recoverable).(failbit == 1 badbit == 1)
    inf.eof(); //End of file (eofbit == 1)
    cout << ios::goodbit << " " << ios::badbit << " " << ios::failbit << " " << ios::eofbit << endl;
    inf.clear(); //clear all the error status (the same as clear(ios::goodbit), set goodbit to 1 and everything else to 0)
    cout << ios::goodbit << " " << ios::badbit << " " << ios::failbit << " " << ios::eofbit << endl;
    inf.clear(ios::badbit); //not clearing the badbit but sets a new value to the error flag(set the badbit to 1 and everything else to 0)
    cout << ios::goodbit << " " << ios::badbit << " " << ios::failbit << " " << ios::eofbit << endl;
    inf.rdstate(); //Read the current status flag;
    inf.clear(inf.rdstate() & ~ios::failbit); //clear the only failbit and everything else stay the same
    cout << ios::goodbit << " " << ios::badbit << " " << ios::failbit << " " << ios::eofbit << endl;
    if(inf) //Equivalent to: if(!inf.fail())
        cout << "Read successfully";
    
    if(inf >> i)
        cout << "Read successfully";
    cout << ios::goodbit << " " << ios::badbit << " " << ios::failbit << " " << ios::eofbit << endl;
    //handle the errors with exceptions
    //inf.exceptions(ios::badbit | ios::failbit); //setting the exception mask
        //when badbit or failbit set to 1, exception of ios::failure will be thrown
        //when eofbit set to 1, no exception
    //inf.exceptions(ios::goodbit); //No exceptions
    
    //Formatting
    cout << 34 << endl;  //34
    cout.setf(ios::oct, ios::basefield);
    cout << 34 << endl; //42
    cout.setf(ios::showbase);
    cout << 34 << endl; //042
    cout.setf(ios::hex, ios::basefield);
    cout << 34 << endl; //0x22

    cout.unsetf(ios::showbase);
    cout << 34 << endl;  //22
    cout.setf(ios::dec, ios::basefield);

    cout.width(10);
    cout << 26 << endl; //         26
    cout.setf(ios::left, ios::adjustfield); //26
    cout << 26 << endl;
    //Floating point data
    cout.setf(ios::scientific, ios::floatfield);
    cout << 340.1 << endl;  //3.401000e+002
    cout.setf(ios::fixed, ios::floatfield);
    cout << 340.1 << endl;  //340.100000
    cout.precision(3);
    cout << 340.1 << endl;  //340.100

    //int i;
    cin.setf(ios::hex, ios::basefield);
    cin >> i; //Enter: 12  12 is treated as a hexadecimal number// i == 18
    cout << i << endl;

    ios::fmtflags f = cout.flags();
    cout.flags(ios::oct | ios::showbase);

    //Member functions for unformatted IO
    //input
    #if 0
    ifstream inf("MyLog.txt");
    char buf[80];
    inf.get(buf, 80); //read up to 80 chars and save into buf
    inf.getline(buf, 80); //read up to 80 chars or until '\n' is encountered
    inf.read(buf, 20);  //read 20 chars
    inf.ignore(3);  //ignore next 3 chars in the stream
    inf.peek();  //return the character on top of the stream
    inf.unget();  //return a char back to the stream, unget function have no parameters, it will always put back the same character you have lasted read back to the stream;
        //inf.putback('z') can put back a different character for next read, in this case, it puts back the character of z
    inf.get();
    inf.gcount(); //return the number of chars being read by last unformatted read
    
    //output
    ofstream of("MyLog.txt");
    of.put('c');  //put one character into the stream
    of.write(buf, 6); //write first 6 chars of buf into the stream
    of.flush();  //it will flush the output
    #endif
    //What is an endl? Object? or build-in datatype? function? it is a function
    cout << "Hello" << endl; //endl: '\n' and flush
    
    #if 0
    //methods to overload endl
    ostream& endl(ostream& sm)  //Manipulator
    {
        sm.put('\n');
        sm.flush();
        return sm;
    }
    // << operator :: ostream& ostream::operator<<(ostream& (*func)(ostream&)) { return (*func)(*this);}
    
    cout << ends;  //'\0'
    cout << flush;
    cin >> ws; //read and discard white spaces
    #endif
    cout.setf(ios::dec, ios::basefield);
    cout << setw(8) << left << setfill('_') << 99 << endl; //99_________
        //set width 8 and set ios::left and replace white spaces with _
    cout << hex << showbase << 14; //0xe
        //set ios::hex and ios::showbase
    
    //IO operation
    //formatting data -- stream
    //communicating data to external devices -- stream buffer(internal module of a stream)
    cout << 34 << endl;
        //cout is responsible for converting 34 into appropriate format
        //and delegate the job of communicating data to its internal module which is a stream buffer
    //cout.rdbuf() // to get s pointer to the internal module of stream buffer
    streambuf* pbuf = cout.rdbuf();
        //cout formatting data; streambuf transmitting data to standard out
    
    ostream myCout(pbuf); //create another stream which has the same stream buffer as cout
        //myCout has the same transferring channel as cout
    myCout << 34 << endl; //34 will be printed out to standard out
    myCout.setf(ios::showpos);
    myCout.width(20);
    myCout << 12 << endl;  //          +12
    cout << 12 << endl; //12

    ofstream of("MyLog.txt");

    //save the original stream buffer of cout
    streambuf* origBuf = cout.rdbuf();

    cout.rdbuf(of.rdbuf()); //assign the stream buffer of of to cout 
    cout << "Hello" << endl;  //MyLog.txt has "Hello"
        //Redirecting the stdout to a log file
    //Restore cout stream buffer
    cout.rdbuf(origBuf);

    cout << "Goodbye" << endl;  //stdout: Goodbye

    //Stream buffer iterator
    istreambuf_iterator<char> in(cin);
    ostreambuf_iterator<char> out(cout);
    while(*in != 'x')
    {
        *out = *in;
        ++out;
        ++in;
    }
    
    //copy(istreambuf_iterator<char>(cin), istreambuf_iterator<char>(), ostreambuf_iterator<char>(cout));
        //points to the begin of the cin streambuf, default constructor points to the end of the stream buffer, points to the begin of the cout stream buffer
    
    //StringStream
    stringstream ss; //Stream without IO operation
    //read/write of string

    ss << 89 << " Hex: " << hex << 89 << " Oct: " << oct << 89;
    cout << ss.str() << endl; //89 Hex: 59 Oct: 131
    
    int a, b, c;
    string s1;
    ss >> hex >> a;  //read the first word and pass it as a hex number and then save to a
        //Formatted input works token by token. tokens are separated by spaces tabs and new lines
        //a == 137
    ss >> s1; //s1: "Hex:"
    ss >> dec >> b;  //b == 59
    ss.ignore(6);

    ss >> oct >> c; // c == 89

    //ostringstream  --  only for formatted output
    //istringstream  --  only for formatted input
    //if need to use the stream for both input and output , should use stringstream 
    //otherwise ostringstream or istringstream(better safety of type)
    return 0;
}
#if 0
struct Dog
{
    int age_;
    string name_;
};

ostream& operator<<(ostream&sm, const Dog& d)
{
    sm << "My name is " << d.name_ << " and my age is " << d.age_ < endl;
    return sm;
}

istream& operator>>(istream& sm, Dog& d)
{
    sm >> d.age_;
    sm >> d.name_;
    return sm;
}

int main()
{
    Dog d{2, "Bob"};  //Universal Initialization
    cout << d;

    cin >> d;

    cout << d;
    return 0;
}
#endif