// model/Car.h
#pragma once
#include <string>

class Car
{
private:
    std::string carId;

public:
    explicit Car(const std::string &id);

    explicit Car(std::string &&id);

    const std::string &getId() const noexcept { return carId; }

    bool operator<(const Car &other) const noexcept
    {
        return carId < other.carId;
    }

    bool operator==(const Car &other) const noexcept
    {
        return carId == other.carId;
    }
};