/*
 * Understanding Rvalue and Lvalue
 *
 * Why do I care?
 * 1. Understand C++ construct, and decypher compliers errors and warnings
 * 2. C++ 11 introduced rvalue reference.
 */

/*
 * Simplified Definition:
 * 
 * lvalue - Any object that occupies some identifiable location in memory
 * rvalue - Any object that is not a lvalue
 */

#if 0

//Most variables in C++ code are lvalues
//Lvalue Examples:
int i;  // i is a lvalue
int* p = &i;  //i's address is identifiable
i = 2;  //Memory content is modified

class dog;
dog d1;  //lavlue of user defined type(class)

//Rvalue Examples:
int x = 2;  //2 is an rvalue
int x = i + 2;  // (i + 2) is an rvalue
int* p = &(i + 2); //Error
i + 2 = 4;  //Error
2 = i;  //Error

dog d1;
d1 = dog();  //dog() is rvalue of user defined type(class)

int sum(int x, int y) { return x + y; }
int i = sum(3, 4);  //sum(3, 4) is rvalue

//Rvalues: 2, i + 2, dog(), sum(3, 4), x + y
//Lvalues: x, i, d1, p

//reference (or lvalue reference)
int i;
int&r = i;

int& r = 5;  ///Error, can't initialize with a rvalue
//Exception: Constant lvalue reference can be assign a rvalue
const int& r = 5;

int square(int& x) { return x * x;}
square(i);  //OK
square(40); //Error
//Workaround:
int square(const int& x) { return x * x; } //square(i) and square(40) both works

/*
 * lvalue can be used to create an rvlaue
 */

int i = 1;
int x = i + 2;

int x = i; //lvalue i implicitly transformed into a rvalue then assigns to x
           //Note: rvalue can not be implicitly transformed into lvalue

/*
 * rvalue can be used to create an lvalue
 */
int v[3];
*(v + 2) = 4;// v + 2 is a rvalue, dereference of (v + 2) is lvalue


/*
 * Misconception 1: function or operator always yields rvalues.
 */

int x = i + 3;
int y = sum(3, 4);

int myglobal;

int& foo() { return myglobal;}
foo() = 50;

//A more common example:
array[3] = 50; //operator [] almost always generates lvalue

/*Misconception 2: lvalues are modifiable
 *
 * C language: lvalue means "value suitable for left-hand-side of assignment"
 * 
 */
const int c = 1; // c is a lvalue
c = 2; //error, c is not modifiable.

 /*
  * Misconception 3: rvalues are not modifiable
  */
 i + 3 = 6;  //Error
 sum(3, 4) = 7 //Error

 //It is not true for user defined type(class)
 class dog;
 dog().bark();  //bark() may change the state of the dog object.

/*
 * Summary
 *
 * 1. Every C++ expression yield either an rvalue or a lvalue
 * 2. If the expression has an identifiable memory address, it's lvalue. otherwise, rvalue.
 */
#endif