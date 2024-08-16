cmake_minimum_required(VERSION 3.26)
project(Minesweeper)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_PREFIX_PATH "/Users/sergeyshakhbazyan/Qt/6.6.1/macos")

find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

include_directories(${Qt6Widgets_INCLUDE_DIRS})

add_executable(Minesweeper main.cpp
        source/Cell.cpp
        source/Cell.h
        source/Board.cpp
        source/Board.h
        source/MainWindow.cpp
        source/MainWindow.h)

target_link_libraries(Minesweeper Qt6::Widgets)