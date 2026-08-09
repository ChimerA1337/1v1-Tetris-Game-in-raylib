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
    target_link_libraries(tetorisu ${RAYLIB_LIBRARY})
else()
    find_package(raylib QUIET)
    if(raylib_FOUND)
        target_link_libraries(tetorisu raylib)
    else()
        target_link_libraries(tetorisu raylib)
    endif()
endif()

# ENet
if(ENET_INCLUDE_DIR AND ENET_LIBRARY)
    target_include_directories(tetorisu PRIVATE ${ENET_INCLUDE_DIR})
    target_link_libraries(tetorisu ${ENET_LIBRARY})
else()
    target_link_libraries(tetorisu enet)
endif()

if(UNIX AND NOT APPLE)
    target_link_libraries(tetorisu GL m pthread dl rt X11)
elseif(APPLE)
    target_link_libraries(tetorisu m pthread)
    target_link_libraries(tetorisu "-framework Cocoa" "-framework OpenGL")
elseif(WIN32)
    target_compile_definitions(tetorisu PRIVATE
        WIN32_LEAN_AND_MEAN
        NOGDI
    )

    target_compile_options(tetorisu PRIVATE /showIncludes)

    target_link_libraries(tetorisu m pthread)
endif()