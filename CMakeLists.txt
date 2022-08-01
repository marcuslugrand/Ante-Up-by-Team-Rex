cmake_minimum_required(VERSION 3.21)
project(AnteUp)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#SFML Library
set(SFML_DIR "SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit/SFML-2.5.1/lib/cmake/SFML")

find_package(SFML 2.5.1 COMPONENTS graphics audio REQUIRED)

add_executable(AnteUp
        src/hand.cpp
        src/hand.h
        src/main.cpp
        src/Record.h
        src/unordered_hand_map.cpp
        src/unordered_hand_map.h
        src/hand_map.h
        src/hand_map.cpp)
target_link_libraries(AnteUp sfml-graphics sfml-audio)
