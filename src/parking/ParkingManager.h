// File: parking/ParkingManager.h
#pragma once
#include "../parking/ParkingLot.h"
#include "../structures/QueueLL.h"
#include <string>

class ParkingManager
{
private:
    ParkingLot *lot;
    QueueLL *entryQueue;

public:
    ParkingManager(ParkingLot *pLot, QueueLL *pQueue);
    ~ParkingManager() = default;

    bool addCar();
    bool addCarToStack(int stackId);

    bool removeCarFromStack(int stackId, const std::string &carId);

    bool findCar(const std::string &carId, int &stackNum, int &position);

    void sortStack(int stackId);

    void moveStack(int fromStackId, int toStackId);

    void printStatus() const;
};