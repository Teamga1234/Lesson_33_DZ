#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

class ZooException {
public:
    virtual std::string showMessage() const = 0;
};

class PredatorException : public ZooException {
public:
    std::string showMessage() const override {
        return "Error: add a predator to a cage with non-predators.";
    }
};

class MaxCapacityException : public ZooException {
public:
    std::string showMessage() const override {
        return "Error: cage is at maximum capacity";
    }
};

class NameException : public ZooException {
public:
    NameException() {}
    std::string showMessage() const override {
        return "Error: create animal - name is missing.";
    }
};


class Animal {
    std::string name;
    bool predator;
public:
    Animal(std::string name, bool predator) : name(name), predator(predator) {
        if (name.empty()) throw NameException();
    }
    std::string getName() const { return name; }
    void setName(std::string name) { this->name = name; }
    bool isPredator() const { return predator; }
    void setPredator(bool isPredator) { predator = isPredator; }
    virtual void showDescription() const {
        std::cout << "Animal: " << name << (predator ? " (Predator)" : "") << std::endl;
    }
};
class Fish : public Animal {
    bool deepWater;
public:
    Fish(std::string name, bool predator, bool deepWater)
        : Animal(name, predator), deepWater(deepWater) {}

    bool isDeepWater() const { return deepWater; }
    void setDeepWater(bool deep) { deepWater = deep; }

    void showDescription() const override {
        Animal::showDescription();
        std::cout << (deepWater ? "Deep water fish" : "Shallow water fish") << std::endl;
    }
};

class Bird : public Animal {
    double flightSpeed;
public:
    Bird(std::string name, bool predator, double speed)
        : Animal(name, predator), flightSpeed(speed) {}

    double getFlightSpeed() const { return flightSpeed; }
    void setFlightSpeed(double speed) { flightSpeed = speed; }

    void showDescription() const override {
        Animal::showDescription();
        std::cout << "Flight speed: " << flightSpeed << " km/h" << std::endl;
    }
};

class Mammal : public Animal {
    std::string habitat;
public:
    Mammal(std::string name, bool predator, std::string habitat)
        : Animal(name, predator), habitat(habitat) {}

    std::string getHabitat() const { return habitat; }
    void setHabitat(std::string hab) { habitat = hab; }

    void showDescription() const override {
        Animal::showDescription();
        std::cout << "Habitat: " << habitat << std::endl;
    }
};

class Cage {
    int number;
    int maxAnimals;
    std::vector<Animal*> animals;
public:
    Cage(int number, int maxAnimals) : number(number), maxAnimals(maxAnimals) {}
    int getNumber() const { return number; }
    void setNumber(int num) { number = num; }

    int getMaxAnimals() const { return maxAnimals; }
    void setMaxAnimals(int max) { maxAnimals = max; }

    int getCurrentAnimalCount() const { return animals.size(); }
    void addAnimal(Animal* animal) {
        if (animals.size() >= maxAnimals) {
            throw MaxCapacityException();
        }
        bool containsNonPredator = false;
        for (const auto& a : animals) {
            if (!a->isPredator()) {
                containsNonPredator = true;
                break;
            }
        }
        if (containsNonPredator && animal->isPredator()) {
            throw PredatorException();
        }
        animals.push_back(animal);
    }
    void removeAnimal(Animal* animal) {
        animals.erase(std::remove(animals.begin(), animals.end(), animal), animals.end());
    }

    void showAnimals() const {
        for (const auto& a : animals) {
            a->showDescription();
        }
    }
};

int main() {
    Cage cage(1, 2);
    try {        
        Animal* lion = new Animal("Lion", true);
        cage.addAnimal(lion); 
    }
    catch (ZooException& ex) {
        std::cout << ex.showMessage() << std::endl;
    }
    try {
        Animal* zebra = new Animal("Zebra", false);
        cage.addAnimal(zebra);
    }
    catch (ZooException& ex) {
        std::cout << ex.showMessage() << std::endl;
    }

    try {
        Animal* unnamed = new Animal("", false);
    }
    catch (ZooException& ex) {
        std::cout << ex.showMessage() << std::endl;
    }

}