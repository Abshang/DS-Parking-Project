// File: Car.h
// Description: Defines Car class with carId. Used in LinkedList, Stack, and Queue.

#pragma once
#include <string>

class Car
{
public:
    std::string carId;
    Car(const std::string &id);
};
