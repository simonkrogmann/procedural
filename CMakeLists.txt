cmake_minimum_required (VERSION 3.0)
project(glphotomagic)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(glm REQUIRED)
find_package(glbinding REQUIRED)

# GLFW
find_package(PkgConfig)
if(PkgConfig_FOUND)
    pkg_search_module(GLFW REQUIRED glfw3)
else()
    find_package(GLFW REQUIRED)
endif()

include_directories(${GLFW_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS} ${GLBINDING_INCLUDE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++14")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory(source)
