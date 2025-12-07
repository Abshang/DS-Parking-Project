// structures/QueueLL.h
#pragma once
#include "LinkedList.h"
#include <string>

class QueueLL
{
private:
    LinkedList list;

public:
    QueueLL() = default;

    ~QueueLL() { clear(); }

    QueueLL(const QueueLL &) = delete;
    QueueLL &operator=(const QueueLL &) = delete;

    void enqueue(Car *car);
    void enqueueFront(Car *car);

    Car *dequeue();
    Car *front() const; // O(1)
    bool isEmpty() const;
    int getSize() const;

    void print(const std::string &title = "") const;

    void clear();
};