cmake_minimum_required(VERSION 3.16)
project(SchedulerSimulator)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets)

set(SOURCES
    main.cpp
    schedulerwindow.cpp
    schedulingcore.cpp
)

set(HEADERS
    schedulerwindow.h
    schedulingcore.h
)

add_executable(SchedulerSimulator ${SOURCES} ${HEADERS})

target_link_libraries(SchedulerSimulator Qt5::Core Qt5::Widgets)

# Set output directory
set_target_properties(SchedulerSimulator PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)