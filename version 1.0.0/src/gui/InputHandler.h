#pragma once
#include "raylib.h"
#include "parking/ParkingManager.h" // correct path
#include "structures/QueueLL.h"
#include "gui/RaylibUtils.h"
#include <string>
#include <cstring>

class InputHandler
{
private:
    // input buffers for car and stack ids
    // O(1)
    char carIdBuffer[32];
    char stackIdBuffer[32];
    char fromStackBuffer[32];
    char toStackBuffer[32];

    // flags to track which fields are being edited
    // O(1)
    bool carIdEditMode;
    bool stackIdEditMode;
    bool fromStackEditMode;
    bool toStackEditMode;

    // message to show in output
    // O(1)
    std::string outputMessage;
    std::string highlightCarId; // car to highlight
    float highlightTimer;       // for timer based highlighting

    // constants for car id and stack id sizes
    static const int MAX_CAR_ID = 32;   // O(1)
    static const int MAX_STACK_ID = 10; // O(1)

    // helper function to convert char array to int
    // O(n)
    int charToInt(const char *str);

public:
    // clear a given input buffer (safe)
    // O(1)
    void clearInput(char *buffer) { std::memset(buffer, 0, 32); }

    // constructor
    // O(1)
    InputHandler();

    // update method (call every frame to handle input and UI)
    // O(1)
    void update(ParkingManager &manager, int numLanes);

    // update only textboxes
    // O(1) each call
    void updateTextBoxes();

    // update highlight timer (called with deltaTime)
    // O(1)
    void updateHighlightTimer(float deltaTime);

    // Getters for buffer content
    // O(1)
    const char *getCarIdBuffer() const { return carIdBuffer; }
    const char *getStackIdBuffer() const { return stackIdBuffer; }
    const char *getFromStackBuffer() const { return fromStackBuffer; }
    const char *getToStackBuffer() const { return toStackBuffer; }

    // Edit mode getters (for toggling)
    // O(1)
    bool &isCarIdEditMode() { return carIdEditMode; }
    bool &isStackIdEditMode() { return stackIdEditMode; }
    bool &isFromStackEditMode() { return fromStackEditMode; }
    bool &isToStackEditMode() { return toStackEditMode; }

    // Output message and highlight accessors
    // O(1)
    const std::string &getOutputMessage() const { return outputMessage; }
    const std::string &getHighlightCarId() const { return highlightCarId; }

    // setter for output message (avoids const_cast)
    // O(1)
    void setOutputMessage(const std::string &msg) { outputMessage = msg; }

    // setters for edit modes
    // O(1)
    void setCarIdEditMode(bool mode) { carIdEditMode = mode; }
    void setStackIdEditMode(bool mode) { stackIdEditMode = mode; }
    void setFromStackEditMode(bool mode) { fromStackEditMode = mode; }
    void setToStackEditMode(bool mode) { toStackEditMode = mode; }

    // action handlers
    // O(n) depending on the operation
    void handleFindCar(ParkingManager &manager);
    void handleParkFirst(ParkingManager &manager);
    void handleParkSpecific(ParkingManager &manager, int numLanes);
    void handleRemoveCar(ParkingManager &manager);
    void handleSortStack(ParkingManager &manager, int numLanes);
    void handleMoveStack(ParkingManager &manager, int numLanes);
    void handleAddCarToQueue(QueueLL &queue);
};
