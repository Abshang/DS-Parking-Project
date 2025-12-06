// StackLL.h

#pragma once
#include "LinkedList.h"
#include <string>

class StackLL
{
private:
    LinkedList list;
    const int capacity;
    const int laneId;

public:
    StackLL(int m, int id = 0);

    StackLL(const StackLL &) = delete;
    StackLL &operator=(const StackLL &) = delete;

    ~StackLL() = default;

    bool push(Car *car); // O(1)
    Car *pop();          // O(1)
    Car *peek() const;   // O(1)

    bool isEmpty() const;
    bool isFull() const;
    int getSize() const;

    int findCar(const std::string &carId) const;

    void sortStack();

    void print(const std::string &title = "") const;

    int getId() const { return laneId; }
};
