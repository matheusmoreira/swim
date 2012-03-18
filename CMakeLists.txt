cmake_minimum_required(VERSION 2.8)

project(swim C)

set(BUILD_SHARED_LIBS ON)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  add_definitions(-DSWIM_PLATFORM_LINUX)
  find_library(X11_LIBRARY X11)
  if(X11_LIBRARY)
    add_definitions(-DSWIM_PLATFORM_LINUX_X11)
  endif()
else()
  message("Warning - platform not supported")
endif()

include_directories("${PROJECT_SOURCE_DIR}/include")
file(GLOB_RECURSE SWIM_SOURCE_FILES "${PROJECT_SOURCE_DIR}/src/*.c")
message("Swim source files: ${SWIM_SOURCE_FILES}")

add_library(swim ${SWIM_SOURCE_FILES})
set_target_properties(swim PROPERTIES LINKER_LANGUAGE C)

add_subdirectory(examples)
