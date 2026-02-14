// model/Car.cpp
#include "Car.h"

// constructor with string copy
Car::Car(const std::string &id) : carId(id) {} // O(n)

// constructor with string move
Car::Car(std::string &&id) : carId(std::move(id)) {} // O(1)