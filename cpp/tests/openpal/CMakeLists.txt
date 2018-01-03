cmake_minimum_required (VERSION 3.8)

enable_testing()

set(openpal_tests_headers ../catch/catch.hpp)

set(openpal_tests_src
    ./src/CatchTestStart.cpp
    ./src/TestBigEndianSerialization.cpp
	./src/TestBuffer.cpp
    ./src/TestFloatSerialization.cpp
	./src/TestHexConversions.cpp
    ./src/TestLittleEndianSerialization.cpp
	./src/TestMockExecutor.cpp
    ./src/TestStaticBuffer.cpp    
)

add_executable(openpal_tests ${openpal_tests_headers} ${openpal_tests_src})
target_compile_features(openpal_tests PRIVATE cxx_std_14)
target_link_libraries(openpal_tests PRIVATE openpal)
target_include_directories(openpal_tests
    PRIVATE ./ ../catch
)

add_test(openpal_tests openpal_tests)
