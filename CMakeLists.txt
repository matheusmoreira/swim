cmake_minimum_required(VERSION 2.8)

project(swim C)
set(BUILD_SHARED_LIBS ON)

set(SWIM_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(SWIM_SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set(SWIM_PLATFORM_DIR ${PROJECT_SOURCE_DIR}/platform)

include_directories(${SWIM_INCLUDE_DIR})

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(SWIM_PLATFORM linux.x11)
else()
  message("Warning - platform not supported")
endif()

set(SWIM_PLATFORM_LIBRARY "swim.${SWIM_PLATFORM}")
set(SWIM_PLATFORM_INCLUDE_DIR ${SWIM_PLATFORM_DIR}/${SWIM_PLATFORM}/include)
set(SWIM_PLATFORM_SRC_DIR ${SWIM_PLATFORM_DIR}/${SWIM_PLATFORM}/src)

message("Swim platform: ${SWIM_PLATFORM}")

# This should set SWIM_PLATFORM_LIBRARY_DEPENDENCIES
include(${SWIM_PLATFORM_DIR}/${SWIM_PLATFORM}.cmake)

file(GLOB_RECURSE SWIM_SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/*.c)
file(GLOB_RECURSE SWIM_PLATFORM_SOURCE_FILES ${SWIM_PLATFORM_SRC_DIR}/*.c)

add_library(${SWIM_PLATFORM_LIBRARY} ${SWIM_PLATFORM_SOURCE_FILES})
add_dependencies(${SWIM_PLATFORM_LIBRARY} ${SWIM_PLATFORM_LIBRARY_DEPENDENCIES})
target_link_libraries(${SWIM_PLATFORM_LIBRARY} ${SWIM_PLATFORM_LIBRARY_DEPENDENCIES})

add_library(swim ${SWIM_SOURCE_FILES})
set_target_properties(swim PROPERTIES LINKER_LANGUAGE C)
add_dependencies(swim ${SWIM_PLATFORM_LIBRARY})
target_link_libraries(swim ${SWIM_PLATFORM_LIBRARY})

add_subdirectory(examples)
