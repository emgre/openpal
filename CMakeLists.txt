cmake_minimum_required (VERSION 3.8)

project(openpal VERSION 1.0.0)

set(is_root OFF)
if(${CMAKE_SOURCE_DIR} EQUAL ${CMAKE_CURRENT_SOURCE_DIR})
	set(is_root ON)
endif()
set(OPENPAL_BUILD_TESTS ${is_root} CACHE BOOL "Build unit tests")

add_subdirectory(./cpp/libs/openpal)
add_subdirectory(./cpp/libs/asiopal)

if(${OPENPAL_BUILD_TESTS})
    enable_testing()
    add_subdirectory(./cpp/tests/openpal)
    add_subdirectory(./cpp/tests/asiopal)
endif()

add_custom_target(
	format
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
	COMMAND astyle -R ./cpp/*.h ./cpp/*.cpp --options=./astyle.cfg
)