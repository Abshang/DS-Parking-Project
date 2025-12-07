// structures/StackLL.cpp
#include "structures/StackLL.h"
#include <iostream>

StackLL::StackLL(int m, int id)
    : capacity(m > 0 ? m : 1), laneId(id)
{
    if (m <= 0)
        std::cerr << "Warning: Stack capacity must be > 0. Using capacity = 1.\n";
}

bool StackLL::push(Car *car)
{
    if (!car)
        return false;
    if (isFull())
    {
        std::cout << "Lane " << laneId << " is FULL (" << capacity << " cars)\n";
        return false;
    }
    list.pushFront(car); // مالکیت به Stack منتقل شد
    return true;
}

Car *StackLL::pop()
{
    Car *car = list.popFront();
    if (!car)
        std::cout << "Lane " << laneId << " is EMPTY\n";
    return car; // مالکیت منتقل شد به caller
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
    return list.findPosition(carId); // از 1 شروع میشه (top = 1)
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
    {
        std::cout << "[Empty]\n";
    }
    else
    {
        list.printList();
    }
}

void StackLL::clear()
{
    // حذف همه Carها (چون متعلق به این Stack هستن)
    Node *current = list.getHead();
    while (current)
    {
        delete current->car; // Car واقعی حذف میشه
        current->car = nullptr;
        current = current->next;
    }
    list.clear(); // فقط Nodeها رو پاک می‌کنه
}