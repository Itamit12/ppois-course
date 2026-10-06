cmake_minimum_required(VERSION 3.15)
project(lab1 CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# === Библиотека с логикой ===
add_library(lab1_lib
    src/Vector3D.cpp
    src/PostMachine.cpp
)
target_include_directories(lab1_lib PUBLIC include)

# === CLI ===
add_executable(lab1_cli src/main.cpp)
target_link_libraries(lab1_cli PRIVATE lab1_lib)

# === Тесты ===
enable_testing()
find_package(GTest CONFIG REQUIRED)
add_executable(lab1_tests
    tests/test_vector.cpp
    tests/test_postmachine.cpp
)
target_link_libraries(lab1_tests PRIVATE lab1_lib GTest::gtest GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(lab1_tests)