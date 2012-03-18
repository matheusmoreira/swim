cmake_minimum_required(VERSION 2.8)

project(swim C)
set(BUILD_SHARED_LIBS ON)

# Set up directories
set(SWIM_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(SWIM_SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set(SWIM_PLATFORM_DIR ${PROJECT_SOURCE_DIR}/platform)

# Make main library files accessible
include_directories(${SWIM_INCLUDE_DIR})
file(GLOB_RECURSE SWIM_SOURCE_FILES ${SWIM_SRC_DIR}/*.c)

# Detect underlying system
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(SWIM_PLATFORM linux.x11)
else()
  message("Warning - platform not supported")
endif()

message("Swim platform: ${SWIM_PLATFORM}")

# Configure shared library names
set(SWIM_LIBRARY ${PROJECT_NAME})
set(SWIM_PLATFORM_LIBRARY "${SWIM_LIBRARY}.${SWIM_PLATFORM}")

# Set up platform-specific directories
set(SWIM_PLATFORM_INCLUDE_DIR ${SWIM_PLATFORM_DIR}/${SWIM_PLATFORM}/include)
set(SWIM_PLATFORM_SRC_DIR ${SWIM_PLATFORM_DIR}/${SWIM_PLATFORM}/src)

# Run platform-specific build instructions,
# which should set SWIM_PLATFORM_LIBRARY_DEPENDENCIES
include(${SWIM_PLATFORM_DIR}/${SWIM_PLATFORM}/build.cmake)

# Make platform-specific files accessible
include_directories(${SWIM_PLATFORM_INCLUDE_DIR})
file(GLOB_RECURSE SWIM_PLATFORM_SOURCE_FILES ${SWIM_PLATFORM_SRC_DIR}/*.c)

# Configure platform-specific library target
add_library(${SWIM_PLATFORM_LIBRARY} ${SWIM_PLATFORM_SOURCE_FILES})
add_dependencies(${SWIM_PLATFORM_LIBRARY} ${SWIM_PLATFORM_LIBRARY_DEPENDENCIES})
target_link_libraries(${SWIM_PLATFORM_LIBRARY} ${SWIM_PLATFORM_LIBRARY_DEPENDENCIES})

# Configure main library target
add_library(${SWIM_LIBRARY} ${SWIM_SOURCE_FILES})
set_target_properties(${SWIM_LIBRARY} PROPERTIES LINKER_LANGUAGE C)
add_dependencies(${SWIM_LIBRARY} ${SWIM_PLATFORM_LIBRARY})
target_link_libraries(${SWIM_LIBRARY} ${SWIM_PLATFORM_LIBRARY})

# Build example code
add_subdirectory(examples)
