// QueueLL.h

#pragma once
#include "LinkedList.h"

class QueueLL
{
private:
    LinkedList list;

public:
    QueueLL() = default;
    ~QueueLL() = default;

    QueueLL(const QueueLL &) = delete;
    QueueLL &operator=(const QueueLL &) = delete;

    void enqueue(Car *car); // O(1)
    Car *dequeue();         // O(1)

    Car *front() const; // O(1)

    bool isEmpty() const;
    int getSize() const;

    void print(const std::string &title = "") const;
};
