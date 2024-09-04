# -----------------------------------------------------------------------------------
# Project:     [EBEK]
# File:        [CMakeLists.txt]
# Author:      Prof.Dr. Onur Tuncer
# Email:       onur.tuncer@itu.edu.tr
# Institution: Istanbul Technical University
#              Faculty of Aeronautics and Astronuatics
# 
# Date:        2024
#
# Description:
# [Top level build file]
#
# License:
# [See License.txt in the top level directory for licence and copyright information]
# -----------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.20)
file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/version.txt" projectVersion)
project(fmu4cpp-template VERSION ${projectVersion})

option(FMU4CPP_BUILD_TESTS "Build tests" OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

list(APPEND FMU_TARGETS GravityJ2
                        AtmosphereUS1976)

# ---------------------------------------Looking for git and updating submodules-------------------
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")

# Git version
execute_process(COMMAND ${GIT_EXECUTABLE} rev-parse --short HEAD
                WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
                OUTPUT_VARIABLE PACKAGE_GIT_VERSION
                ERROR_QUIET
                OUTPUT_STRIP_TRAILING_WHITESPACE)
# Update submodules as needed
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(WARNING "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

#-----------------------------------------------------------------------------------------------------

# ***** Build libode library *****************************************************

file(GLOB libode_SRC  "vendor/libode/src/*.cc")

add_library(libode STATIC ${libode_SRC})

set_target_properties(libode PROPERTIES     CXX_STANDARD 17
                                            CXX_STANDARD_REQUIRED ON
                                            CXX_EXTENSIONS OFF)
target_include_directories(libode PUBLIC "vendor/libode/src"
                                          "vendor/libode/include/ode")
# ********************************************************************************

if (MSVC)
    # link statically against the the Visual C runtime
    string(REPLACE "/MD" "/MT" CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}")
    string(REPLACE "/MDd" "/MTd" CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG}")
endif ()

if ("${CMAKE_SIZEOF_VOID_P}" STREQUAL "8")
    set(BITNESS 64)
else ()
    set(BITNESS 32)
endif ()

if (WIN32)
    set(TARGET_PLATFORM win${BITNESS})
elseif (APPLE)
    set(TARGET_PLATFORM darwin${BITNESS})
else ()
    set(TARGET_PLATFORM linux${BITNESS})
endif ()

add_subdirectory(export)
add_subdirectory(src)

if (FMU4CPP_BUILD_TESTS)
    Include(FetchContent)

    FetchContent_Declare(
            Catch2
            GIT_REPOSITORY https://github.com/catchorg/Catch2.git
            GIT_TAG v2.13.8
    )
    FetchContent_MakeAvailable(Catch2)

    enable_testing()
    add_subdirectory(export/tests)
endif ()