#
# This file is part of C11_TEMPLATE.
#

###############################
# Project / compiler settings #
###############################
cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(C11_TEMPLATE C)

enable_testing()

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/packages")

# Setup general compiler warnings
if(CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic")
elseif()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /Wall")
endif()

# Available build options
option(BUILD_TESTS "Build all of the unit tests" ON)
option(ENABLE_SDL2 "Look for OpenGL and SDL2" ON)

####################
# Project packages #
####################
if(ENABLE_SDL2)
    set(OpenGL_GL_PREFERENCE "GLVND")
    find_package(OpenGL)
    find_package(SDL2)
endif()

###########################
# Project sub-directories #
###########################
add_subdirectory(src)

if(BUILD_TESTS)
    message(STATUS "Building the unit tests")
    add_subdirectory(tests)
endif()
