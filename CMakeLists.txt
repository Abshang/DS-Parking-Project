cmake_minimum_required(VERSION 3.10)
project(ParkingLotManager VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) 

if(NOT RAYLIB_ROOT_PATH)
    set(RAYLIB_ROOT_PATH "C:/Users/Abshang-pc/Parking_project/raylib/raylib-5.0_win64_mingw-w64" CACHE PATH "Path to your Raylib installation root.")
endif()

message(STATUS "Using Raylib from: ${RAYLIB_ROOT_PATH}")

include_directories(${RAYLIB_ROOT_PATH}/include)
link_directories(${RAYLIB_ROOT_PATH}/lib)

include_directories(
    src/model
    src/structures
    src/parking
    src/gui
)

set(MODEL_SOURCES
    src/model/Car.cpp
    src/model/Node.cpp
)

set(STRUCTURES_SOURCES
    src/structures/LinkedList.cpp
    src/structures/StackLL.cpp
    src/structures/QueueLL.cpp
)

set(PARKING_SOURCES
    src/parking/ParkingLot.cpp
    src/parking/ParkingManager.cpp
)

set(GUI_SOURCES
    src/gui/RaylibUtils.cpp
    src/gui/InputHandler.cpp
)

set(PROJECT_SOURCES
    main.cpp
    ${MODEL_SOURCES}
    ${STRUCTURES_SOURCES}
    ${PARKING_SOURCES}
    ${GUI_SOURCES}
)


add_executable(parking_manager ${PROJECT_SOURCES})

target_link_libraries(parking_manager PRIVATE raylib)

if(WIN32)
    target_link_libraries(parking_manager PRIVATE winmm gdi32)
endif()

if(UNIX AND NOT APPLE)
    target_link_libraries(parking_manager PRIVATE m pthread dl rt X11)
endif()



set_target_properties(parking_manager PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

install(TARGETS parking_manager DESTINATION bin)

message(STATUS "")
message(STATUS "========================================")
message(STATUS "  Parking Lot Manager Configuration")
message(STATUS "========================================")
message(STATUS "  C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "  Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "  Compiler: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "  Raylib Path: ${RAYLIB_ROOT_PATH}")
message(STATUS "========================================")
message(STATUS "")