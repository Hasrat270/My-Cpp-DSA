// INPUT IN C++
#include <iostream>
using namespace std;

int main() {
    cout << "Enter You Age: ";
    int age;
    // cin >> age;
    if (age >= 18) {
        cout << "You are elgible for Driving license." << endl;
    } else {
        cout << "You are not eligible." << endl;
    }
    // Types Cating example below :
    cout << "Type Assigned by Type Casting: " << (5 / (double)2) << endl;
    cout << ((4 > 6) || (1 > 0));

    return 0;
}