// structures/StackLL.h
#pragma once
#include "structures/LinkedList.h"
#include <string>

class StackLL
{
private:
    LinkedList list;
    const int capacity;
    const int laneId;

public:
    StackLL(int m, int id = 0); // O(1)

    ~StackLL() { clear(); } // O(m)

    StackLL(const StackLL &) = delete;
    StackLL &operator=(const StackLL &) = delete;

    bool push(Car *car); // O(1)
    Car *pop();          // O(1)
    Car *peek() const;   // O(1)

    bool isEmpty() const; // O(1)
    bool isFull() const;  // O(1)
    int getSize() const;  // O(1)

    int findCar(const std::string &carId) const; // O(m)
    void sortStack();                            // O(m log m)

    void print(const std::string &title = "") const; // O(m)
    int getId() const { return laneId; }             // O(1)

    Node *getHead() const { return list.getHead(); } // O(1)
    Node *getTail() const { return list.getTail(); } // O(1)

    void clear(); // O(m)
};