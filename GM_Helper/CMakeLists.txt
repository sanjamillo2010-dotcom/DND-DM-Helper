cmake_minimum_required(VERSION 3.14)

project(GM_Helper LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Export compile commands for VSCode IntelliSense
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find Qt6 (with Qt5 fallback)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets)

# Find yaml-cpp
find_package(yaml-cpp REQUIRED)

# Locate Qt6 headers (Ubuntu puts them in an arch-specific path)
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

add_executable(GM_Helper
    main.cpp
)

target_include_directories(GM_Helper PRIVATE
    /usr/include/x86_64-linux-gnu/qt6
    /usr/include/x86_64-linux-gnu/qt6/QtCore
    /usr/include/x86_64-linux-gnu/qt6/QtWidgets
    /usr/include/x86_64-linux-gnu/qt6/QtGui
)

target_link_libraries(GM_Helper
    Qt6::Core
    Qt6::Widgets
    yaml-cpp::yaml-cpp
)

include(GNUInstallDirs)
install(TARGETS GM_Helper
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
