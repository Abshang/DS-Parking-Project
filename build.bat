g++ -std=c++17 -O2 -Wall ^
main.cpp ^
src/model/Car.cpp ^
src/model/Node.cpp ^
src/structures/LinkedList.cpp ^
src/structures/QueueLL.cpp ^
src/structures/StackLL.cpp ^
src/parking/ParkingLot.cpp ^
src/parking/ParkingManager.cpp ^
src/gui/RaylibUtils.cpp ^
src/gui/InputHandler.cpp ^
-I src -I src/model -I src/structures -I src/parking -I src/gui ^
-I raylib/raylib-5.0_win64_mingw-w64/include ^
-L raylib/raylib-5.0_win64_mingw-w64/lib ^
-lraylib -lopengl32 -lgdi32 -lwinmm -static ^
-o ParkingLot.exe
