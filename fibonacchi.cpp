#include <iostream>
using namespace std;

unsigned long long fibonacchi(int a) {
    if (a==1) return 1;
    if (a<=0) return 0;
    return fibonacchi(a-1)+fibonacchi(a-2);
}

int main() {
    int a;
    cout<<"Enter your number";
    cin>>a;
    cout<<fibonacchi(a-1);
    return 0;
}

