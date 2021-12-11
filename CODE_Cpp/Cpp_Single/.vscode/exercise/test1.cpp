#include <iostream>
using namespace std;

int main() {
    double item1 = 14.5;
    double item2 = 25.8;
    double item3 = 7.4;
    double rate = 0.07;

    double subtotal = item1 + item2 + item3;
    double tax = subtotal * rate;
    double total = subtotal + tax;

    cout << "Item 1: $" << item1 << endl;
    cout << "Item 2: $" << item2 << endl;
    cout << "Item 3: $" << item3 << endl;
    cout << "Subtotal: $" << subtotal << endl;
    cout << "Sales tax: $" << tax << endl;
    cout << "Total: $" << total << endl;
}