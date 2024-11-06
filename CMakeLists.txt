cmake_minimum_required(VERSION 3.29)
project(ClionCpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "C:/Qt/5.15.2/msvc2019/lib/cmake")

message(STATUS "QT5DIR: " $ENV{QT5DIR})
string(REPLACE "\\" "/" QT5DIR_UNIX $ENV{QT5DIR})

message(STATUS "QT5DIR: " ${QT5DIR_UNIX})

message(STATUS "CMAKE_SOURCE_DIR: " ${CMAKE_SOURCE_DIR})

SET(PRO_DIR ${PROJECT_SOURCE_DIR})
SET(LIB_DIR $<IF:$<CONFIG:Debug>, ${PRO_DIR}/lib/debug, ${PRO_DIR}/lib/release>)
SET(EXE_DIR $<IF:$<CONFIG:Debug>, ${PRO_DIR}/bin/debug, ${PRO_DIR}/bin/release>)

message(${EXE_DIR})
message(${LIB_DIR})

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

include(CGraph/cmake/CGraph-env-include.cmake)

add_executable(ClionCpp
        $<TARGET_OBJECTS:CGraph>
        main.cpp)

target_link_libraries(ClionCpp
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)



#git submodule add git@github.com:ChunelFeng/CGraph.git ./CGraph

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt5${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()
