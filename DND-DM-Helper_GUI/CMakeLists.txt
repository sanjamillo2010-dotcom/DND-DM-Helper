cmake_minimum_required(VERSION 3.5)

if(WIN32)
    set(CMAKE_TOOLCHAIN_FILE "F:/workspace/vcpkg/scripts/buildsystems/vcpkg.cmake")
    set(VCPKG_TARGET_TRIPLET "x64-mingw-dynamic")
endif()

project(DND_MG_Helper_GUI VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        widget.cpp
        widget.h
        widget.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(DND_MG_Helper_GUI
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        NPC.h
        Race.h
        Race.cpp
        classtype.h classtype.cpp
        alignment.h alignment.cpp
        divinite.h divinite.cpp
        NPC.cpp
        widget.cpp
        widget.h
        widget.ui
        conf/conf.yaml
        conf/NPC_conf.yaml
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET DND_MG_Helper_GUI APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(DND_MG_Helper_GUI SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(DND_MG_Helper_GUI
            ${PROJECT_SOURCES}
        )
    endif()
endif()

find_package(yaml-cpp CONFIG REQUIRED)

target_link_libraries(DND_MG_Helper_GUI PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
     yaml-cpp::yaml-cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.DND_MG_Helper_GUI)
endif()
set_target_properties(DND_MG_Helper_GUI PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS DND_MG_Helper_GUI
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(DND_MG_Helper_GUI)

    set_target_properties(DND_MG_Helper_GUI PROPERTIES
        VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
    )

add_custom_command(TARGET DND_MG_Helper_GUI POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/conf
    $<TARGET_FILE_DIR:DND_MG_Helper_GUI>/conf
)

install(DIRECTORY conf/
    DESTINATION bin/conf
)

endif()
