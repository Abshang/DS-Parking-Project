// parking/ParkingLot.h

#pragma once

#include "structures/StackLL.h"

#include <string>

class ParkingLot

{

private:
    StackLL **stacks;

    int numStacks;

    int stackCapacity;

public:
    ParkingLot(int n, int capacity); // O(n)

    ~ParkingLot(); // O(n * m)

    int getTotalCars() const; // O(n)

    int getNumStacks() const { return numStacks; } // O(1)

    StackLL *getStack(int index) const // O(1)

    {

        if (index >= 0 && index < numStacks)

            return stacks[index];

        return nullptr;
    }

    bool parkCarInFirstAvailable(Car *car); // O(n)

    bool parkCarInSpecificStack(Car *car, int stackId); // O(1)

    bool removeCarFromStack(int stackId, const std::string &carId); // O(1)

    bool findCar(const std::string &carId, int &stackNum, int &position); // O(n* m)

    void sortStack(int stackId); // O(m log m)

    void printParkingLot() const; // O(n * m)
};
