// structures/QueueLL.cpp
#include "structures/QueueLL.h"
#include <iostream>

void QueueLL::enqueue(Car *car)
{
    if (car)
        list.pushBack(car);
}

void QueueLL::enqueueFront(Car *car)
{
    if (car)
        list.pushFront(car);
}

Car *QueueLL::dequeue()
{
    return list.popFront();
}

Car *QueueLL::front() const
{
    return list.getFront();
}

bool QueueLL::isEmpty() const
{
    return list.isEmpty();
}

int QueueLL::getSize() const
{
    return list.getSize();
}

void QueueLL::print(const std::string &title) const
{
    std::cout << "=== Entry Queue ";
    if (!title.empty())
        std::cout << "| " << title << " ";
    std::cout << "| Size: " << getSize() << " ===\n";

    if (isEmpty())
    {
        std::cout << "[Empty]\n";
    }
    else
    {
        list.printList();
    }
}

void QueueLL::clear()
{
    Node *current = list.getHead();
    while (current)
    {
        delete current->car;
        current->car = nullptr;
        current = current->next;
    }
    list.clear();
}