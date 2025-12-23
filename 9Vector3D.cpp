#include <iostream>
#include <cmath>


class Vector3D {
private:
    double x, y, z;
    mutable double cached_magnitude;
    mutable bool cache_valid;

    static int total_vectors;

public:
    Vector3D(double x = 0.0, double y = 0.0, double z = 0.0)
        : x(x), y(y), z(z), cache_valid(false) {
        total_vectors++;
    }

    Vector3D(const Vector3D& other)
        : x(other.x), y(other.y), z(other.z), cache_valid(false) {
        total_vectors++;
    }

    ~Vector3D() {
        total_vectors--;
    }

    double getX() const { return x; }
    double getY() const { return y; }
    double getZ() const { return z; }

    void setX(double new_x) {
        x = new_x;
        cache_valid = false;
    }
    void setY(double new_y) {
        y = new_y;
        cache_valid = false;
    }
    void setZ(double new_z) {
        z = new_z;
        cache_valid = false;
    }

    double getMagnitude() const {
        if (!cache_valid) {
            cached_magnitude = std::sqrt(x*x + y*y + z*z);
            cache_valid = true;
        }
        return cached_magnitude;
    }

    Vector3D normalized() const {
        double mag = getMagnitude();
        if (mag == 0.0) {
            return Vector3D(0, 0, 0);
        }
        return Vector3D(x / mag, y / mag, z / mag);
    }

    static double dotProduct(const Vector3D& a, const Vector3D& b) {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    bool operator()(double component_value) const {
        return (x == component_value) || (y == component_value) || (z == component_value);
    }

    static int getTotalVectors() {
        return total_vectors;
    }

    Vector3D operator+(const Vector3D& other) const {
        return Vector3D(x + other.x, y + other.y, z + other.z);
    }

    Vector3D operator-(const Vector3D& other) const {
        return Vector3D(x - other.x, y - other.y, z - other.z);
    }

    Vector3D operator*(double scalar) const {
        return Vector3D(x * scalar, y * scalar, z * scalar);
    }

    bool operator==(const Vector3D& other) const {
        const double epsilon = 1e-10;
        return std::abs(x - other.x) < epsilon &&
               std::abs(y - other.y) < epsilon &&
               std::abs(z - other.z) < epsilon;
    }

    bool operator!=(const Vector3D& other) const {
        return !(*this == other);
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector3D& vec);
    friend class Vector3DTest;

private:
    static bool validateComponent(double component) {
        return !std::isnan(component) && !std::isinf(component);
    }
};

int Vector3D::total_vectors = 0;

std::ostream& operator<<(std::ostream& os, const Vector3D& vec) {
    os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    return os;
}

class Vector3DTest {
public:
    static void testStaticCounter() {
        std::cout << "1. Тестирование статического счетчика векторов:" << std::endl;

        int initial_count = Vector3D::getTotalVectors();
        std::cout << "   Начальное количество векторов: " << initial_count << std::endl;

        {
            Vector3D v1(1, 2, 3);
            Vector3D v2(4, 5, 6);
            std::cout << "   После создания 2 векторов: " << Vector3D::getTotalVectors() << std::endl;

            Vector3D v3 = v1;
            std::cout << "   После копирования: " << Vector3D::getTotalVectors() << std::endl;
        }

        std::cout << "   После удаления векторов: " << Vector3D::getTotalVectors() << std::endl;

        if (Vector3D::getTotalVectors() == initial_count) {
            std::cout << "   Счетчик векторов работает корректно!" << std::endl;
        } else {
            std::cout << "   Ошибка в счетчике векторов!" << std::endl;
        }
    }

    static void testCachingMechanism() {
        std::cout << "\n2. Тестирование механизма кеширования:" << std::endl;

        Vector3D v(3, 4, 0);
        std::cout << "   Первый вызов: " << v.getMagnitude() << std::endl;
        std::cout << "   Второй вызов (должен использовать кеш): " << v.getMagnitude() << std::endl;

        v.setX(6);
        std::cout << "   После изменения x: " << v.getMagnitude() << " (пересчитано)" << std::endl;

        if (std::abs(v.getMagnitude() - 7.211102550927978) < 1e-10) {
            std::cout << "   Кеширование работает корректно!" << std::endl;
        } else {
            std::cout << "   Ошибка в кешировании!" << std::endl;
        }
    }

    static void testVectorAddition() {
        std::cout << "\n3. Тестирование сложения векторов:" << std::endl;

        Vector3D v1(1, 2, 3);
        Vector3D v2(4, 5, 6);
        Vector3D result = v1 + v2;

        std::cout << "   " << v1 << " + " << v2 << " = " << result << std::endl;

        if (result.getX() == 5 && result.getY() == 7 && result.getZ() == 9) {
            std::cout << "   Сложение векторов работает корректно!" << std::endl;
        } else {
            std::cout << "   Ошибка в сложении векторов!" << std::endl;
        }
    }

    static void testVectorSubtraction() {
        std::cout << "\n4. Тестирование вычитания векторов:" << std::endl;

        Vector3D v1(5, 7, 9);
        Vector3D v2(1, 2, 3);
        Vector3D result = v1 - v2;

        std::cout << "   " << v1 << " - " << v2 << " = " << result << std::endl;

        if (result.getX() == 4 && result.getY() == 5 && result.getZ() == 6) {
            std::cout << "   Вычитание векторов работает корректно!" << std::endl;
        } else {
            std::cout << "   Ошибка в вычитании векторов!" << std::endl;
        }
    }

    static void testScalarMultiplication() {
        std::cout << "\n5. Тестирование умножения на скаляр:" << std::endl;

        Vector3D v(1, 2, 3);
        Vector3D result = v * 2.5;

        std::cout << "   " << v << " * 2.5 = " << result << std::endl;

        if (result.getX() == 2.5 && result.getY() == 5.0 && result.getZ() == 7.5) {
            std::cout << "   Умножение на скаляр работает корректно!" << std::endl;
        } else {
            std::cout << "   Ошибка в умножении на скаляр!" << std::endl;
        }
    }

    static void testEqualityOperator() {
        std::cout << "\n6. Тестирование операторов сравнения:" << std::endl;

        Vector3D v1(1.0, 2.0, 3.0);
        Vector3D v2(1.0, 2.0, 3.0);
        Vector3D v3(1.1, 2.0, 3.0);

        std::cout << "   " << v1 << " == " << v2 << ": " << (v1 == v2 ? "true" : "false") << std::endl;
        std::cout << "   " << v1 << " == " << v3 << ": " << (v1 == v3 ? "true" : "false") << std::endl;
        std::cout << "   " << v1 << " != " << v3 << ": " << (v1 != v3 ? "true" : "false") << std::endl;

        // Проверка вместо assert
        if (v1 == v2 && v1 != v3) {
            std::cout << "   Операторы сравнения работают корректно!" << std::endl;
        } else {
            std::cout << "   Ошибка в операторах сравнения!" << std::endl;
        }
    }

    static void testDotProduct() {
        std::cout << "\n7. Тестирование скалярного произведения:" << std::endl;

        Vector3D v1(1, 2, 3);
        Vector3D v2(4, 5, 6);
        double result = Vector3D::dotProduct(v1, v2);

        std::cout << " (" << v1 << ", " << v2 << ") = " << result << std::endl;

        if (result == 32) {  // 1*4 + 2*5 + 3*6 = 4 + 10 + 18 = 32
            std::cout << "   Скалярное произведение работает корректно!" << std::endl;
        } else {
            std::cout << "   Ошибка в скалярном произведении!" << std::endl;
        }
    }

    static void testNormalization() {
        std::cout << "\n8. Тестирование нормализации векторов:" << std::endl;

        Vector3D v(3, 4, 0);
        Vector3D normalized = v.normalized();

        std::cout << "   Вектор: " << v << std::endl;
        std::cout << "   Длина: " << v.getMagnitude() << std::endl;
        std::cout << "   Нормализованный: " << normalized << std::endl;
        std::cout << "   Длина нормализованного: " << normalized.getMagnitude() << std::endl;

        if (std::abs(normalized.getMagnitude() - 1.0) < 1e-10) {
            std::cout << "   Нормализация работает корректно!" << std::endl;
        } else {
            std::cout << "   Ошибка в нормализации!" << std::endl;
        }

        Vector3D zero(0, 0, 0);
        Vector3D zero_normalized = zero.normalized();
        std::cout << "   Нулевой вектор: " << zero << std::endl;
        std::cout << "   Нормализованный нулевой вектор: " << zero_normalized << std::endl;

        if (zero_normalized.getMagnitude() == 0.0) {
            std::cout << "   Обработка нулевого вектора корректна!" << std::endl;
        } else {
            std::cout << "   Ошибка при обработке нулевого вектора!" << std::endl;
        }
    }

    static void testFunctionalObject() {
        std::cout << "\n9. Тестирование функтора:" << std::endl;

        Vector3D v(1.5, 2.5, 3.5);

        std::cout << "   Вектор: " << v << std::endl;
        std::cout << "   Проверка наличия компонента 2.5: " << (v(2.5) ? "найден" : "не найден") << std::endl;
        std::cout << "   Проверка наличия компонента 5.0: " << (v(5.0) ? "найден" : "не найден") << std::endl;

        if (v(2.5) == true && v(5.0) == false) {
            std::cout << "   Функтор работает корректно!" << std::endl;
        } else {
            std::cout << "   Ошибка в работе функтора!" << std::endl;
        }
    }

    static void runAllTests() {
        std::cout << "=== Запуск всех тестов Vector3D ===" << std::endl;

        testStaticCounter();
        testCachingMechanism();
        testVectorAddition();
        testVectorSubtraction();
        testScalarMultiplication();
        testEqualityOperator();
        testDotProduct();
        testNormalization();
        testFunctionalObject();

        std::cout << "\n=== Все тесты завершены! ===" << std::endl;
    }
};

int main() {
    std::cout << "=== Демонстрация работы класса Vector3D ===" << std::endl;

    Vector3D v1(1, 2, 3);
    Vector3D v2(4, 5, 6);

    std::cout << "Созданы векторы:" << std::endl;
    std::cout << "  v1 = " << v1 << std::endl;
    std::cout << "  v2 = " << v2 << std::endl;
    std::cout << "  Всего векторов: " << Vector3D::getTotalVectors() << std::endl;

    std::cout << "\nВекторные операции:" << std::endl;
    std::cout << "  v1 + v2 = " << (v1 + v2) << std::endl;
    std::cout << "  v1 - v2 = " << (v1 - v2) << std::endl;
    std::cout << "  v1 * 2.5 = " << (v1 * 2.5) << std::endl;

    std::cout << "\nСкалярное произведение:" << std::endl;
    std::cout << "  v1 ⋅ v2 = " << Vector3D::dotProduct(v1, v2) << std::endl;

    std::cout << "\nДлина и нормализация:" << std::endl;
    std::cout << "  Длина v1: " << v1.getMagnitude() << std::endl;
    std::cout << "  Нормализованный v1: " << v1.normalized() << std::endl;
    std::cout << "  Длина нормализованного: " << v1.normalized().getMagnitude() << std::endl;

    std::cout << "\nИспользование функтора:" << std::endl;
    std::cout << "  В v1 есть компонент 2? " << (v1(2.0) ? "да" : "нет") << std::endl;
    std::cout << "  В v1 есть компонент 5? " << (v1(5.0) ? "да" : "нет") << std::endl;

    std::cout << "\nЦепочка операций:" << std::endl;
    Vector3D result = ((v1 + v2) * 0.5).normalized();
    std::cout << "  ((v1 + v2) * 0.5).normalized() = " << result << std::endl;

    std::cout << "\n=== Запуск unit-тестов ===" << std::endl;
    Vector3DTest::runAllTests();

    std::cout << "\n=== Программа успешно завершена ===" << std::endl;
    return 0;
}
