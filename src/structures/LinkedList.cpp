// structures/LinkedList.cpp
#include "LinkedList.h"
#include <iostream>

// O(1)
LinkedList::LinkedList() : head(nullptr), tail(nullptr), size(0) {}

// O(n) - Destructor: Calls clear() to delete all nodes. n = list size.
LinkedList::~LinkedList()
{
    clear();
}

// O(1) - Adds a node to the end of the list (Used for Queue enqueue).
void LinkedList::pushBack(Car *car)
{
    if (!car)
        return;

    Node *newNode = new Node(car);
    newNode->next = nullptr;

    if (!head)
    {
        head = tail = newNode;
    }
    else
    {
        tail->next = newNode;
        tail = newNode;
    }
    ++size;
}

// O(1) - Adds a node to the front of the list (Used for Stack push and Queue enqueueFront).
void LinkedList::pushFront(Car *car)
{
    if (!car)
        return;

    Node *newNode = new Node(car);
    newNode->next = head;
    head = newNode;
    if (!tail)
        tail = newNode;
    ++size;
}

// O(1) - Removes and returns the car from the front (Used for Stack pop and Queue dequeue).
Car *LinkedList::popFront()
{
    if (isEmpty())
        return nullptr;

    Node *tmp = head;
    Car *car = tmp->car;
    tmp->car = nullptr;

    head = head->next;
    if (!head)
        tail = nullptr;

    delete tmp;
    --size;
    return car;
}

// O(1) - Checks if the list is empty.
bool LinkedList::isEmpty() const { return head == nullptr; }

// O(1) - Returns the current size.
int LinkedList::getSize() const { return size; }

// O(1) - Returns the car at the front without removal.
Car *LinkedList::getFront() const
{
    return head ? head->car : nullptr;
}

// O(n) - Searches for a car by ID. n = list size.
int LinkedList::findPosition(const std::string &carId) const
{
    Node *current = head;
    int pos = 1;
    while (current)
    {
        if (current->car && current->car->getId() == carId)
            return pos;
        current = current->next;
        ++pos;
    }
    return -1;
}

// O(n) - Merges two sorted lists. n = total nodes in left + right.
Node *LinkedList::merge(Node *left, Node *right)
{
    if (!left)
        return right;
    if (!right)
        return left;

    std::string leftId = left->car ? left->car->getId() : "";
    std::string rightId = right->car ? right->car->getId() : "";

    if (left->car == nullptr || (right->car != nullptr && leftId.compare(rightId) <= 0))
    {
        left->next = merge(left->next, right);
        return left;
    }
    else
    {
        right->next = merge(left, right->next);
        return right;
    }
}

// O(n) - Splits the list into two halves using the fast/slow pointer technique. n = source size.
void LinkedList::split(Node *source, Node *&left, Node *&right)
{
    if (!source || !source->next)
    {
        left = source;
        right = nullptr;
        return;
    }

    Node *slow = source;
    Node *fast = source->next;

    while (fast)
    {
        fast = fast->next;
        if (fast)
        {
            slow = slow->next;
            fast = fast->next;
        }
    }

    left = source;
    right = slow->next;
    slow->next = nullptr;
}

// O(n log n) - Recursive core of Merge Sort. n = current list size.
void LinkedList::mergeSortHelper(Node *&headRef)
{
    if (!headRef || !headRef->next)
        return;

    Node *left = nullptr;
    Node *right = nullptr;
    split(headRef, left, right);

    mergeSortHelper(left);
    mergeSortHelper(right);

    headRef = merge(left, right);
}

// O(n log n) - Public method to start the Merge Sort.
void LinkedList::mergeSort()
{
    mergeSortHelper(head);

    tail = head;
    if (tail)
    {
        while (tail->next)
            tail = tail->next;
    }
}

// O(n) - Displays list contents (for debugging/status). n = list size.
void LinkedList::printList() const
{
    if (isEmpty())
    {
        std::cout << "[Empty]" << std::endl;
        return;
    }

    Node *current = head;
    std::cout << "Top -> ";
    while (current)
    {
        if (current->car)
            std::cout << current->car->getId();
        else
            std::cout << "[NULL]";

        if (current->next)
            std::cout << " -> ";
        current = current->next;
    }
    std::cout << " -> Bottom" << std::endl;
}

// O(n) - Deletes all nodes and their associated Car objects (Crucial for memory management). n = list size.
void LinkedList::clear()
{
    Node *cur = head;
    while (cur)
    {
        Node *next = cur->next;
        cur->car = nullptr;
        delete cur;
        cur = next;
    }
    head = tail = nullptr;
    size = 0;
}