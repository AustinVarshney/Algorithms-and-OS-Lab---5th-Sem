# CPU Scheduling Simulator - Qt GUI

This is a graphical user interface (GUI) application for simulating CPU scheduling algorithms, built using Qt Framework. It preserves all the original algorithm implementations while providing an intuitive visual interface.

## Features

- **Three Scheduling Algorithms**:
  - Round Robin (RR) with configurable time quantum
  - Shortest Job First (SJF) - Non-preemptive
  - Shortest Remaining Time First (SRTF) - Preemptive

- **Interactive GUI**:
  - Add/Remove processes dynamically
  - Visual Gantt chart representation
  - Step-by-step execution animation
  - Real-time execution log
  - Results table with timing calculations

- **Preserved Original Code**: All your original algorithm logic has been preserved and integrated into the GUI framework.

## Prerequisites

To run this simulator on your Windows system, you need:

1. **Qt Framework** (Qt 5.12 or later)
   - Download from: https://www.qt.io/download
   - Choose the open-source version
   - Install Qt Creator and Qt libraries
   - Make sure to install MinGW compiler with Qt

2. **Environment Setup**:
   - Add Qt's bin directory to your system PATH
   - Example: `C:\Qt\5.15.2\mingw81_64\bin`

## Installation and Running

### Method 1: Using the Batch File (Easiest)

1. Open Command Prompt or PowerShell in the project directory
2. Run the batch file:
   ```cmd
   build_and_run.bat
   ```
3. The script will automatically build and run the application

### Method 2: Manual Build with Qt Creator

1. Open Qt Creator
2. Open the project file: `SchedulerSimulator.pro`
3. Configure the project with MinGW compiler
4. Build and run the project (Ctrl+R)

### Method 3: Command Line Build

1. Open Command Prompt in the project directory
2. Create a build directory:
   ```cmd
   mkdir build
   cd build
   ```
3. Generate Makefile:
   ```cmd
   qmake ..\SchedulerSimulator.pro
   ```
4. Build the application:
   ```cmd
   mingw32-make
   ```
5. Run the executable:
   ```cmd
   release\SchedulerSimulator.exe
   ```

## How to Use the Simulator

### 1. Input Processes
- Click "Add Process" to add new processes
- Set Arrival Time and Burst Time for each process
- Process IDs are automatically assigned (P1, P2, etc.)
- Use "Remove Selected" to delete a process
- Use "Clear All" to start fresh

### 2. Select Algorithm
- Choose from the dropdown:
  - Round Robin (RR) - requires time quantum input
  - Shortest Job First (SJF)
  - Shortest Remaining Time First (SRTF)

### 3. Run Simulation
- Click "Run Simulation" to execute the selected algorithm
- View results in the Results table
- Check the execution log for step-by-step details
- Observe the Gantt chart visualization

### 4. Animation Controls
- Use "Play" to animate the execution step by step
- Use "Pause" to stop animation
- Use "Step Forward/Back" to manually navigate through steps
- Use "Reset" to return to the beginning

## File Structure

```
Lab6/
├── main.cpp                    # Application entry point
├── schedulerwindow.h           # Main window header
├── schedulerwindow.cpp         # Main window implementation
├── schedulingcore.h           # Core scheduling algorithms header
├── schedulingcore.cpp         # Core scheduling algorithms (your original code)
├── SchedulerSimulator.pro     # Qt project file
├── CMakeLists.txt            # CMake build configuration
├── build_and_run.bat         # Windows build script
├── README.md                 # This file
│
├── Original Files (preserved):
├── CombinedScheduling.cpp    # Your original combined implementation
├── RR.cpp                    # Your original Round Robin
├── SJF.cpp                   # Your original SJF
└── SRTF.cpp                  # Your original SRTF
```

## Troubleshooting

### Common Issues:

1. **"qmake not found"**
   - Solution: Add Qt's bin directory to your PATH environment variable

2. **"mingw32-make not found"**
   - Solution: Install Qt with MinGW compiler or add MinGW to PATH

3. **Build errors**
   - Make sure you have Qt 5.12 or later
   - Check that all source files are in the same directory

4. **Application doesn't start**
   - Check if Qt libraries are in PATH
   - Try running from Qt Creator instead

### Getting Help:

If you encounter issues:
1. Check the Qt installation
2. Verify PATH environment variables
3. Try building from Qt Creator IDE
4. Check Qt version compatibility (Qt 5.12+ recommended)

## Technical Details

- **Framework**: Qt 5/6 with Widgets
- **Language**: C++11
- **Compiler**: MinGW (Windows) or GCC/Clang (Linux/Mac)
- **Build System**: qmake (primary) or CMake (alternative)

The application preserves all your original algorithm implementations while providing a modern GUI interface for better visualization and interaction.