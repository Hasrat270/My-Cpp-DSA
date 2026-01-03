// PRIMITIVES DATA TYPES 
#include <iostream>
using namespace std;

int main () {
    // int data tupe takes 4 bytes in memory = to 32 bits
    int age = 21;
    // char takes 1 byte in memory = to 8 bits
    char grade = 'A';
    cout << sizeof(age) << endl;
    cout << sizeof(grade) << endl;
    cout << "Grade: " << grade << endl;
    // float takes 4 bytes in memory = to 32 bits
    float PI = 3.14f;
    cout <<"PI: "<< PI << endl;
    // boolean takes 1 byte in memory = 8 bits (true = 1, false = 0)
    bool isEligible = true;
    cout  << "Boolean: "<< isEligible << endl;
    // double takes 8 bytes in memory = 64 bits
    double price = 100.99;
    cout << "Double: " << price << endl;
    // Implicit Conversion (Small to big)
    int value = grade;
    cout << "Converted ASCII Value (Implicit): " << value << endl;
    // Type Casting Conversion (Big to small)
    int newPrice = (int)price;
    cout << "Converted ASCII Value: (Explicit): " <<newPrice << endl;

    return 0;
}