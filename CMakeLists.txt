cmake_minimum_required(VERSION 3.31)

project(cardozo)

add_library(
    ${PROJECT_NAME}
    src/dense_cr.cpp
    src/sparse_cr.cpp
    src/vector.cpp
)

execute_process(COMMAND python combine.py
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})

target_include_directories(${PROJECT_NAME} PRIVATE headers src)

if(WIN32) 
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Werror -Wextra)
endif()
