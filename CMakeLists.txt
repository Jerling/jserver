cmake_minimum_required(VERSION 3.7)
set(PROJECT_NAME "jserver")
project(${PROJECT_NAME})
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_SOURCE_DIR}/include/jbase/config.h"
  )

option(USE_GLOG "Use google log" ON)

if(USE_GLOG)
  set(EXTRA_LIBS ${EXTRA_LIBS} glog)
  message("-- Use glog ...")
endif(USE_GLOG)

set(INC_LISTS
  ${INC_LISTS}
  include
  third_part/glog/src
  third_part/benchmark/include
  third_part/benchmark/googletest/googletest/include
  )
include_directories(${INC_LISTS})

add_subdirectory(tests)
