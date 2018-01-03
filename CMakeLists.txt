cmake_minimum_required (VERSION 3.8)

project(openpal VERSION 1.0.0)

add_subdirectory(./cpp/libs/openpal)
add_subdirectory(./cpp/tests)

add_custom_target(
	format
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
	COMMAND astyle -R ./cpp/*.h ./cpp/*.cpp --options=./astyle.cfg
)