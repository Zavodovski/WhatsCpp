#include<iostream>
#include<random>
#include<sstream>
#include<chrono>
#include<algorithm>
#include<vector>
using namespace std;

/*  Random Engine:
 *      Stateful generator that generates random values within predefined min and max
 *      Not truely random -- pseudorandom
 */

void printRandom(std::default_random_engine e)
{
    for(int i = 0; i < 10; i ++)
        cout << e() << " ";
    cout << endl;
}



int main()
{
    std::default_random_engine eng;
    cout << "Min: " << eng.min() << endl;
    cout << "Max: " << eng.max() << endl;

    cout << eng() << endl;
    cout << eng() << endl;

    std::stringstream state;
    state << eng;  //save the current state

    cout << eng() << endl;
    cout << eng() << endl;

    state >> eng;  //restore the state

    cout << eng() << endl;
    cout << eng() << endl;

    std::default_random_engine e;
    std::default_random_engine e2;

    printRandom(e);
    printRandom(e2);  //when created both engines are in the same state, the initial state; and thus generates same numbers

    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    std::default_random_engine e3(seed);  //seed is a number that determines the interal state of an engine
    printRandom(e3);

    e.seed();  //reset engine e to initial state
    e.seed(109);  //set engine e to a state according to seed 109
    e2.seed(109); 
    if(e == e2)
        cout << "e and e2 have the same state" << endl;

    vector<int> d = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::shuffle(d.begin(), d.end(), std::default_random_engine());

    for(auto it = d.begin(); it != d.end(); it ++)
        cout << *it << " ";
    cout << endl;

    std::default_random_engine e4(seed);
    cout << e4() << endl;  //range: [e.min(), e.max()]

    //Range:[0, 5]
    cout << e4() % 6 << endl;
    //1. Bad quality of randomness
    //2. Can only provide uniform distribution

    std::uniform_int_distribution<int> distr(0, 5); //Range:[0, 5]
    cout << distr(e4) << endl;

    std::uniform_real_distribution<double> distrR(0, 5); //Range:[0, 5)
    cout << distrR(e4) << endl;

    std::poisson_distribution<int> distrP(1.0);  //mean: 1.0
    cout << distrP(e4) << endl;

    cout << " normal_distribution: " << endl;
    std::normal_distribution<double> distrN(10.0, 3.0);  //mean and standard deviation
    vector<int> v(20);
    for(int i = 0; i < 800; i ++)
    {
        int num = distrN(e);   //convert double to int
        if(num >= 0 && num < 20)
            v[num] ++;//e.g. v[10] records number of times 10 appeared
    }
    for(int i = 0; i < 20; i ++)
    {
        cout << i << ": " << std::string(v[i], '*') << endl;
    }
    cout << endl;
    return 0;
}