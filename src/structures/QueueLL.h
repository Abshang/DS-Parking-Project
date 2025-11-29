// File: QueueLL.h
// Description: Defines Queue class using LinkedList.

#pragma once
#include "LinkedList.h"
#include "Node.h"

class QueueLL
{
private:
    LinkedList list;

public:
    QueueLL();
    ~QueueLL();
    void enqueue(Car *car);
    Car *dequeue();
    bool isEmpty();
};
