#include <iostream>
#include <string>

template<typename T, int Capacity>
class Stack {
private:
    T data[Capacity];
    int topIndex;

public:
    Stack() : topIndex(-1) {}

    void push(const T& value) {
        if (topIndex >= Capacity - 1) {
            throw "Стек полон!";
        }
        data[++topIndex] = value;
    }

    T pop() {
        if (topIndex < 0) {
            throw "Стек пуст!";
        }
        return data[topIndex--];
    }

    const T& top() const {
        if (topIndex < 0) {
            throw "Стек пуст!";
        }
        return data[topIndex];
    }

    bool empty() const {
        return topIndex == -1;
    }

    bool full() const {
        return topIndex == Capacity - 1;
    }

    int size() const {
        return topIndex + 1;
    }
};

// Тестирование
int main() {
    std::cout << "=== Тестирование Stack ===" << std::endl;

    std::cout << "\n1. Нормальная работа:" << std::endl;
    Stack<int, 3> stack;

    stack.push(10);
    stack.push(20);
    stack.push(30);

    std::cout << "Size: " << stack.size() << std::endl;      // 3
    std::cout << "Empty: " << stack.empty() << std::endl;    // 0
    std::cout << "Full: " << stack.full() << std::endl;      // 1

    std::cout << "\nИзвлечение элементов:" << std::endl;
    while (!stack.empty()) {
        std::cout << "Pop: " << stack.pop() << std::endl;
    }
    std::cout << "Empty после извлечения: " << stack.empty() << std::endl;

    std::cout << "\n2. Обработка ошибок:" << std::endl;

    Stack<int, 2> miniStack;

    try {
        std::cout << "Добавление 3 элементов в стек размером 2:" << std::endl;
        miniStack.push(100);
        miniStack.push(200);
        std::cout << "Добавили 2 элемента" << std::endl;

        miniStack.push(300);

    } catch (const char* error_msg) {
        std::cout << "ОШИБКА: " << error_msg << std::endl;
    }

    try {
        std::cout << "\nИзвлечение из пустого стека:" << std::endl;
        Stack<int, 5> emptyStack;
        int value = emptyStack.pop();

    } catch (const char* error_msg) {
        std::cout << "ОШИБКА: " << error_msg << std::endl;
    }

    try {
        std::cout << "\nПросмотр верхнего элемента пустого стека:" << std::endl;
        Stack<int, 5> emptyStack2;
        int topValue = emptyStack2.top();

    } catch (const char* error_msg) {
        std::cout << "ОШИБКА: " << error_msg << std::endl;
    }

    std::cout << "\n3. Работа с разными типами:" << std::endl;

    Stack<std::string, 4> stringStack;
    stringStack.push("Hello");
    stringStack.push("World");

    std::cout << "Top: " << stringStack.top() << std::endl;
    std::cout << "Pop: " << stringStack.pop() << std::endl;
    std::cout << "Top после pop: " << stringStack.top() << std::endl;

    std::cout << "\n4. Граничные случаи:" << std::endl;

    Stack<double, 1> singleStack;
    singleStack.push(3.14);

    std::cout << "Full для стека из 1 элемента: " << singleStack.full() << std::endl;
    std::cout << "Pop единственного элемента: " << singleStack.pop() << std::endl;
    std::cout << "Empty после извлечения: " << singleStack.empty() << std::endl;

    std::cout << "\n=== Все тесты завершены ===" << std::endl;

    return 0;
}