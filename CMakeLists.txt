cmake_minimum_required(VERSION 3.10)
project(LibrarySystem)

set(CMAKE_CXX_STANDARD 11)

add_executable(library_app main.cpp)
target_compile_definitions(library_app PRIVATE BUILD_EXECUTABLE)

find_package(GTest REQUIRED)
add_executable(runTests test.cpp)
target_link_libraries(runTests GTest::GTest GTest::Main pthread)

target_compile_definitions(runTests PRIVATE BUILD_TESTS)

enable_testing()
add_test(NAME library_tests COMMAND runTests)
