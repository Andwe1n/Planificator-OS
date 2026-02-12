@echo off
echo ============================================
echo  Heap Scheduler - Windows Compilation
echo ============================================
echo.

REM Clean previous build
if exist heap_scheduler.exe del heap_scheduler.exe

echo Compiling...
echo.

REM Compile with g++ (MinGW)
g++ -std=c++17 ^
    -I./include ^
    src/main.cpp ^
    src/scheduler/scheduler.cpp ^
    -o heap_scheduler.exe

if %ERRORLEVEL% EQU 0 (
    echo.
    echo ============================================
    echo  Compilation Successful!
    echo ============================================
    echo.
    echo To run the program, type: heap_scheduler.exe
    echo.
) else (
    echo.
    echo ============================================
    echo  Compilation Failed!
    echo ============================================
    echo.
    echo Make sure you have MinGW installed and in PATH
    echo.
)

pause
