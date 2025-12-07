// ParkingLot.cpp
#include "parking/ParkingLot.h"
#include <iostream>

ParkingLot::ParkingLot(int n, int capacity)
    : numStacks(n > 0 ? n : 1), stackCapacity(capacity > 0 ? capacity : 1)
{
    stacks = new StackLL *[numStacks];
    for (int i = 0; i < numStacks; ++i)
    {
        stacks[i] = new StackLL(stackCapacity, i + 1);
    }
}

ParkingLot::~ParkingLot()
{
    for (int i = 0; i < numStacks; ++i)
        delete stacks[i]; // ~StackLL() فراخوانی میشه → همه Carها حذف میشن
    delete[] stacks;
}

// پارک در اولین استک خالی
bool ParkingLot::parkCarInFirstAvailable(Car *car)
{
    if (!car)
        return false;

    for (int i = 0; i < numStacks; ++i)
    {
        if (!stacks[i]->isFull())
        {
            stacks[i]->push(car); // مالکیت به Stack منتقل شد
            std::cout << "Car " << car->getId() << " parked in lane " << stacks[i]->getId() << "\n";
            return true;
        }
    }
    std::cout << "Parking Lot is FULL! Cannot park car " << car->getId() << "\n";
    return false;
}

bool ParkingLot::parkCarInSpecificStack(Car *car, int stackId)
{
    if (!car)
        return false;
    if (stackId < 1 || stackId > numStacks)
    {
        std::cout << "Invalid Stack ID " << stackId << "\n";
        return false;
    }

    StackLL *stack = stacks[stackId - 1];
    if (stack->isFull())
    {
        std::cout << "Lane " << stackId << " is FULL! Cannot park car " << car->getId() << "\n";
        return false;
    }

    stack->push(car); // مالکیت منتقل شد
    std::cout << "Car " << car->getId() << " parked in lane " << stackId << "\n";
    return true;
}

// اصلاح اصلی: حذف ماشین + حذف حافظه!
bool ParkingLot::removeCarFromStack(int stackId, const std::string &carId)
{
    if (stackId < 1 || stackId > numStacks)
    {
        std::cout << "Invalid Stack ID " << stackId << "\n";
        return false;
    }

    StackLL *stack = stacks[stackId - 1];
    Car *frontCar = stack->peek();

    if (!frontCar)
    {
        std::cout << "Lane " << stackId << " is EMPTY\n";
        return false;
    }

    if (frontCar->getId() != carId)
    {
        std::cout << "Cannot remove car " << carId << " from lane " << stackId
                  << " (not at the front)\n";
        return false;
    }

    Car *removedCar = stack->pop(); // مالکیت به ما منتقل شد
    delete removedCar;              // مهم! حذف حافظه
    std::cout << "Car " << carId << " removed from lane " << stackId << " and memory freed.\n";
    return true;
}

bool ParkingLot::findCar(const std::string &carId, int &stackNum, int &position)
{
    for (int i = 0; i < numStacks; ++i)
    {
        int pos = stacks[i]->findCar(carId);
        if (pos != -1)
        {
            stackNum = stacks[i]->getId();
            position = pos;
            return true;
        }
    }
    stackNum = -1;
    position = -1;
    return false;
}

void ParkingLot::sortStack(int stackId)
{
    if (stackId < 1 || stackId > numStacks)
    {
        std::cout << "Invalid Stack ID " << stackId << "\n";
        return;
    }
    stacks[stackId - 1]->sortStack();
    std::cout << "Lane " << stackId << " sorted successfully.\n";
}

void ParkingLot::printParkingLot() const
{
    std::cout << "\n================= PARKING LOT STATUS =================\n";
    for (int i = 0; i < numStacks; ++i)
    {
        stacks[i]->print();
    }
    std::cout << "======================================================\n";
}