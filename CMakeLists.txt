cmake_minimum_required(VERSION 3.14)
project(RoguelikeSurvivor VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES_ENEMY "source/enemies/*.cpp")
file(GLOB SOURCES_PLAYER "source/player/*.cpp")
file(GLOB SOURCE_MANAGER "source/*.cpp")
list(APPEND SOURCES ${SOURCES_ENEMY} ${SOURCES_PLAYER} ${SOURCE_MANAGER} main.cpp)

add_executable(survivor ${SOURCES})

target_include_directories(survivor PRIVATE include include/enemies include/player)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
target_link_libraries(survivor sfml-graphics sfml-window sfml-system)