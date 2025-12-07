// structures/QueueLL.cpp
#include "QueueLL.h"
#include <iostream>

// O(1) - Adds a car to the back of the queue (FIFO standard enqueue).
void QueueLL::enqueue(Car *car)
{
    if (car)
        list.pushBack(car);
}
// O(1) - Adds a car to the front of the queue (Used when lot is full).
void QueueLL::enqueueFront(Car *car)
{
    if (car)
        list.pushFront(car);
}

// O(1) - Removes and returns the car from the front (FIFO dequeue).
Car *QueueLL::dequeue()
{
    return list.popFront();
}

// O(1) - Returns the car at the front (peek).
Car *QueueLL::front() const
{
    return list.getFront();
}

// O(1) - Checks if the queue is empty.
bool QueueLL::isEmpty() const
{
    return list.isEmpty();
}

// O(1) - Returns the number of elements.
int QueueLL::getSize() const
{
    return list.getSize();
}

// O(n) - Prints the contents of the queue. n = queue size.
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

// O(n) - Clears the queue, deleting all stored Car objects. n = queue size.
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