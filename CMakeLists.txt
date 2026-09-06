cmake_minimum_required(VERSION 3.14)
project(RoguelikeSurvivor VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(ENABLE_SANITIZERS "Enable runtime sanitizers" OFF)

file(GLOB SOURCES_ENEMY "source/enemies/*.cpp")
file(GLOB SOURCES_PLAYER "source/player/*.cpp")
file(GLOB SOURCE_MANAGER "source/*.cpp")
file(GLOB SOURCE_STATE "source/State/*.cpp")
list(APPEND SOURCES ${SOURCES_ENEMY} ${SOURCES_PLAYER} ${SOURCE_MANAGER} ${SOURCE_STATE} main.cpp)

add_executable(survivor ${SOURCES})

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(survivor PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )
elseif(MSVC)
    target_compile_options(survivor PRIVATE /W4)
endif()

if(ENABLE_SANITIZERS AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(survivor PRIVATE
        -fsanitize=address,undefined
        -fno-omit-frame-pointer
    )

    target_link_options(survivor PRIVATE
        -fsanitize=address,undefined
    )
endif()

target_include_directories(survivor PRIVATE include include/enemies include/player include/State)

find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)
target_link_libraries(survivor PRIVATE SFML::Graphics SFML::Window SFML::System)