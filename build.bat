@echo off
chcp 65001 > nul
echo.
echo ==================================================
echo     PARKING LOT PROJECT - COMPLETE BUILD SCRIPT  
echo ==================================================
echo.

rem ساخت پوشه خروجی
if not exist "bin" mkdir bin

rem پاک کردن فایل قدیمی
if exist "bin\parking.exe" del /Q "bin\parking.exe"

echo.
echo [1/3] Compiling all source files...
g++ -std=c++17 -Wall -Wextra -Wpedantic -g3 ^
    -I src ^
    src/main.cpp ^
    src/model/Car.cpp ^
    src/structures/LinkedList.cpp ^
    src/structures/QueueLL.cpp ^
    src/structures/StackLL.cpp ^
    src/parking/ParkingLot.cpp ^
    src/parking/ParkingManager.cpp ^
    -o bin/parking.exe

if %errorlevel% == 0 (
    echo.
    echo [2/3] BUILD SUCCESSFUL!
    echo ==================================================
    echo   Executable: bin\parking.exe
    echo ==================================================
    echo.
    echo [3/3] Running program...
    echo --------------------------------------------------
    bin\parking.exe
    echo.
    echo --------------------------------------------------
    echo.
    echo ==================================================
    echo          PROJECT TEST COMPLETED SUCCESSFULLY!
    echo ==================================================
    echo.
    echo Press any key to exit...
    pause > nul
) else (
    echo.
    echo [2/3] BUILD FAILED!
    echo ==================================================
    echo Check the error messages above and fix the issues.
    echo Common problems:
    echo   1. Missing header files (.h)
    echo   2. Wrong include paths in .h files
    echo   3. Syntax errors in .cpp files
    echo ==================================================
    echo.
    pause
)