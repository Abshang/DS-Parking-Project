// LinkedList.h
#pragma once
#include "../model/Node.h"
#include <iostream>
#include <string>

class LinkedList
{
private:
    Node *head;
    Node *tail;
    int size;

    static Node *merge(Node *left, Node *right);
    static void split(Node *source, Node *&left, Node *&right);
    static void mergeSortHelper(Node *&headRef);

public:
    LinkedList();
    ~LinkedList();

    // O(1)
    void pushBack(Car *car);

    // O(1)
    Car *popFront();

    // O(1)
    bool isEmpty() const;
    int getSize() const;

    // O(n)
    int findPosition(const std::string &carId) const;

    // O(n log n)
    void mergeSort();

    // O(n)
    void printList() const;

    // O(1)
    Car *getFront() const;

    // O(n)
    void clear(bool deleteCars = false);
};
