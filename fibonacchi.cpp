#include <iostream>
using namespace std;

unsigned long long fibonacchi(int a) {
    if (a==1) return 1;
    if (a<=0) return 0;
    return fibonacchi(a-1)+fibonacchi(a-2);
}

int main() {
   /*=== FROM TEACHER ===
		Инициализируй переменные простого типа сразу.
		int a{0};
	*/
    int a;
    cout<<"Enter your number";
    cin>>a;
    /*=== FROM TEACHER ===
		Почему a-1 ?
	*/
    cout<<fibonacchi(a-1);
    return 0;
}


