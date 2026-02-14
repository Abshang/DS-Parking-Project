#include "QueueLL.h"
#include <iostream>

// O(1)
void QueueLL::enqueue(Car *car)
{
    if (!car)
        return;

    list.pushBack(car);
}

// O(1)
void QueueLL::enqueueFront(Car *car)
{
    if (!car)
        return;

    list.pushFront(car);
}

// O(1)
Car *QueueLL::dequeue()
{
    return list.popFront();
}

// O(1)
Car *QueueLL::front() const
{
    return list.getFront();
}

// O(1)
bool QueueLL::isEmpty() const
{
    return list.isEmpty();
}

// O(1)
int QueueLL::getSize() const
{
    return list.getSize();
}

// O(n)
void QueueLL::print(const std::string &title) const
{
    std::cout << "=== Entry Queue ";
    if (!title.empty())
        std::cout << "| " << title << " ";
    std::cout << "| Size: " << getSize() << " ===\n";

    if (isEmpty())
        std::cout << "[Empty]\n";
    else
        list.printList();
}

// O(n)
void QueueLL::clear()
{
    Node *current = list.getHead();
    while (current)
    {
        delete current->car;
        current = current->next;
    }

    list.clear();
}
