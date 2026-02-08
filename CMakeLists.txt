cmake_minimum_required(VERSION 3.31)

project(cardozo)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# This adds the cardozo.h file, teaches cmake how to get it and what it depends on
add_custom_command(
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/cardozo.h"
    COMMAND python "${CMAKE_CURRENT_LIST_DIR}/combine.py" && 
            mv "${CMAKE_CURRENT_LIST_DIR}/cardozo.h" "${CMAKE_CURRENT_BINARY_DIR}"
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
    DEPENDS combine.py
    COMMENT "Merging all headers into a single file"
)

# Basically this adds all dependencies to the project
add_library(
    ${PROJECT_NAME}
    src/dense_cr.cpp
    src/sparse_cr.cpp
    src/vector.cpp
    src/utils.cpp
    "${CMAKE_CURRENT_BINARY_DIR}/cardozo.h"
)

# Tests 
enable_testing()
add_subdirectory(tests)

# Where to find the folders
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_BINARY_DIR}" PRIVATE headers src)

# Compile flags
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Werror -Wextra)

# How to install
install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/cardozo.h" DESTINATION include)

