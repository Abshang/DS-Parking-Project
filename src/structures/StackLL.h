// structures/StackLL.h
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

    // مهم: وقتی Stack نابود میشه، همه Carها رو حذف کنه
    ~StackLL() { clear(); }

    StackLL(const StackLL &) = delete;
    StackLL &operator=(const StackLL &) = delete;

    bool push(Car *car); // O(1) - مالکیت به Stack منتقل میشه
    Car *pop();          // O(1) - مالکیت منتقل میشه به caller
    Car *peek() const;   // O(1)

    bool isEmpty() const;
    bool isFull() const;
    int getSize() const;

    int findCar(const std::string &carId) const; // موقعیت از بالا (1 = top)
    void sortStack();                            // merge sort روی همین لیست

    void print(const std::string &title = "") const;
    int getId() const { return laneId; }

    // --- خیلی مهم برای moveStack بدون برعکس کردن ---
    Node *getHead() const { return list.getHead(); }
    Node *getTail() const { return list.getTail(); }

    // حذف همه ماشین‌ها (مثلاً موقع نابودی یا moveStack)
    void clear(); // همه Carها رو delete می‌کنه + Nodeها
};