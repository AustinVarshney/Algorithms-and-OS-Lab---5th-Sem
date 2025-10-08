@echo off
echo ====================================================
echo  CPU Scheduling Simulator - Build and Run Script
echo ====================================================
echo.

:: Check if Qt is installed
where qmake >nul 2>nul
if %errorlevel% neq 0 (
    echo ERROR: Qt qmake not found in PATH!
    echo Please install Qt and add it to your PATH environment variable.
    echo You can download Qt from: https://www.qt.io/download
    echo.
    echo Alternatively, you can specify the full path to qmake:
    echo set PATH=C:\Qt\5.15.2\mingw81_64\bin;%PATH%
    echo.
    pause
    exit /b 1
)

:: Create build directory if it doesn't exist
if not exist build mkdir build
cd build

:: Generate Makefile using qmake
echo Generating Makefile...
qmake ..\SchedulerSimulator.pro
if %errorlevel% neq 0 (
    echo ERROR: Failed to generate Makefile!
    pause
    exit /b 1
)

:: Build the application
echo Building application...
mingw32-make
if %errorlevel% neq 0 (
    echo ERROR: Build failed!
    pause
    exit /b 1
)

:: Run the application if build was successful
echo.
echo Build successful! Starting application...
echo.
if exist release\SchedulerSimulator.exe (
    start release\SchedulerSimulator.exe
) else if exist debug\SchedulerSimulator.exe (
    start debug\SchedulerSimulator.exe
) else if exist SchedulerSimulator.exe (
    start SchedulerSimulator.exe
) else (
    echo ERROR: Could not find the executable!
    pause
    exit /b 1
)

echo Application started successfully!
cd ..
pause