// model/Car.cpp
#include "Car.h"

Car::Car(const std::string &id) : carId(id) {}

Car::Car(std::string &&id) : carId(std::move(id)) {}