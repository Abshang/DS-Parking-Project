// LinkedList.cpp
#include "LinkedList.h"

LinkedList::LinkedList() : head(nullptr), tail(nullptr), size(0) {}

LinkedList::~LinkedList()
{

    Node *cur = head;
    while (cur)
    {
        Node *next = cur->next;
        delete cur->car;
        delete cur;
        cur = next;
    }
    head = tail = nullptr;
    size = 0;
}

void LinkedList::pushBack(Car *car)
{
    //  O(1)
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

Car *LinkedList::popFront()
{
    // O(1)
    if (!head)
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

bool LinkedList::isEmpty() const { return head == nullptr; }

int LinkedList::getSize() const { return size; }

int LinkedList::findPosition(const std::string &carId) const
{
    //  O(n)
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

Node *LinkedList::merge(Node *left, Node *right)
{

    if (!left)
        return right;
    if (!right)
        return left;

    if (left->car->getId().compare(right->car->getId()) <= 0)
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

void LinkedList::split(Node *source, Node *&left, Node *&right)
{
    //  O(n)
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

void LinkedList::mergeSort()
{
    //  O(n log n)
    mergeSortHelper(head);

    tail = head;
    if (tail)
    {
        while (tail->next)
            tail = tail->next;
    }
}

Car *LinkedList::getFront() const
{
    // O(1)
    return isEmpty() ? nullptr : head->car;
}

void LinkedList::printList() const
{
    //  O(n)
    if (isEmpty())
    {
        std::cout << "[Empty]" << std::endl;
        return;
    }
    Node *current = head;
    std::cout << "Top -> ";
    while (current)
    {
        std::cout << current->car->getId();
        if (current->next)
            std::cout << " -> ";
        current = current->next;
    }
    std::cout << " -> Bottom" << std::endl;
}

void LinkedList::clear(bool deleteCars)
{
    // O(n)
    Node *cur = head;
    while (cur)
    {
        Node *next = cur->next;
        if (deleteCars)
            delete cur->car;
        delete cur;
        cur = next;
    }
    head = tail = nullptr;
    size = 0;
}
