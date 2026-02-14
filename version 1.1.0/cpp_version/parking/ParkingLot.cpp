// parking/ParkingLot.cpp

#include "ParkingLot.h"

#include <iostream>

// Constructor

ParkingLot::ParkingLot(int n, int capacity)

    : numStacks(n > 0 ? n : 1), stackCapacity(capacity > 0 ? capacity : 1)

{

    stacks = new StackLL *[numStacks];

    for (int i = 0; i < numStacks; ++i)

    {

        stacks[i] = new StackLL(stackCapacity, i + 1);
    }
}

// Destructor

ParkingLot::~ParkingLot()

{

    for (int i = 0; i < numStacks; ++i)

    {

        delete stacks[i];
    }

    delete[] stacks;
}

// Get total number of cars in the parking lot

int ParkingLot::getTotalCars() const

{

    int total = 0;

    for (int i = 0; i < numStacks; ++i)

    {

        total += stacks[i]->getSize();
    }

    return total;
}

// Park car in the first available stack

bool ParkingLot::parkCarInFirstAvailable(Car *car)

{

    if (!car)

        return false;

    for (int i = 0; i < numStacks; ++i)

    {

        if (!stacks[i]->isFull())

        {

            stacks[i]->push(car);

            std::cout << "Car " << car->getId() << " parked in lane " << stacks[i]->getId() << std::endl;

            return true;
        }
    }

    std::cout << "Parking lot is full!" << std::endl;

    return false;
}

// Park car in a specific stack by stackId

bool ParkingLot::parkCarInSpecificStack(Car *car, int stackId)

{

    if (!car || stackId < 1 || stackId > numStacks)

        return false;

    StackLL *stack = stacks[stackId - 1];

    if (stack->isFull())

    {

        std::cout << "Lane " << stackId << " is full." << std::endl;

        return false;
    }

    stack->push(car);

    std::cout << "Car " << car->getId() << " parked in lane " << stackId << std::endl;

    return true;
}

// Remove a car from a specific stack

bool ParkingLot::removeCarFromStack(int stackId, const std::string &carId)

{

    if (stackId < 1 || stackId > numStacks)

    {

        std::cout << "ERROR: Invalid stack ID" << std::endl;

        return false;
    }

    StackLL *stack = stacks[stackId - 1];

    int position = stack->findCar(carId);

    if (position == -1)

    {

        std::cout << "Car " << carId << " not found in lane " << stackId << std::endl;

        return false;
    }

    if (position != 1)

    {

        std::cout << "Car " << carId << " is not at the top of stack. Cannot remove." << std::endl;

        return false;
    }

    Car *removedCar = stack->pop();

    delete removedCar;

    std::cout << "Car " << carId << " removed from lane " << stackId << std::endl;

    return true;
}

// Find a car in the entire parking lot

bool ParkingLot::findCar(const std::string &carId, int &stackNum, int &position)

{

    for (int i = 0; i < numStacks; ++i)

    {

        position = stacks[i]->findCar(carId);

        if (position != -1)

        {

            stackNum = stacks[i]->getId();

            return true;
        }
    }

    std::cout << "Car " << carId << " not found in parking lot." << std::endl;

    return false;
}

// Sort a specific stack using merge sort

void ParkingLot::sortStack(int stackId)

{

    if (stackId < 1 || stackId > numStacks)

    {

        std::cout << "ERROR: Invalid stack ID" << std::endl;

        return;
    }

    stacks[stackId - 1]->sortStack();

    std::cout << "Stack " << stackId << " sorted." << std::endl;
}

// Print the status of the parking lot

void ParkingLot::printParkingLot() const

{

    std::cout << "\n=================== PARKING LOT STATUS ===================" << std::endl;

    for (int i = 0; i < numStacks; ++i)

    {

        stacks[i]->print();
    }

    std::cout << "===========================================================" << std::endl;
}
