#include <iostream>
#include <string>
using namespace std;

template<typename T>
class Printer {
public:
    void print(const T& value) {
        cout << "Value: " << value << endl;
    }
};

template<>
class Printer<bool> {
public:
    void print(const bool& value) {
        cout << (value ? "true" : "false") << endl;
    }
};

template<typename T>
class Printer<T*> {
public:
    void print(T* const& ptr) {
        cout << "Address: " << ptr << " Value: " << *ptr << endl;
    }
};

int main() {
    Printer<int> p1;
    p1.print(42);

    Printer<double> p2;
    p2.print(3.14);

    Printer<string> p3;
    p3.print("Hello");

    Printer<bool> p4;
    p4.print(true);
    p4.print(false);

    int x = 100;
    Printer<int*> p5;
    p5.print(&x);

    double y = 2.718;
    Printer<double*> p6;
    p6.print(&y);

    string str = "world";
    Printer<string*> p7;
    p7.print(&str);

    return 0;
}