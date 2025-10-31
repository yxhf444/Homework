#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;



int create() {
    int number = 1+rand()%100;
    return number;
}

int guess(int n) {
    vector <int> vec;
    int attempt;
    cin>>attempt;
    while (attempt!=n) {
        vec.push_back(attempt);
        if (attempt>n){
            cout<<"Меньше"<<endl;
        }
        else {
            cout<<"Больше"<<endl;
        }
        cout<<"Try again"<<endl;
        cin>>attempt;
    }
    cout<<"Поздравляю вы угадали число: "<<n<<". Количество попыток: "<<vec.size()<<endl;
    cout<<"Попытки: ";
    for (auto i:vec) {
        cout<<i<<"  ";
    }
    return 0;
}

int main() {
    srand(time(0));
    int num = create();
    cout<<"Число загадано "<<endl;

    guess(num);
    cout<<guess(num);

    return 0;
}


//ЧТобы работало создать мейн