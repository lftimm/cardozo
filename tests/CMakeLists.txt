cmake_minimum_required(VERSION 3.31)
project(tests)

# GoogleTest requires at least C++17
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

add_executable(
    ${PROJECT_NAME}
    algos_test.cpp
    vector_test.cpp
)

target_link_libraries(
    ${PROJECT_NAME}
    GTest::gtest_main
    cardozo
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
