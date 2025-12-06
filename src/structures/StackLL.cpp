// StackLL.cpp
// Implements parking lane with capacity m
#include "StackLL.h"
#include <iostream>

StackLL::StackLL(int m, int id)
    : capacity(m), laneId(id)
{
    if (m <= 0)
    {
        std::cerr << "Error: Stack capacity must be > 0\n";
    }
}

bool StackLL::push(Car *car)
{
    if (isFull())
    {
        std::cout << "Lane " << laneId << " is FULL (" << capacity << " cars)\n";
        return false;
    }
    list.pushBack(car);
    return true;
}

Car *StackLL::pop()
{
    if (isEmpty())
    {
        std::cout << "Lane " << laneId << " is EMPTY\n";
        return nullptr;
    }
    return list.popFront();
}

Car *StackLL::peek() const
{
    return list.getFront();
}

bool StackLL::isEmpty() const { return list.isEmpty(); }
bool StackLL::isFull() const { return list.getSize() == capacity; }
int StackLL::getSize() const { return list.getSize(); }

int StackLL::findCar(const std::string &carId) const
{
    return list.findPosition(carId);
}

void StackLL::sortStack()
{
    list.mergeSort();
}

void StackLL::print(const std::string &title) const
{
    std::cout << "=== Lane " << laneId
              << " | " << getSize() << "/" << capacity << " cars";
    if (!title.empty())
        std::cout << " | " << title;
    std::cout << " ===\n";
    list.printList();
}