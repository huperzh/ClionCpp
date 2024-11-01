cmake_minimum_required(VERSION 3.29)
project(ClionCpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "C:/Qt/5.15.2/msvc2019/lib/cmake")

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(ClionCpp main.cpp)
target_link_libraries(ClionCpp
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)

