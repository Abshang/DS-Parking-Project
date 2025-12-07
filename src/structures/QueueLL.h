// structures/QueueLL.h
#pragma once
#include "structures/LinkedList.h"
#include <string>

class QueueLL
{
private:
    LinkedList list;

public:
    QueueLL() = default; // O(1)

    ~QueueLL() { clear(); } // O(n)

    QueueLL(const QueueLL &) = delete;
    QueueLL &operator=(const QueueLL &) = delete;

    void enqueue(Car *car);      // O(1)
    void enqueueFront(Car *car); // O(1)

    Car *dequeue();       // O(1)
    Car *front() const;   // O(1)
    bool isEmpty() const; // O(1)
    int getSize() const;  // O(1)

    void print(const std::string &title = "") const; // O(n)

    void clear(); // O(n)
};