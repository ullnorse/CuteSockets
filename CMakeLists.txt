cmake_minimum_required(VERSION 3.16)

project(CuteSockets VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appCuteSockets
    main.cpp
)

qt_add_qml_module(appCuteSockets
    URI CuteSockets
    VERSION 1.0
    QML_FILES Main.qml ui/ClientTab.qml ui/ServerTab.qml ui/UdpTab.qml ui/AboutTab.qml
    QML_FILES
    RESOURCES qml.qrc
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appCuteSockets PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appCuteSockets
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appCuteSockets
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appCuteSockets
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
