// structures/StackLL.cpp
#include "StackLL.h"
#include <iostream>

// O(1)
StackLL::StackLL(int m, int id)
    : capacity(m > 0 ? m : 1), laneId(id)
{
    if (m <= 0)
        std::cerr << "Warning: Stack capacity must be > 0. Using capacity = 1.\n";
}

// O(1)
bool StackLL::push(Car *car)
{
    if (!car)
        return false;

    if (isFull())
    {
        std::cout << "Lane " << laneId << " is FULL (" << capacity << " cars)\n";
        return false;
    }

    list.pushFront(car);
    return true;
}

// O(1)
Car *StackLL::pop()
{
    Car *car = list.popFront();
    if (!car)
        std::cout << "Lane " << laneId << " is EMPTY\n";
    return car;
}

// O(1)
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

    if (isEmpty())
        std::cout << "[Empty]\n";
    else
        list.printList();
}

// O(m)
void StackLL::clear()
{
    Node *current = list.getHead();
    while (current)
    {
        delete current->car;
        current = current->next;
    }

    list.clear();
}
