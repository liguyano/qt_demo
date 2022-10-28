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
set(LINK_DIR ./lib)
link_directories(${LINK_DIR})
QT5_WRAP_UI(project_FORMS_HEADERS setting.ui)
QT5_ADD_RESOURCES(project_RESOURCE_CPPS setting.qrc)

set(public_include ${CMAKE_CURRENT_SOURCE_DIR}/cmake-build-debug/qt_Demo_autogen/include/)
# 拷贝 main.cpp 到 public_include 中
execute_process(COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/cmake-build-release/ui_setting.h ${public_include})
message("copy succed")
set(public_include ${CMAKE_CURRENT_SOURCE_DIR}/cmake-build-release/qt_Demo_autogen/include/)
# 拷贝 main.cpp 到 public_include 中
execute_process(COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/cmake-build-release/ui_setting.h ${public_include})
message("copy succed")

add_executable(qt_Demo main.cpp mainwindow.cpp Q_person.cpp Q_person.h tcpListening.cpp tcpListening.h tcpSock.cpp
        tcpSock.h tcpReceiver.cpp tcpReceiver.h userInfo.cpp userInfo.h setting.cpp setting.h
        ${project_FORMS_HEADERS}
        )
add_executable(test modelTest.cpp tcpSock.cpp tcpSock.h tcpReceiver.cpp tcpReceiver.h)
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

