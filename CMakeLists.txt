cmake_minimum_required(VERSION 3.21)
project(Ante Up)

set(CMAKE_CXX_STANDARD 14)

#SFML Library
set(SFML_DIR "Ante-Up-by-Team-Rex/SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit/SFML-2.5.1/lib/cmake/SFML")

find_package(SFML 2.5.1 COMPONENTS graphics audio REQUIRED)

add_executable(Ante Up
        Ante-Up-by-Team-Rex/src/hand.cpp
        Ante-Up-by-Team-Rex/src/hand.h
        Ante-Up-by-Team-Rex/src/main.cpp
        Ante-Up-by-Team-Rex/src/Record.h
        Ante-Up-by-Team-Rex/src/unordered_hand_map.cpp
        Ante-Up-by-Team-Rex/src/unordered_hand_map.h
        Ante-Up-by-Team-Rex/src/hand_map.h
        Ante-Up-by-Team-Rex/src/hand_map.cpp)
target_link_libraries(Ante Up sfml-graphics sfml-audio)
