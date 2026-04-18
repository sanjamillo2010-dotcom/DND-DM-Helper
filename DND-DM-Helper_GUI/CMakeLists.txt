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
find_package(yaml-cpp CONFIG REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets PrintSupport)


# -------------------------------------------------------
# Shared source files (used by both GUI and tests)
# -------------------------------------------------------
set(SHARED_SOURCES
    src/NPC/alignment.cpp
    src/NPC/classtype.cpp
    src/NPC/divinite.cpp
    src/NPC/Race.cpp
    src/NPC/NPC.cpp

    src/Inventory/armor.cpp
    src/Inventory/weapon.cpp
    src/Inventory/damage_dice.cpp
    src/Inventory/item.cpp

    src/UI/npcbattlestats.cpp
    src/UI/widget.cpp

    src/Export/pdfexporter.cpp

    include/NPC/alignment.h
    include/NPC/classtype.h
    include/NPC/divinite.h
    include/NPC/Race.h
    include/NPC/NPC.h

    include/Inventory/armor.h
    include/Inventory/weapon.h
    include/Inventory/damage_dice.h
    include/Inventory/item.h

    include/UI/npcbattlestats.h
    include/UI/widget.h

    include/Export/pdfexporter.h

    ui/widget.ui
    ui/npcbattlestats.ui
)

# -------------------------------------------------------
# 1. Main GUI executable
# -------------------------------------------------------
set(PROJECT_SOURCES
    src/main.cpp
    src/UI/widget.cpp
    include/UI/widget.h
    ui/widget.ui
    src/UI/npcbattlestats.cpp
    include/UI/npcbattlestats.h
    ui/npcbattlestats.ui
)

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/conf"
     DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/ui)
    qt_add_executable(DND_MG_Helper_GUI
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${SHARED_SOURCES}
        conf/conf.yaml
        conf/NPC_conf.yaml
        conf/Armor_conf.yaml
        conf/Weapon_conf.yaml
        conf/Item_conf.yaml
    )
else()
    if(ANDROID)
        add_library(DND_MG_Helper_GUI SHARED ${PROJECT_SOURCES} ${SHARED_SOURCES})
    else()
        add_executable(DND_MG_Helper_GUI ${PROJECT_SOURCES} ${SHARED_SOURCES})
    endif()
endif()

target_include_directories(DND_MG_Helper_GUI PRIVATE include)

target_link_libraries(DND_MG_Helper_GUI PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::PrintSupport
    yaml-cpp::yaml-cpp
)

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
    install(DIRECTORY conf/ DESTINATION bin/conf)
endif()

# -------------------------------------------------------
# 2. Separate test executable
# -------------------------------------------------------
find_package(GTest CONFIG QUIET)

if(GTest_FOUND)
    message(STATUS "GTest found — building tests")
    enable_testing()

    add_executable(run_tests
        test/tst_armor.cpp
        test/tst_test_main.cpp
        test/tst_classtype.cpp
        test/tst_npc.cpp
        test/tst_race.cpp
        test/tst_item.cpp

        conf/test/conf_Armor_test.yaml
        conf/test/Test_NPC_conf.yaml
        conf/test/empty.yaml

        src/NPC/alignment.cpp
        src/NPC/classtype.cpp
        src/NPC/divinite.cpp
        src/NPC/Race.cpp
        src/NPC/NPC.cpp

        src/Inventory/armor.cpp
        src/Inventory/weapon.cpp
        src/Inventory/damage_dice.cpp
        src/Inventory/item.cpp

        src/UI/npcbattlestats.cpp
        src/UI/widget.cpp

        src/Export/pdfexporter.cpp

        include/NPC/alignment.h
        include/NPC/classtype.h
        include/NPC/divinite.h
        include/NPC/Race.h
        include/NPC/NPC.h

        include/Inventory/armor.h
        include/Inventory/weapon.h
        include/Inventory/damage_dice.h
        include/Inventory/item.h

        include/UI/npcbattlestats.h
        include/UI/widget.h

        include/Export/pdfexporter.h
    )

    target_include_directories(run_tests PRIVATE include)

    target_link_libraries(run_tests PRIVATE
        Qt${QT_VERSION_MAJOR}::Widgets
        yaml-cpp::yaml-cpp
        GTest::gtest_main
        GTest::gmock_main
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::PrintSupport
        yaml-cpp
    )

    set_target_properties(run_tests PROPERTIES
        AUTOMOC ON
        AUTOUIC ON
        AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/ui
    )

    include(GoogleTest)
    gtest_discover_tests(run_tests)
else()
    message(STATUS "GTest NOT found — skipping tests")
endif()
