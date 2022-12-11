cmake_minimum_required(VERSION 3.22)
project(qt_Demo)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(Qt5_DIR D:\\QT5\\5.12.9\\msvc2017_64\\lib\\cmake\\Qt5)
#set(Qt5_DIR D:\\QT5\\5.12.9\\mingw73_32\\lib\\cmake\\Qt5)


find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        Network
        REQUIRED
        )
set(LINK_DIR ./lib)
link_directories(${LINK_DIR})


QT5_WRAP_UI(project_FORMS_HEADERS selfInfo.ui setting.ui paintWidget.ui)
QT5_ADD_RESOURCES(project_RESOURCE_CPPS res.qrc)

add_executable(qt_Demo main.cpp mainwindow.cpp Q_person.cpp Q_person.h udpListening.cpp udpListening.h tcpFileSender.cpp
        tcpFileSender.h tcpReceiver.cpp tcpReceiver.h userInfo.cpp userInfo.h setting.cpp setting.h
        ${project_FORMS_HEADERS}
        ${project_RESOURCE_CPPS}
        InfoDialog.cpp InfoDialog.h paintWidget.cpp paintWidget.h PaintGracy.cpp PaintGracy.h)
add_executable(test modelTest.cpp)
add_library(xml tinyxml/tinyxml.cpp tinyxml/tinystr.cpp tinyxml/tinyxmlerror.cpp tinyxml/tinyxmlparser.cpp)

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
        xml
        )

