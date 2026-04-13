#include <iostream>
#include <string>
#include <type_traits>
using namespace std;

class Animal {
public:
    virtual ~Animal() {}
    virtual void makeSound() const = 0;
    virtual void move() const = 0;
    virtual string getName() const = 0;
};

class Cat : public Animal {
public:
    void makeSound() const override {
        cout << "Мяу!" << endl;
    }
    void move() const override {
        cout << "Кошка крадётся" << endl;
    }
    string getName() const override {
        return "Cat";
    }
};

class Dog : public Animal {
public:
    void makeSound() const override {
        cout << "Гав!" << endl;
    }
    void move() const override {
        cout << "Собака бежит" << endl;
    }
    string getName() const override {
        return "Dog";
    }
};

class Bird : public Animal {
public:
    void makeSound() const override {
        cout << "Чирик!" << endl;
    }
    void move() const override {
        cout << "Птица летит" << endl;
    }
    string getName() const override {
        return "Bird";
    }
};

class Car {
public:
    void drive() const {
        cout << "Машина едет" << endl;
    }
    string getName() const {
        return "Car";
    }
};

template<typename T>
void feedAnimal(const T& entity) {
    if constexpr (is_base_of_v<Animal, T>) {
        cout << "Кормим " << entity.getName() << " - животное ест корм" << endl;
    } else {
        cout << "Ошибка: " << entity.getName() << " не животное!" << endl;
    }
}

template<typename T>
void checkAnimalType(const T& entity) {
    static_assert(is_base_of_v<Animal, T>, 
                  "Ошибка компиляции: тип должен быть наследником Animal!");
    cout << entity.getName() << " - это животное (проверено при компиляции)" << endl;
}


int main() {
    Cat cat;
    Dog dog;
    Bird bird;
    Car car;

    feedAnimal(cat);
    feedAnimal(dog);
    feedAnimal(car);

    checkAnimalType(cat);
    checkAnimalType(dog);
    checkAnimalType(bird);
    // checkAnimalType(car);

    cout << "Cat: "; cat.makeSound(); cat.move();
    cout << "Dog: "; dog.makeSound(); dog.move();
    cout << "Bird: "; bird.makeSound(); bird.move();
    cout << "Car: "; car.drive();
    
    return 0;
}