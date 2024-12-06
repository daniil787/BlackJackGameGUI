cmake_minimum_required(VERSION 3.16)

project(BlackJack VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Multimedia LinguistTools)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)


qt_add_executable(BlackJack
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        GameController.h
        AnimationHandler.h
        AnimationHandler.cpp
        SoundManager.cpp
        DataManager.cpp
        Card.h
        CardLogic.cpp
        Deck.h
        Deck.cpp
        GameController.cpp
        CardAreaWidget.h
        CardAreaWidget.cpp

        SkinManager.h
        SkinManager.cpp
        SoundManager.h
        resourses.qrc
        DataManager.h
        SkinGalleryDialog.h
        SkinGalleryDialog.cpp
        DeckWidget.h
        DeckWidget.cpp

    )

qt_add_translations(BlackJack TS_FILES BlackJack_uk_UA.ts)
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET TestBlackJack APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(BlackJack SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(BlackJack
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(BlackJack PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(BlackJack PRIVATE Qt${QT_VERSION_MAJOR}::Multimedia)


# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.BlackJack)
endif()
set_target_properties(BlackJack PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS BlackJack
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(BlackJack)
endif()
