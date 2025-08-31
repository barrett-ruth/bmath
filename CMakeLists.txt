cmake_minimum_required(VERSION 3.20)
project(
  bmath
  VERSION 0.1.0
  DESCRIPTION "Header-only C++23 math library"
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(bmath INTERFACE)
add_library(bmath::bmath ALIAS bmath)

target_include_directories(
  bmath INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                  $<INSTALL_INTERFACE:include>)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL
                                           "Clang")
  target_compile_options(
    bmath
    INTERFACE -pedantic-errors
              -Wall
              -Wextra
              -Wpedantic
              -Wshadow
              -Wformat=2
              -Wfloat-equal
              -Wlogical-op
              -Wshift-overflow=2
              -Wnon-virtual-dtor
              -Wold-style-cast
              -Wcast-qual
              -Wuseless-cast
              -Wcast-align
              -Wunused
              -Woverloaded-virtual
              -Wconversion
              -Wmisleading-indentation
              -Wduplicated-cond
              -Wduplicated-branches
              -Wnull-dereference
              -Wno-conversion
              -Wformat-overflow
              -Wformat-truncation
              -Wdouble-promotion
              -Wundef)
endif()

target_compile_definitions(bmath INTERFACE LOCAL)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_compile_options(
    bmath
    INTERFACE -O0
              -g3
              -fsanitize=address,undefined
              -fsanitize=float-divide-by-zero
              -fsanitize=float-cast-overflow
              -fno-sanitize-recover=all
              -fstack-protector-all
              -fno-omit-frame-pointer
              -fno-inline
              -ffunction-sections)

  target_compile_definitions(bmath INTERFACE _GLIBCXX_DEBUG
                                             _GLIBCXX_DEBUG_PEDANTIC)

  target_link_options(
    bmath INTERFACE -fsanitize=address,undefined
    -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow)
else()
  target_compile_options(bmath INTERFACE -O2)
  target_compile_definitions(bmath INTERFACE NDEBUG)
endif()

enable_testing()
add_subdirectory(tests)
