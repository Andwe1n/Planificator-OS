@echo off
chcp 65001 >nul 2>&1
cls
echo ============================================
echo  Heap Scheduler - Windows Compilation
echo ============================================
echo.

REM Clean previous build
if exist heap_scheduler.exe (
    echo Cleaning old executable...
    del heap_scheduler.exe
    echo.
)

echo Compiling with g++ (C++17)...
echo.

REM Compile with g++ (MinGW)
g++ -std=c++17 -I./include src/main.cpp src/scheduler/scheduler.cpp -o heap_scheduler.exe 2>&1

if %ERRORLEVEL% EQU 0 (
    echo.
    echo ============================================
    echo  [SUCCESS] Compilation Successful!
    echo ============================================
    echo.
    echo To run the program:
    echo   heap_scheduler.exe
    echo.
    echo Or just double-click heap_scheduler.exe
    echo.
) else (
    echo.
    echo ============================================
    echo  [ERROR] Compilation Failed!
    echo ============================================
    echo.
    echo Possible solutions:
    echo 1. Install MinGW-w64 from: https://www.mingw-w64.org/
    echo 2. Make sure g++ is in your PATH
    echo 3. Check error messages above
    echo.
)

pause
