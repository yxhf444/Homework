#include <iostream>
#include <string>

class Vehicle {
protected:
    std::string make;
    std::string model;
    int year;
    double fuelEfficiency;

public:
    Vehicle(const std::string& make, const std::string& model, int year, double fuelEfficiency)
        : make(make), model(model), year(year), fuelEfficiency(fuelEfficiency) {}

    virtual void startEngine() = 0;
    virtual void stopEngine() = 0;
    virtual std::string getDescription() const = 0;
    virtual double calculateRange(double fuelAmount) const = 0;

    virtual ~Vehicle() = default;

    std::string getMake() const { return make; }
    std::string getModel() const { return model; }
    int getYear() const { return year; }
    double getFuelEfficiency() const { return fuelEfficiency; }
};

class Car : public Vehicle {
private:
    int numberOfDoors;
    double trunkCapacity;

public:
    Car(const std::string& make, const std::string& model, int year,
        double fuelEfficiency, int doors, double trunkCap)
        : Vehicle(make, model, year, fuelEfficiency),
          numberOfDoors(doors), trunkCapacity(trunkCap) {}

    void startEngine() override {
        std::cout << "Двигатель машины запущен: " << make << " " << model << " готов к поездке!" << std::endl;
    }

    void stopEngine() override {
        std::cout << "Двигатель машины остановлен" << std::endl;
    }

    std::string getDescription() const override {
        return make + " " + model + " (" + std::to_string(year) + ") - " +
               std::to_string(numberOfDoors) + " дверей, " +
               std::to_string(trunkCapacity) + " литров багажник, " +
               "эффективность: " + std::to_string(fuelEfficiency) + " км/литр";
    }

    double calculateRange(double fuelAmount) const override {
        return fuelAmount * fuelEfficiency;
    }

    void openTrunk() {
        std::cout << "Багажник открыт. Осталось места: " << trunkCapacity << " литров" << std::endl;
    }

    int getNumberOfDoors() const { return numberOfDoors; }
    double getTrunkCapacity() const { return trunkCapacity; }
};

class Truck : public Vehicle {
private:
    double cargoCapacity;
    bool hasTrailer;
public:
    Truck(const std::string& make, const std::string& model, int year,
          double fuelEfficiency, double cargoCap, bool trailer)
        : Vehicle(make, model, year, fuelEfficiency),
          cargoCapacity(cargoCap), hasTrailer(trailer) {}

    void startEngine() override {
        std::cout << "Двигатель грузовика " << make << " " << model << " запущен! Готов к перевозке грузов." << std::endl;
    }

    void stopEngine() override {
        std::cout << "Двигатель грузовика " << make << " " << model << " остановлен." << std::endl;
    }

    std::string getDescription() const override {
        std::string trailerInfo = hasTrailer ? "с прицепом" : "без прицепа";
        return make + " " + model + " (" + std::to_string(year) + ") - " +
               "грузоподъемность: " + std::to_string(cargoCapacity) + " т, " +
               trailerInfo + ", " +
               "эффективность: " + std::to_string(fuelEfficiency) + " км/литр";
    }

    double calculateRange(double fuelAmount) const override {
        return fuelAmount * fuelEfficiency;
    }

    void loadCargo(double weight) {
        if (weight <= cargoCapacity) {
            std::cout << "Груз массой " << weight << " т загружен в грузовик " << model << std::endl;
        } else {
            std::cout << "Ошибка: груз массой " << weight << " т превышает грузоподъемность " << cargoCapacity << " т" << std::endl;
        }
    }

    void attachTrailer() {
        if (!hasTrailer) {
            hasTrailer = true;
            std::cout << "Прицеп присоединен к грузовику " << model << std::endl;
        } else {
            std::cout << "Прицеп уже присоединен" << std::endl;
        }
    }

    void detachTrailer() {
        if (hasTrailer) {
            hasTrailer = false;
            std::cout << "Прицеп отсоединен от грузовика " << model << std::endl;
        } else {
            std::cout << "Прицеп не присоединен" << std::endl;
        }
    }

    double getCargoCapacity() const { return cargoCapacity; }
    bool getHasTrailer() const { return hasTrailer; }
};

class Motorcycle : public Vehicle {
private:
    int engineSizeCC;
    bool hasSideCar;

public:
    Motorcycle(const std::string& make, const std::string& model, int year,
               double fuelEfficiency, int engineSize, bool sideCar)
        : Vehicle(make, model, year, fuelEfficiency),
          engineSizeCC(engineSize), hasSideCar(sideCar) {}

    void startEngine() override {
        std::cout << "Двигатель мотоцикла " << make << " " << model << " запущен!" << std::endl;
    }

    void stopEngine() override {
        std::cout << "Двигатель мотоцикла " << make << " " << model << " заглушен." << std::endl;
    }

    std::string getDescription() const override {
        std::string sideCarInfo = hasSideCar ? "с коляской" : "без коляски";
        return make + " " + model + " (" + std::to_string(year) + ") - " +
               "двигатель: " + std::to_string(engineSizeCC) + " см в кубе, " +
               sideCarInfo + ", " +
               "эффективность: " + std::to_string(fuelEfficiency) + " км/литр";
    }

    double calculateRange(double fuelAmount) const override {
        return fuelAmount * fuelEfficiency;
    }
    
    void toggleSideCar() {
        hasSideCar = !hasSideCar;
        std::cout << "Коляска " << (hasSideCar ? "установлена на мотоцикл" : "снята с мотоцикла") << " " << make << " " << model << std::endl;
    }

    int getEngineSizeCC() const { return engineSizeCC; }
    bool getHasSideCar() const { return hasSideCar; }
};

int main() {
    Car myCar("Toyota", "Camry", 2023, 15.5, 4, 480.0);
    std::cout << myCar.getDescription() << std::endl;
    myCar.startEngine();
    myCar.openTrunk();
    std::cout << "Запас хода с 50л топлива: " << myCar.calculateRange(50) << " км" << std::endl;
    myCar.stopEngine();

    Truck myTruck("Volvo", "H16", 2022, 8.2, 25.0, true);
    std::cout << myTruck.getDescription() << std::endl;
    myTruck.startEngine();
    myTruck.loadCargo(15.5);
    myTruck.loadCargo(30.0);
    std::cout << "Запас хода с 300л топлива: " << myTruck.calculateRange(300) << " км" << std::endl;
    myTruck.detachTrailer();
    myTruck.stopEngine();

    Motorcycle myBike("Harley-Davidson", "Sport", 2021, 20.5, 1200, false);
    std::cout << myBike.getDescription() << std::endl;
    myBike.startEngine();
    std::cout << "Запас хода с 15л топлива: " << myBike.calculateRange(15) << " км" << std::endl;
    myBike.toggleSideCar();
    myBike.stopEngine();

    return 0;
}
