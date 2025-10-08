@echo off
echo Starting CPU Scheduling Simulator...
echo.

cd /d "d:\BTECH SEM-5 3rd Year\Algorithms & OS Lab\Lab6\build\Desktop_Qt_6_9_2_MinGW_64_bit-Debug\debug"

if not exist "SchedulerSimulator.exe" (
    echo ERROR: SchedulerSimulator.exe not found in the expected location!
    echo Current directory: %CD%
    echo.
    echo Please make sure the application has been built properly.
    pause
    exit /b 1
)

echo Found executable. Starting application...
echo Application Directory: %CD%
echo.

SchedulerSimulator.exe

if %errorlevel% neq 0 (
    echo ERROR: Failed to start the application!
    echo Error level: %errorlevel%
    pause
    exit /b 1
) else (
    echo Application started successfully!
    echo.
    echo The CPU Scheduling Simulator GUI should now be visible.
    echo You can close this window.
)

pause