cmake_minimum_required(VERSION 3.16)
project(CipherTrace LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Gui Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Widgets)

include_directories(
    CODE
    engine/ds
    engine/core
    engine/detectors
    engine/algo
)

add_executable(CipherTraceGUI
    gui/main_gui.cpp
    gui/MainWindow.cpp
    gui/MainWindow.h
)

target_link_libraries(CipherTraceGUI PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets
)
