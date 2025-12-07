// File: parking/ParkingManager.cpp
#include "../parking/ParkingManager.h"
#include <iostream>

// سازنده
ParkingManager::ParkingManager(ParkingLot *pLot, QueueLL *pQueue)
    : lot(pLot), entryQueue(pQueue)
{
}

// اضافه کردن ماشین از صف به اولین جای خالی
bool ParkingManager::addCar()
{
    if (entryQueue->isEmpty())
    {
        std::cout << "Entry Queue is EMPTY\n";
        return false;
    }

    Car *car = entryQueue->dequeue();

    if (!lot->parkCarInFirstAvailable(car))
    {
        std::cout << "Parking Lot is FULL. Returning car " << car->getId() << " to front of queue.\n";
        entryQueue->enqueueFront(car); // مهم: به اول صف برمی‌گرده!
        return false;
    }

    std::cout << "Car " << car->getId() << " successfully parked in first available lane.\n";
    return true;
}

// اضافه کردن ماشین به استک مشخص
bool ParkingManager::addCarToStack(int stackId)
{
    if (entryQueue->isEmpty())
    {
        std::cout << "Entry Queue is EMPTY\n";
        return false;
    }

    Car *car = entryQueue->dequeue();

    if (!lot->parkCarInSpecificStack(car, stackId))
    {
        std::cout << "Cannot park in lane " << stackId << ". Returning car to front of queue.\n";
        entryQueue->enqueueFront(car); // به اول صف!
        return false;
    }

    std::cout << "Car " << car->getId() << " parked in specified lane " << stackId << ".\n";
    return true;
}

// خروج ماشین (فقط از بالای استک)
bool ParkingManager::removeCarFromStack(int stackId, const std::string &carId)
{
    if (!lot->removeCarFromStack(stackId, carId))
    {
        std::cout << "Cannot remove car " << carId << " from lane " << stackId << " (not at front or invalid lane)\n";
        return false;
    }
    std::cout << "Car " << carId << " successfully exited from lane " << stackId << ".\n";
    return true;
}

// جستجوی ماشین
bool ParkingManager::findCar(const std::string &carId, int &stackNum, int &position)
{
    if (!lot->findCar(carId, stackNum, position))
    {
        std::cout << "Car " << carId << " NOT FOUND in parking lot.\n";
        return false;
    }
    std::cout << "Car " << carId << " found in Lane " << stackNum
              << " at position " << position << " (1 = top)\n";
    return true;
}

// مرتب‌سازی یک استک
void ParkingManager::sortStack(int stackId)
{
    if (stackId < 1 || stackId > lot->getNumStacks())
    {
        std::cout << "Invalid stack number: " << stackId << "\n";
        return;
    }
    lot->sortStack(stackId);
    std::cout << "Lane " << stackId << " sorted successfully using Merge Sort.\n";
}

// تابع جابه‌جایی — کاملاً درست، بدون برعکس شدن ترتیب!
void ParkingManager::moveStack(int fromStackId, int toStackId)
{
    if (fromStackId < 1 || fromStackId > lot->getNumStacks() ||
        toStackId < 1 || toStackId > lot->getNumStacks())
    {
        std::cout << "Invalid stack number(s)\n";
        return;
    }
    if (fromStackId == toStackId)
    {
        std::cout << "Cannot move stack to itself!\n";
        return;
    }

    StackLL *source = lot->getStack(fromStackId - 1);
    if (source->isEmpty())
    {
        std::cout << "Stack " << fromStackId << " is already empty.\n";
        return;
    }

    // مرحله ۱: همه ماشین‌ها رو با ترتیب درست (قدیمی → جدید) جمع‌آوری می‌کنیم
    LinkedList carsToMove;
    while (!source->isEmpty())
    {
        carsToMove.pushBack(source->pop()); // قدیمی‌ترین اول وارد لیست موقت میشه
    }

    // مرحله ۲: ماشین‌ها رو به استک مقصد و بعدی‌ها منتقل می‌کنیم
    int targetId = toStackId;
    Node *current = carsToMove.getHead(); // شروع از قدیمی‌ترین ماشین

    while (current != nullptr && targetId <= lot->getNumStacks())
    {
        StackLL *target = lot->getStack(targetId - 1);

        while (!target->isFull() && current != nullptr)
        {
            Car *car = current->car;
            current->car = nullptr; // مالکیت منتقل شد

            target->push(car); // push عادی → چون ترتیب درسته، خروجی هم درسته

            std::cout << "Car " << car->getId()
                      << " moved from lane " << fromStackId
                      << " → lane " << targetId << "\n";

            current = current->next;
        }
        targetId++;
    }

    // اگه جا کم بود
    if (current != nullptr)
    {
        std::cout << "Not enough space! Remaining cars returned to original stack " << fromStackId << ".\n";
        // ماشین‌های باقی‌مونده رو برمی‌گردونیم (اختیاری ولی حرفه‌ای)
        while (current != nullptr)
        {
            source->push(current->car);
            current->car = nullptr;
            current = current->next;
        }
    }
}

// نمایش وضعیت کامل
void ParkingManager::printStatus() const
{
    std::cout << "\n";
    std::cout << "========================================================\n";
    std::cout << "                  PARKING SYSTEM STATUS                 \n";
    std::cout << "========================================================\n";
    entryQueue->print("Incoming Cars");
    std::cout << "\n";
    lot->printParkingLot();
    std::cout << "========================================================\n\n";
}