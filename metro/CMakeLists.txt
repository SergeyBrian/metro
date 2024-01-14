cmake_minimum_required(VERSION 3.5)

project(Metro VERSION 2.1.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets PrintSupport REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets PrintSupport REQUIRED)

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
        stationellipse.cpp
        stationellipse.h
        graphicsscene.cpp
        graphicsscene.h
        graphicsitemhelper.cpp
        graphicsitemhelper.h
        metro/Route.cpp
        metro/Route.h
        metro/Filesys.cpp
        metro/Filesys.h
        fileselector.cpp
        fileselector.h
        metro/Exceptions.cpp
        metro/Exceptions.h
        metroapp.cpp
        metroapp.h
        metro/search/ISearcher.cpp
        metro/search/ISearcher.h
        metro/search/StupidSearcher.cpp
        metro/search/StupidSearcher.h
        metro/search/Search.h
        metro/search/Search.cpp
        metro/search/Exceptions.cpp
        metro/search/Exceptions.h
        metro/legacy_filesys/LegacyFilesys.cpp
        metro/legacy_filesys/LegacyFilesys.h
        metro/legacy_filesys/Filesys_v2.cpp
        metro/legacy_filesys/Filesys_v2.h
        filesys.cpp
        filesys.h
        metro/search/AStarSearcher.cpp
        metro/search/AStarSearcher.h
        metro/tests/Tests.cpp
        metro/tests/Tests.h
        metro/tests/Benchmark.cpp
        metro/tests/Benchmark.h
        metro/tests/Exceptions.cpp
        metro/tests/Exceptions.h
        benchmarkworker.cpp
        benchmarkworker.h
        benchmarkupdatemitter.cpp
        benchmarkupdatemitter.h
        lib/qcustomplot.cpp
        lib/qcustomplot.h
        metro/search/MoscowStarSearcher.cpp
        metro/search/MoscowStarSearcher.h
)

if (${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Metro MANUAL_FINALIZATION MACOSX_BUNDLE ${PROJECT_SOURCES}
            generatedialog.h generatedialog.cpp generatedialog.ui
            metrowindow.h metrowindow.cpp metrowindow.ui
            benchmarkdialog.h benchmarkdialog.cpp benchmarkdialog.ui
            benchmarkviewer.h benchmarkviewer.cpp benchmarkviewer.ui
    )
else ()
    add_executable(Metro
            ${PROJECT_SOURCES}
    )
endif ()

target_link_libraries(Metro PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::PrintSupport)

set_target_properties(Metro PROPERTIES
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
        MACOSX_BUNDLE_INFO_PLIST platform/macos/Info.plist
)
set(app_icon_macos "${CMAKE_CURRENT_SOURCE_DIR}/img/metro.icns")
set_source_files_properties(${app_icon_macos} PROPERTIES
        MACOSX_PACKAGE_LOCATION "Resources")

if (QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Metro)
endif ()
