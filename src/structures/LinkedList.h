// structures/LinkedList.h
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

    // Merge Sort helpers
    static Node *merge(Node *left, Node *right);
    static void split(Node *source, Node *&left, Node *&right);
    static void mergeSortHelper(Node *&headRef);

public:
    LinkedList();
    ~LinkedList();

    void pushBack(Car *car);  // O(1)
    void pushFront(Car *car); // O(1)
    Car *popFront();

    bool isEmpty() const; // O(1)
    int getSize() const;  // O(1)
    Car *getFront() const;

    int findPosition(const std::string &carId) const; // O(n)

    void mergeSort(); // O(n log n)

    void printList() const; // O(n)

    Node *getHead() const { return head; }
    Node *getTail() const { return tail; }

    void clear();
    LinkedList(const LinkedList &) = delete;
    LinkedList &operator=(const LinkedList &) = delete;
};