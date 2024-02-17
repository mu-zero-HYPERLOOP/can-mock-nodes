######################################################################
# @author      : karl (karlsasssie@gmail.com)
# @file        : CMakeLists
# @created     : Friday Apr 07, 2023 15:39:05 CEST
######################################################################

cmake_minimum_required(VERSION 3.5)
project(mock-pdu12 C)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
SET(CMAKE_C_FLAGS  "-lm")


set(SOURCE_FILES 
  ${CMAKE_CURRENT_SOURCE_DIR}/main.c
  ${CMAKE_CURRENT_SOURCE_DIR}/can.c
  ${CMAKE_CURRENT_SOURCE_DIR}/time_util.c
  ${CMAKE_CURRENT_SOURCE_DIR}/mutex.c
  ${CMAKE_CURRENT_SOURCE_DIR}/thread.c
)

include(FetchContent)

FetchContent_Declare(
  can-socketcan-platform
  GIT_REPOSITORY https://github.com/mu-zero-HYPERLOOP/can-socketcan-platform
  GIT_TAG origin/main
)

FetchContent_Declare(
  can-cli-rs
  GIT_REPOSITORY https://github.com/mu-zero-HYPERLOOP/can-cli-rs
  GIT_TAG origin/main
)

FetchContent_MakeAvailable(can-socketcan-platform can-cli-rs)


set(NODE_NAME pdu12)

add_custom_command(
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/canzero
  COMMAND mkdir canzero
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

add_custom_target(
  canzero_codegen
  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/__header.h
)

add_custom_command(
  OUTPUT 
    ${CMAKE_CURRENT_BINARY_DIR}/__header.h
    ${CMAKE_CURRENT_BINARY_DIR}/canzero/canzero.h 
    ${CMAKE_CURRENT_BINARY_DIR}/canzero/canzero.c 
  COMMAND cargo run -- gen --node ${NODE_NAME} --output ${CMAKE_CURRENT_BINARY_DIR}/canzero
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/_deps/can-cli-rs-src/
  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/canzero
)

add_executable(${PROJECT_NAME}
  ${SOURCE_FILES}
  ${CMAKE_CURRENT_BINARY_DIR}/canzero/canzero.c
)
add_dependencies(${PROJECT_NAME} canzero_codegen)

target_include_directories(${PROJECT_NAME} 
  PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_BINARY_DIR}/canzero
)

target_link_libraries(${PROJECT_NAME}
  PRIVATE can-socketcan-platform
)

