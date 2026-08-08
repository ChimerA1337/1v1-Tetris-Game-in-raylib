cmake_minimum_required(VERSION 3.10)
project(tetorisu C)

# C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Collect all source files
file(GLOB SOURCES "source/*.c")
list(APPEND SOURCES "main.c")

# Create executable
add_executable(tetorisu ${SOURCES})

# Include directories
target_include_directories(tetorisu PRIVATE include)

# Find and link raylib
find_package(raylib REQUIRED)
target_link_libraries(tetorisu raylib)

# Find and link ENet using pkg-config
find_package(PkgConfig QUIET)
if(PkgConfig_FOUND)
    pkg_check_modules(ENET QUIET enet)
    if(ENET_FOUND)
        target_include_directories(tetorisu PRIVATE ${ENET_INCLUDE_DIRS})
        target_link_libraries(tetorisu ${ENET_LIBRARIES})
    else()
        target_link_libraries(tetorisu enet)
    endif()
else()
    target_link_libraries(tetorisu enet)
endif()

# Platform-specific libraries
if(UNIX AND NOT APPLE)
    # Linux
    target_link_libraries(tetorisu GL m pthread dl rt X11)
elseif(APPLE)
    # macOS
    target_link_libraries(tetorisu m pthread)
    target_link_libraries(tetorisu "-framework Cocoa" "-framework OpenGL")
elseif(WIN32)
    # Windows
    target_link_libraries(tetorisu m pthread)
endif()