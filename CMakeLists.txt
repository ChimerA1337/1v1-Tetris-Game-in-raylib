# Rewrite this piece of shit when you learn how CMakeLists works

cmake_minimum_required(VERSION 3.10)
project(tetorisu C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

file(GLOB SOURCES "source/*.c")
list(APPEND SOURCES "main.c")

add_executable(tetorisu ${SOURCES})
target_include_directories(tetorisu PRIVATE include)

# Raylib
if(RAYLIB_INCLUDE_DIR AND RAYLIB_LIBRARY)
    target_include_directories(tetorisu PRIVATE ${RAYLIB_INCLUDE_DIR})
    target_link_libraries(tetorisu PRIVATE ${RAYLIB_LIBRARY})
else()
    find_package(raylib QUIET)
    if(raylib_FOUND)
        target_link_libraries(tetorisu PRIVATE raylib)
    else()
        target_link_libraries(tetorisu PRIVATE raylib)
    endif()
endif()

# ENet
if(ENET_INCLUDE_DIR AND ENET_LIBRARY)
    target_include_directories(tetorisu PRIVATE ${ENET_INCLUDE_DIR})
    target_link_libraries(tetorisu PRIVATE ${ENET_LIBRARY})
else()
    find_package(enet QUIET)
    if(enet_FOUND)
        target_link_libraries(tetorisu PRIVATE enet)
    else()
        target_link_libraries(tetorisu PRIVATE enet)
    endif()
endif()

if(UNIX AND NOT APPLE)
    target_link_libraries(tetorisu PRIVATE m pthread dl rt X11)
elseif(APPLE)
    target_link_libraries(tetorisu PRIVATE m pthread)
    target_link_libraries(tetorisu PRIVATE "-framework Cocoa" "-framework OpenGL")
elseif(WIN32)
    # Keep Windows headers from declaring symbols that collide with raylib
    target_compile_definitions(tetorisu PRIVATE
        WIN32_LEAN_AND_MEAN   # shrink windows.h
        NOGDI                 # prevent DrawText / Rectangle GDI conflicts
        NOUSER                # prevent CloseWindow / ShowCursor winuser conflicts
        NOMINMAX              # prevent min/max macro conflicts
        _WIN32_WINNT=0x0601   # suppress "please define _WIN32_WINNT" warning
    )

    # Remove /showIncludes when you're done debugging include order
    # target_compile_options(tetorisu PRIVATE /showIncludes)

    # Windows-specific libs: winmm (raylib audio/time), ws2_32 (ENet sockets)
    target_link_libraries(tetorisu PRIVATE winmm ws2_32)
endif()