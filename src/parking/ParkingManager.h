// File: ParkingManager.h
// Description: Implements operations: add, remove, find, sort, move cars.

#pragma once
#include "ParkingLot.h"
#include "QueueLL.h"

class ParkingManager
{
private:
    ParkingLot *lot;
    QueueLL *entryQueue;

public:
    ParkingManager(ParkingLot *pLot, QueueLL *pQueue);
    ~ParkingManager();
    // Functions like addCar, removeCar, findCar, sortStack, moveStack will be added later
};
