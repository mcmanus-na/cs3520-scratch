#include <string>
#include <vector>
#include <iostream>

using namespace std;

void print_vector(const vector<int> &vec) {
    cout << "----" << endl;
    for (size_t i = 0; i < vec.size(); i++) {
        cout << i << ": " << vec[i] << endl;
    }
    cout << "----" << endl;
}

/*
Write a program that:

Initializes an int vector with 3 elements, all with the value 300
Adds 7 elements to that vector, all with the value 700 (think about the .resize() function)
Inserts the element 800 at the 8th position.
Creates a new vector.
Fills the new vector with elements from the first vector in reverse order. Use the functions .back() and .pop_back()
*/
void part1() {
    vector<int> vec(3, 300);
    vec.resize(vec.size() + 7, 700);
    vec.insert(vec.begin() + 7, 800); // instructions unclear I think
    print_vector(vec);
    vector<int> new_vec;
    while (!vec.empty()) {
        new_vec.push_back(vec.back());
        vec.pop_back();
    }
    print_vector(new_vec);
}

/*
Write a function named make_ordered that takes two int arguments a and b by reference. 
If needed, it swaps the values of the arguments so that the the smaller value is stored 
in a and the larger in b. That is, it orders the values so that a <= b after the function 
returns. After you've finished that, write a second, overloaded function that does the 
same for doubles.
*/
void make_ordered(int &a, int &b) {
    int max = a > b ? a : b;
    int min = a < b ? a : b;
    a = min;
    b = max;
}

void make_ordered(double &a, double &b) {
    double avg = (a+b)/2;
    double half_diff = (a-b)/2;
    a = avg - half_diff;
    b = avg + half_diff;
}

/*
Write a function named vector_length_equals that takes in two integer vectors and prints "YES!"
if the vectors have the same length, or "NO!" if they don't. Your function should be split into 
a separate declaration and definition. Your function should take in the vectors via const reference, 
and have a comment explaining why the const reference is a good idea.
*/

// Const references here lets you pass in two vectors without copying them,
// but ensures this function cannot edit the vectors somehow
void vector_length_equals(const vector<int> &vec1, const vector<int> &vec2) {
    cout << (vec1.size() == vec2.size() ? "YES!" : "NO!") << endl;
}

int main() {
    part1();

    int a = 8;
    int b = 3;
    make_ordered(a, b);
    cout << a << " < " << b << endl;

    double a2 = 8.5;
    double b2 = 3.5;
    make_ordered(a2, b2);
    cout << a2 << " < " << b2 << endl;

    vector<int> v1 = {1,2,3};
    vector<int> v2 = {4,5,6};
    vector<int> v3 = {1};
    vector_length_equals(v1,v2); //YES!
    vector_length_equals(v1,v3); //NO!
}