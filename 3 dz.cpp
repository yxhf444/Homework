#include <iostream>
#include <vector>
#include <algorithm>
#include <type_traits>
using namespace std;

template<typename T>
class MiniSmartList {
    vector<T> data_;
    
public:
    void push_back(const T& value) {
        data_.push_back(value);
    }
    
    void pop_back() {
        if (!data_.empty()) {
            data_.pop_back();
        }
    }
    
    size_t size() const {
        return data_.size();
    }
    
    void clear() {
        data_.clear();
    }

    template<typename U = T>
    enable_if_t<is_arithmetic_v<U>, U> sum() const {
        U result = 0;
        for (const auto& item : data_) {
            result += item;
        }
        return result;
    }

    template<typename U = T>
    auto sort() -> enable_if_t<
        is_same_v<decltype(declval<U>() < declval<U>()), bool>
    > {
        std::sort(data_.begin(), data_.end());
    }

    template<typename U = T>
    auto print() const -> enable_if_t<
        is_same_v<decltype(cout << declval<U>()), ostream&>
    > {
        for (const auto& item : data_) {
            cout << item << " ";
        }
        cout << endl;
    }

    void debug_print() const {
        for (const auto& item : data_) {
            if constexpr (is_pointer_v<T>) {
                cout << "[ptr] " << item << " -> " << *item << endl;
            } else {
                cout << "[val] " << item << endl;
            }
        }
    }

    template<typename U>
    bool contains(U&& value) const {
        using CleanType = remove_cv_t<remove_reference_t<U>>;
        
        for (const auto& item : data_) {
            if constexpr (is_same_v<CleanType, T>) {
                if (item == value) return true;
            } else {
                if (item == static_cast<T>(value)) return true;
            }
        }
        return false;
    }
};

int main() {
    MiniSmartList<int> list1;
    list1.push_back(5);
    list1.push_back(2);
    list1.push_back(8);
    list1.push_back(1);
    
    cout << "Size: " << list1.size() << endl;
    cout << "Sum: " << list1.sum() << endl;
    
    cout << "Before sort: ";
    list1.print();
    
    list1.sort();
    cout << "After sort: ";
    list1.print();
    
    cout << "Debug print:" << endl;
    list1.debug_print();

    MiniSmartList<string> list2;
    list2.push_back("banana");
    list2.push_back("apple");
    list2.push_back("cherry");
    
    cout << "Before sort: ";
    list2.print();
    
    list2.sort();
    cout << "After sort: ";
    list2.print();


    int a = 10, b = 20, c = 30;
    MiniSmartList<int*> list3;
    list3.push_back(&a);
    list3.push_back(&b);
    list3.push_back(&c);
    
    list3.debug_print();

    MiniSmartList<int> list4;
    list4.push_back(1);
    list4.push_back(2);
    list4.push_back(3);
    
    int x = 2;
    const int y = 3;
    
    cout << "Contains 2? " << list4.contains(x) << endl;
    cout << "Contains 3? " << list4.contains(y) << endl;
    cout << "Contains 4? " << list4.contains(4) << endl;
    cout << "Contains 1? " << list4.contains(move(x)) << endl;

    struct NoSort {
        int value;
    };
    
    MiniSmartList<NoSort> list5;
    list5.push_back({1});
    list5.push_back({2});


    return 0;
}