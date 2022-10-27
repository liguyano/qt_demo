cmake_minimum_required(VERSION 3.22)
project(qt_Demo)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(Qt5_DIR D:\\QT5\\5.12.9\\msvc2017_64\\lib\\cmake\\Qt5)
#set(Qt5_DIR D:\\QT5\\5.12.9\\mingw73_64\\lib\\cmake\\Qt5)

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        Network
        REQUIRED
        )

add_executable(qt_Demo main.cpp mainwindow.cpp Q_person.cpp Q_person.h tcpListening.cpp tcpListening.h tcpSock.cpp tcpSock.h tcpReceiver.cpp tcpReceiver.h userInfo.cpp userInfo.h)
add_executable(test modelTest.cpp tcpSock.cpp tcpSock.h tcpReceiver.cpp tcpReceiver.h)

target_link_libraries(test
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Network
        )
target_link_libraries(qt_Demo
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Network
        )

