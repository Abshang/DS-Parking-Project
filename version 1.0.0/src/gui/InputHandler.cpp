#include "InputHandler.h"
#include <sstream>

// constructor to initialize everything
// O(1)
InputHandler::InputHandler()
    : carIdEditMode(false), stackIdEditMode(false),
      fromStackEditMode(false), toStackEditMode(false),
      highlightTimer(0.0f)
{
    std::memset(carIdBuffer, 0, sizeof(carIdBuffer));         // O(n)
    std::memset(stackIdBuffer, 0, sizeof(stackIdBuffer));     // O(n)
    std::memset(fromStackBuffer, 0, sizeof(fromStackBuffer)); // O(n)
    std::memset(toStackBuffer, 0, sizeof(toStackBuffer));     // O(n)

    outputMessage = "Welcome to Parking Lot Manager! Add cars to queue first."; // O(1)
    highlightCarId.clear();                                                     // O(1)
}

// helper to convert char array to int
// O(n)
int InputHandler::charToInt(const char *str)
{
    if (!str || std::strlen(str) == 0)
        return -1;             // O(1)
    std::stringstream ss(str); // O(n)
    int value;
    ss >> value;                   // O(n)
    return ss.fail() ? -1 : value; // O(1)
}

// update highlight timer
// O(1)
void InputHandler::updateHighlightTimer(float deltaTime)
{
    if (highlightTimer > 0.0f) // O(1)
    {
        highlightTimer -= deltaTime; // O(1)
        if (highlightTimer <= 0.0f)  // O(1)
        {
            highlightTimer = 0.0f;  // O(1)
            highlightCarId.clear(); // O(1)
        }
    }
}

// update textboxes and timers
// O(1)
void InputHandler::update(ParkingManager &manager, int numLanes)
{
    updateTextBoxes();                    // O(1)
    updateHighlightTimer(GetFrameTime()); // O(1)

    if (IsKeyPressed(KEY_ENTER)) // O(1)
    {
        // handle enter key if needed
    }
}

// update textboxes for user input
// O(1) each
void InputHandler::updateTextBoxes()
{
    UpdateModernTextBox(Rectangle{UI_AREA_START_X, UI_AREA_START_Y - 40, BUTTON_WIDTH, 40},
                        carIdBuffer, carIdEditMode, MAX_CAR_ID); // O(1)

    UpdateModernTextBox(Rectangle{UI_AREA_START_X, UI_AREA_START_Y + 11 * (BUTTON_HEIGHT + SPACING), BUTTON_WIDTH, 36},
                        stackIdBuffer, stackIdEditMode, 8); // O(1)

    UpdateModernTextBox(Rectangle{UI_AREA_START_X, UI_AREA_START_Y + 12 * (BUTTON_HEIGHT + SPACING) + 6, BUTTON_WIDTH / 2 - 8, 32},
                        fromStackBuffer, fromStackEditMode, 4); // O(1)

    UpdateModernTextBox(Rectangle{UI_AREA_START_X + BUTTON_WIDTH / 2 + 8, UI_AREA_START_Y + 12 * (BUTTON_HEIGHT + SPACING) + 6, BUTTON_WIDTH / 2 - 8, 32},
                        toStackBuffer, toStackEditMode, 4); // O(1)
}

// find a car in parking
// O(n)
void InputHandler::handleFindCar(ParkingManager &manager)
{
    std::string carId = carIdBuffer;
    int stackNum = -1, position = -1;

    if (carId.empty()) // O(1)
    {
        outputMessage = "ERROR: Enter Car ID for search."; // O(1)
    }
    else if (manager.findCar(carId, stackNum, position)) // O(n)
    {
        outputMessage = "Found " + carId + " in Lane " + std::to_string(stackNum) +
                        " at Position " + std::to_string(position) + "."; // O(n)
        highlightCarId = carId;                                           // O(1)
        highlightTimer = 5.0f;                                            // O(1)
    }
    else
    {
        outputMessage = "Car " + carId + " not found."; // O(n)
        highlightCarId.clear();                         // O(1)
    }
}

// park car in first available lane
// O(1)
void InputHandler::handleParkFirst(ParkingManager &manager)
{
    if (manager.addCar()) // O(1)
    {
        outputMessage = "Car dequeued and parked in first available lane."; // O(1)
    }
    else
    {
        outputMessage = "Parking Lot is FULL, or Queue is EMPTY."; // O(1)
    }
}

// park car in specific lane
// O(1) for checking input, O(n) for parking car
void InputHandler::handleParkSpecific(ParkingManager &manager, int numLanes)
{
    int stackId = charToInt(stackIdBuffer); // O(n)
    if (stackId < 1 || stackId > numLanes)  // O(1)
    {
        outputMessage = "ERROR: Invalid Stack ID (1-" + std::to_string(numLanes) + ")."; // O(n)
    }
    else if (manager.addCarToStack(stackId)) // O(n)
    {
        outputMessage = "Car parked in Lane " + std::to_string(stackId) + "."; // O(n)
    }
    else
    {
        outputMessage = "ERROR: Lane " + std::to_string(stackId) +
                        " is FULL, or Queue is EMPTY."; // O(n)
    }
}

// remove car from parking
// O(n) for find and remove
void InputHandler::handleRemoveCar(ParkingManager &manager)
{
    std::string carId = carIdBuffer;
    if (carId.empty()) // O(1)
    {
        outputMessage = "ERROR: Enter Car ID to remove."; // O(1)
        return;
    }

    int stackNum = -1, position = -1;
    if (!manager.findCar(carId, stackNum, position)) // O(n)
    {
        outputMessage = "ERROR: Car " + carId + " not found in parking lot."; // O(n)
        return;
    }

    if (position != 1) // O(1)
    {
        outputMessage = "Car " + carId + " is not at Stack Head (Position 1). Removal NOT allowed."; // O(n)
        return;
    }

    if (manager.removeCarFromStack(stackNum, carId)) // O(n)
    {
        outputMessage = "Car " + carId + " removed from Lane " + std::to_string(stackNum) + "."; // O(n)
        highlightCarId = carId;                                                                  // O(1)
        highlightTimer = 5.0f;                                                                   // O(1)
    }
    else
    {
        outputMessage = "ERROR: Failed to remove car " + carId + "."; // O(n)
    }
}

// sort stack with merge sort
// O(m log m)
void InputHandler::handleSortStack(ParkingManager &manager, int numLanes)
{
    int stackId = charToInt(stackIdBuffer); // O(n)
    if (stackId < 1 || stackId > numLanes)  // O(1)
    {
        outputMessage = "ERROR: Invalid Stack ID (1-" + std::to_string(numLanes) +
                        ") for sorting."; // O(n)
        return;
    }
    manager.sortStack(stackId);                                                                   // O(m log m)
    outputMessage = "Lane " + std::to_string(stackId) + " sorted using Merge Sort (O(m log m))."; // O(n)
}

// move cars from one stack to another
// O(n)
void InputHandler::handleMoveStack(ParkingManager &manager, int numLanes)
{
    int fromId = charToInt(fromStackBuffer); // O(n)
    int toId = charToInt(toStackBuffer);     // O(n)

    if (fromId < 1 || fromId > numLanes || toId < 1 || toId > numLanes) // O(1)
    {
        outputMessage = "ERROR: Invalid Stack ID for Move operation."; // O(n)
        return;
    }
    if (fromId == toId) // O(1)
    {
        outputMessage = "ERROR: Cannot move stack to itself."; // O(1)
        return;
    }

    manager.moveStack(fromId, toId); // O(n)
}

// add car to queue
// O(1) for enqueueing
void InputHandler::handleAddCarToQueue(QueueLL &queue)
{
    std::string carId = carIdBuffer;
    if (carId.empty()) // O(1)
    {
        outputMessage = "ERROR: Enter Car ID to add to queue."; // O(1)
        return;
    }

    queue.enqueue(new Car(carId));                             // O(1)
    outputMessage = "Car " + carId + " added to entry queue."; // O(n)
    clearInput(carIdBuffer);                                   // O(1)
}
