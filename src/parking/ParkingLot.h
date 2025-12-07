// File: ParkingLot.h
// Description: Manages parking spaces (array of Stacks).

#pragma once
#include "../structures/StackLL.h"
#include <string>

class ParkingLot
{
private:
    StackLL **stacks;
    int numStacks;
    int stackCapacity;

public:
    ParkingLot(int n, int capacity);
    ~ParkingLot();

    int getTotalCars() const;
    int getNumStacks() const { return numStacks; }
    StackLL *getStack(int index) const
    {
        if (index >= 0 && index < numStacks)
            return stacks[index];
        return nullptr;
    }

    bool parkCarInFirstAvailable(Car *car);                               // O(n)
    bool parkCarInSpecificStack(Car *car, int stackId);                   // O(1)
    bool removeCarFromStack(int stackId, const std::string &carId);       // O(1)
    bool findCar(const std::string &carId, int &stackNum, int &position); // O(n^2 worst case)
    void sortStack(int stackId);                                          // O(n log n)

    void printParkingLot() const; // O(n * m)
};
