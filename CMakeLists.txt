cmake_minimum_required(VERSION 3.5)

project(SDSGUI VERSION 0.1 LANGUAGES CXX)

option(INSTALLER "Build the IFW installer - Make sure QtIFW is in your system PATH" ON)

if(INSTALLER)
    include(CPack)
    include(CPackIFW)
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package( ...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets LinguistTools REQUIRED)

set(TS_FILES SDSGUI_en_GB.ts)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        logindialog.h
        logindialog.cpp
        logindialog.ui
        ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(SDSGUI
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(SDSGUI SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(SDSGUI
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(SDSGUI PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(SDSGUI PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(SDSGUI)
endif()

add_executable(TOKEN_PLACER placer.cpp)
add_dependencies(SDSGUI TOKEN_PLACER)

if(INSTALLER)
    cpack_add_component(SDSGUI DISPLAY_NAME "SchoolDigitalSignage Management Interface" REQUIRED)
    cpack_ifw_configure_component(SDSGUI REQUIRES_ADMIN_RIGHTS)
    install(TARGETS SDSGUI TOKEN_PLACER RUNTIME)
    set(CPACK_GENERATOR "IFW")
endif()

