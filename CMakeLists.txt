cmake_minimum_required(VERSION 3.16)

project(CuteSockets VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

set(SOURCES
    # cmake-format: sort
    src/appmanager.cpp
    src/tcpclient.cpp
    src/tcpserver.cpp
    src/udpserver.cpp
)

set(HEADER
    # cmake-format: sort
    inc/public/CuteSockets/appmanager.h
    inc/public/CuteSockets/tcpclient.h
    inc/public/CuteSockets/tcpserver.h
    inc/public/CuteSockets/udpserver.h
)

set(QML
    # cmake-format: sort
    Main.qml
    qml/ClientTab.qml
    qml/ServerTab.qml
    qml/UdpTab.qml
)

set(RESOURCES

)


find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)
qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appCuteSockets main.cpp)
target_include_directories(appCuteSockets PRIVATE inc/public/CuteSockets)

qt_add_qml_module(
    appCuteSockets
    URI             CuteSockets
    RESOURCE_PREFIX /qml
    VERSION         1.0
    QML_FILES       ${QML}
    SOURCES         ${SOURCES} ${HEADER}
    RESOURCES       ${RESOURCES}
)


## Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
## If you are developing for iOS or macOS you should consider setting an
## explicit, fixed bundle identifier manually though.
#set_target_properties(appCuteSockets PROPERTIES
##    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appCuteSockets
#    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
#    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
#    MACOSX_BUNDLE TRUE
#    WIN32_EXECUTABLE TRUE
#)

target_link_libraries(appCuteSockets
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appCuteSockets
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
