// model/Car.h
#pragma once 
#include <string>

class Car
{
private:
    std::string carId;

public:
    explicit Car(const std::string &id); // O(1)

    explicit Car(std::string &&id); // O(1)

    const std::string &getId() const noexcept { return carId; } // O(1)

    // using for merge sort 

    bool operator<(const Car &other) const noexcept // O(n)
    {
        return carId < other.carId;
    }
// using for find method 
    bool operator==(const Car &other) const noexcept // O(n)
    {
        return carId == other.carId;
    }
};