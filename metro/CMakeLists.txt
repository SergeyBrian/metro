cmake_minimum_required(VERSION 3.5)

project(Metro VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "/Users/sergey/Qt/6.6.1/macos/lib/cmake")

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui


        metro/Color.cpp
        metro/Color.h
        resources.qrc
        img/metro.icns
        metro/Station.cpp
        metro/Station.h
        metro/Metro.cpp
        metro/Metro.h
        metro/Position.cpp
        metro/Position.h
        metro/Utils.cpp
        metro/Branch.cpp
        metro/Branch.h
)

if (${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Metro MANUAL_FINALIZATION MACOSX_BUNDLE ${PROJECT_SOURCES}
            generatedialog.h generatedialog.cpp generatedialog.ui
            metrowindow.h metrowindow.cpp metrowindow.ui)
    #    qt_add_executable(metro
    #            MANUAL_FINALIZATION
    #            ${PROJECT_SOURCES}
    #    )
    # Define target properties for Android with Qt 6 as:
    #    set_property(TARGET metro APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
    #                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
    # For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else ()
    if (ANDROID)
        add_library(Metro SHARED
                ${PROJECT_SOURCES}
        )
        # Define properties for Android with Qt 5 after find_package() calls as:
        #    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else ()
        add_executable(Metro
                ${PROJECT_SOURCES}
        )
    endif ()
endif ()

target_link_libraries(Metro PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(Metro PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER bimbim.bambam.com
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE_ICON_FILE metro.icns
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
)
set(app_icon_macos "${CMAKE_CURRENT_SOURCE_DIR}/img/metro.icns")
set_source_files_properties(${app_icon_macos} PROPERTIES
        MACOSX_PACKAGE_LOCATION "Resources")

if (QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Metro)
endif ()