cmake_minimum_required(VERSION 3.28)
project(AdvacedProgramingZit2)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

add_executable(AdvacedProgramingZit2 main.cpp
        BGTile.cpp
        Game.cpp
        World.cpp
        GameView.cpp
        Observers.cpp
        Singletons.cpp)

target_link_libraries(AdvacedProgramingZit2 sfml-system sfml-window sfml-graphics)