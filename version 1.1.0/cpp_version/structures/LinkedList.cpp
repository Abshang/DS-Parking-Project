// structures/LinkedList.cpp

#include "LinkedList.h"

#include <iostream>

// O(1)

LinkedList::LinkedList() : head(nullptr), tail(nullptr), size(0) {}

// O(n)

LinkedList::~LinkedList()

{

    clear();
}

// O(1)

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

// O(1)

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

// O(1)

Car *LinkedList::popFront()

{

    if (isEmpty())

        return nullptr;

    Node *tmp = head;

    Car *car = tmp->car;

    head = head->next;

    if (!head)

        tail = nullptr;

    delete tmp;

    --size;

    return car;
}

// O(1)

bool LinkedList::isEmpty() const { return head == nullptr; }

// O(1)

int LinkedList::getSize() const { return size; }

// O(1)

Car *LinkedList::getFront() const

{

    return head ? head->car : nullptr;
}

// O(n)

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

// O(n)

Node *LinkedList::merge(Node *left, Node *right)

{

    if (!left)

        return right;

    if (!right)

        return left;

    if (!left->car)

        return merge(left->next, right);

    if (!right->car)

        return merge(left, right->next);

    if (left->car->getId() <= right->car->getId())

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

// O(n)

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

// O(n log n)

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

// O(n log n)

void LinkedList::mergeSort()

{

    mergeSortHelper(head);

    tail = head;

    while (tail && tail->next)

        tail = tail->next;
}

void LinkedList::printList() const

{

    if (isEmpty())

    {

        std::cout << "[Empty]\n";

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

    std::cout << " -> Bottom\n";
}

// O(n)

void LinkedList::clear()

{

    Node *cur = head;

    while (cur)

    {

        Node *next = cur->next;

        delete cur;

        cur = next;
    }

    head = tail = nullptr;

    size = 0;
}
