cmake_minimum_required(VERSION 3.16)
project(InventoryGUI VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# required for Qt's signal/slot system to work (MOC step)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(InventoryGUI
    src/main.cpp
    src/main_window.cpp
    src/display.cpp
    src/perform_transaction.cpp
    src/validate.cpp
    include/common.h
)

target_include_directories(InventoryGUI PRIVATE include)
target_link_libraries(InventoryGUI PRIVATE Qt6::Widgets)
