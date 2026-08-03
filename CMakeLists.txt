cmake_minimum_required(VERSION 3.10)
project(MyGame C)

set(CMAKE_C_STANDARD 11)

# Grab all .c files in source/
file(GLOB SOURCES "source/*.c")

add_executable(main ${SOURCES}
        include/definitions.h
        include/input.h
        source/input.c
        source/randomizer.c
        include/randomizer.h
        include/gameState.h
        include/settings.h
        source/gameState.c
        source/tetrisLogic.c
        include/tetrisLogic.h
        source/rotation.c
        include/rotation.h
)

target_include_directories(main PRIVATE include)

find_library(RAYLIB_LIB raylib)
target_link_libraries(main ${RAYLIB_LIB} GL m pthread dl rt X11)