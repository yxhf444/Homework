#include <iostream>
using namespace std;

class Rectangle {
private:
		double width{0};
    double height{0};
public:
    Rectangle(): width(1), height(1) {
        // cout <<"Создан"<<" 1x1"<<endl;
    }
    Rectangle(double size): width(size), height(size) {
        // cout<<"Создан квадрат с длиной стороны "<<size<<endl;
    }

    Rectangle(double w, double h) : width(w), height(h) {
        // cout << "Создан " << w << "x" << h << endl;
    }


    ~Rectangle() {
        cout << "Удален " << width << "x" << height << endl;
    }
    double area() const { return width * height; }
    double perimeter() const { return 2 * (width + height); }
    bool is_square() const { return width == height; }
    double get_width() { return width; }
    double get_height() { return height; }

    void scale(double factor) {
        if (factor > 0) {
            width = factor*width;
            height = factor*height;
            cout<<"Текуший размер "<<width<<"x"<<height<<endl;
        }
        else {
            cout<<"error"<<endl;
        }
    }
    void print() const {
        cout<<"Прямоугольник "<<width<<"x"<<height<<"( площадь: "<<width*height<<" периметр: "<<(width+height)*2<<")"<<endl;
    }

    void set_width(double w) {
        if (w > 0) width = w;
        else cout << "Ошибка ширина должна быть> 0" << endl;
    }
    void set_height(double h) {
        if (h > 0) height = h;
        else cout << "Ошибка высота должна быть > 0" << endl;
    }


};

int main () {
    Rectangle rect1;
    rect1.print();
    Rectangle rect2(4.0);
    rect2.print();
    Rectangle rect3(5,6);
    rect3.print();
    rect3.scale(12);
    rect3.print();

}
