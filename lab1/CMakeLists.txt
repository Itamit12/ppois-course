cmake_minimum_required(VERSION 3.15)
project(lab1 CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# MSVC: отключаем warning C4834 (nodiscard) — мешает в тестах с EXPECT_THROW
if (MSVC)
    add_compile_options(/wd4834)
endif()

# === Флаги покрытия (только для GCC/Clang, Debug) ===
option(ENABLE_COVERAGE "Enable coverage flags" OFF)

if (ENABLE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-O0 -g --coverage -fprofile-arcs -ftest-coverage)
    add_link_options(--coverage)
endif()

# === Библиотека с логикой ===
add_library(lab1_lib
    src/Vector3D.cpp
    src/PostMachine.cpp
)
target_include_directories(lab1_lib PUBLIC include)

# === CLI ===
add_executable(lab1_cli src/main.cpp)
target_link_libraries(lab1_cli PRIVATE lab1_lib)

# === Тесты через FetchContent ===
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(lab1_tests
    tests/test_vector.cpp
    tests/test_postmachine.cpp
)
target_link_libraries(lab1_tests PRIVATE lab1_lib gtest gtest_main)

include(GoogleTest)
gtest_discover_tests(lab1_tests)