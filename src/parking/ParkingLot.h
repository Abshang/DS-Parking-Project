// File: ParkingLot.h
// Description: Manages parking spaces (array of Stacks).

#pragma once
#include "StackLL.h"

class ParkingLot
{
private:
    StackLL *stacks;
    int numStacks;
    int stackCapacity;

public:
    ParkingLot(int n, int capacity);
    ~ParkingLot();
    // Functions to manage stacks will be added later
};
