cmake_minimum_required(VERSION 3.15)

project(QtExToolkit
  VERSION 0.0.1
  DESCRIPTION "Qt Extensions App Toolkit Library"
  HOMEPAGE_URL "io.github.whs31"
  LANGUAGES C CXX
)

if(NOT CMAKE_C_STANDARD)
    set(CMAKE_C_STANDARD 17)
    set(CMAKE_C_STANDARD_REQUIRED OFF)
    set(CMAKE_C_EXTENSIONS OFF)
endif(NOT CMAKE_C_STANDARD)

if(NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif(NOT CMAKE_CXX_STANDARD)

if(TARGET ${PROJECT_NAME})
    return()
endif()

set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

find_package(QT NAMES Qt5 REQUIRED COMPONENTS Core)
find_package(Qt5 REQUIRED COMPONENTS Core Quick)

enable_testing()
include_directories(src/c++ include)

file(GLOB_RECURSE QTEX_TK src/c++/*)
file(GLOB_RECURSE QTEX_TK_INCLUDE include/QtExToolkit/*)

set(SRC ${QTEX_TK} ${QTEX_TK_INCLUDE})
add_library(${PROJECT_NAME} STATIC ${SRC})

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt5::Core
    Qt5::Quick
    QtExCore
)

target_include_directories(${PROJECT_NAME} PUBLIC include src/c++)