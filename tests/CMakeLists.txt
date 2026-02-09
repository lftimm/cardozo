cmake_minimum_required(VERSION 3.31)
project(tests)

# GoogleTest requires at least C++17
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/releases/download/v1.17.0/googletest-1.17.0.tar.gz
)

FetchContent_MakeAvailable(googletest)

add_executable(
    ${PROJECT_NAME}
    vector_test.cpp
    matrix_test.cpp
    algos_test.cpp
)

target_link_libraries(
    ${PROJECT_NAME}
    GTest::gtest_main
    cardozo
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
