@echo off
chcp 65001 >nul 2>&1
cls

if not exist heap_scheduler.exe (
    echo ============================================
    echo  ERROR: heap_scheduler.exe not found!
    echo ============================================
    echo.
    echo Please compile first by running:
    echo   compile.bat
    echo.
    pause
    exit /b 1
)

echo ============================================
echo  Running Heap Scheduler...
echo ============================================
echo.

heap_scheduler.exe

echo.
echo ============================================
echo  Program ended.
echo ============================================
echo.
pause
