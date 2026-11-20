cmake_minimum_required(VERSION 3.15)
project(lab1 CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# MSVC: отключаем warning C4834 (nodiscard) — мешает в тестах с EXPECT_THROW
if (MSVC)
    add_compile_options(/wd4834)
endif()

# === Покрытие ===
# GCC/Clang: инструментирование на этапе компиляции (флаг ENABLE_COVERAGE).
# MSVC: инструментирование не нужно — отчёт снимает OpenCppCoverage с PDB.
option(ENABLE_COVERAGE "Enable coverage flags (GCC/Clang)" OFF)
set(COVERAGE_THRESHOLD 0 CACHE STRING "Minimum line coverage (%), 0 = no check")

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
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
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

# === Цель coverage: прогон тестов + таблица покрытия в консоли ===
if (MSVC)
    find_program(OPENCPPCOVERAGE_EXECUTABLE
        NAMES OpenCppCoverage
        HINTS "$ENV{ProgramFiles}/OpenCppCoverage" "C:/Program Files/OpenCppCoverage"
    )

    if (OPENCPPCOVERAGE_EXECUTABLE)
        set(COVERAGE_XML  "${CMAKE_BINARY_DIR}/coverage.xml")
        set(COVERAGE_HTML "${CMAKE_BINARY_DIR}/coverage_html")

        # OpenCppCoverage принимает только пути с обратными слэшами.
        file(TO_NATIVE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src" COVERAGE_SOURCES_NATIVE)
        file(TO_NATIVE_PATH "${COVERAGE_XML}"  COVERAGE_XML_NATIVE)
        file(TO_NATIVE_PATH "${COVERAGE_HTML}" COVERAGE_HTML_NATIVE)

        add_custom_target(coverage
            COMMAND ${OPENCPPCOVERAGE_EXECUTABLE}
                --quiet
                --sources ${COVERAGE_SOURCES_NATIVE}
                --export_type=cobertura:${COVERAGE_XML_NATIVE}
                --export_type=html:${COVERAGE_HTML_NATIVE}
                -- $<TARGET_FILE:lab1_tests>
            COMMAND ${CMAKE_COMMAND}
                -DCOBERTURA_XML=${COVERAGE_XML}
                -DCOVERAGE_HTML=${COVERAGE_HTML}
                -DCOVERAGE_THRESHOLD=${COVERAGE_THRESHOLD}
                -P ${CMAKE_CURRENT_SOURCE_DIR}/cmake/PrintCoverage.cmake
            DEPENDS lab1_tests
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMENT "Running tests under OpenCppCoverage"
            VERBATIM
        )
    else ()
        message(STATUS "OpenCppCoverage not found: 'coverage' target disabled")
    endif ()

elseif (ENABLE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    find_program(LCOV_EXECUTABLE lcov)
    find_program(GENHTML_EXECUTABLE genhtml)

    if (LCOV_EXECUTABLE)
        set(_coverage_html_cmd "")
        if (GENHTML_EXECUTABLE)
            set(_coverage_html_cmd
                COMMAND ${GENHTML_EXECUTABLE} coverage.info
                    --output-directory ${CMAKE_BINARY_DIR}/coverage_html
                    --title "lab1 coverage")
        endif ()

        add_custom_target(coverage
            COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
            COMMAND ${LCOV_EXECUTABLE} --capture
                --directory ${CMAKE_BINARY_DIR}
                --output-file coverage.info
                --ignore-errors mismatch,empty,gcov,source
            COMMAND ${LCOV_EXECUTABLE} --remove coverage.info
                '/usr/*' '*/tests/*' '*/_deps/*' '*/main.cpp'
                --output-file coverage.info
                --ignore-errors unused,source
            COMMAND ${LCOV_EXECUTABLE} --list coverage.info
                --fail-under-lines ${COVERAGE_THRESHOLD}
            ${_coverage_html_cmd}
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMENT "Running tests and collecting coverage with lcov"
            VERBATIM
        )
    else ()
        message(STATUS "lcov not found: 'coverage' target disabled")
    endif ()
endif ()