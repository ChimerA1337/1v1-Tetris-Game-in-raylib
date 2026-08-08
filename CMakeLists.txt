cmake_minimum_required(VERSION 3.10)
project(tetorisu C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

file(GLOB SOURCES "source/*.c")
list(APPEND SOURCES "main.c")

add_executable(tetorisu ${SOURCES})
target_include_directories(tetorisu PRIVATE include)

find_package(raylib REQUIRED)
target_link_libraries(tetorisu raylib)

# Use ENET_INCLUDE_DIR and ENET_LIBRARY from CMake cache
if(ENET_INCLUDE_DIR AND ENET_LIBRARY)
    target_include_directories(tetorisu PRIVATE ${ENET_INCLUDE_DIR})
    target_link_libraries(tetorisu ${ENET_LIBRARY})
else()
    # Fallback
    target_link_libraries(tetorisu enet)
endif()

if(UNIX AND NOT APPLE)
    target_link_libraries(tetorisu GL m pthread dl rt X11)
elseif(APPLE)
    target_link_libraries(tetorisu m pthread)
    target_link_libraries(tetorisu "-framework Cocoa" "-framework OpenGL")
elseif(WIN32)
    target_link_libraries(tetorisu m pthread)
endif()