// structures/LinkedList.h

#pragma once

#include "model/Node.h"

#include <iostream>

#include <string>

class LinkedList

{

private:
    Node *head;

    Node *tail;

    int size;

    // Merge Sort helpers

    static Node *merge(Node *left, Node *right); // O(n)

    static void split(Node *source, Node *&left, Node *&right); // O(n)

    static void mergeSortHelper(Node *&headRef); // O(n log n)

public:
    LinkedList(); // O(1)

    ~LinkedList(); // O(n)

    void pushBack(Car *car); // O(1)

    void pushFront(Car *car); // O(1)

    Car *popFront(); // O(1)

    bool isEmpty() const; // O(1)

    int getSize() const; // O(1)

    Car *getFront() const; // O(1)

    int findPosition(const std::string &carId) const; // O(n)

    void mergeSort(); // O(n log n)

    void printList() const; // O(n)

    Node *getHead() const { return head; } // O(1)

    Node *getTail() const { return tail; } // O(1)

    void clear(); // O(n)

    LinkedList(const LinkedList &) = delete;

    LinkedList &operator=(const LinkedList &) = delete;
};