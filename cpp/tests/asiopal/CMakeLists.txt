cmake_minimum_required (VERSION 3.8)

enable_testing()

set(asiopal_tests_headers ../catch/catch.hpp)

set(asiopal_tests_src
    ./src/CatchTestStart.cpp
    ./src/TestBasicExecutor.cpp
    ./src/TestStrandExecutor.cpp  
)

add_executable(asiopal_tests ${asiopal_tests_headers} ${asiopal_tests_src})
target_compile_features(asiopal_tests PRIVATE cxx_std_14)
target_link_libraries(asiopal_tests PRIVATE asiopal)
target_include_directories(asiopal_tests
    PRIVATE ./ ../catch
)

add_test(asiopal_tests asiopal_tests)
