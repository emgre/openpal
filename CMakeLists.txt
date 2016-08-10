cmake_minimum_required (VERSION 2.8)
project (opendnp3)
set(OPENPAL_MAJOR_VERSION 1)
set(OPENPAL_MINOR_VERSION 0)
set(OPENPAL_MICRO_VERSION 0)
set(OPENPAL_VERSION ${OPENPAL_MAJOR_VERSION}.${OPENPAL_MINOR_VERSION}.${OPENPAL_MICRO_VERSION})

include(${PROJECT_SOURCE_DIR}/cmake/settings.cmake)

# various optional libraries and projects
option(WERROR "Set all warnings to errors" OFF)
option(STATICLIBS "Builds static versions of all installed libraries" OFF)

# include paths for all the local libraries
include_directories(./cpp/libs/src)
include_directories(./cpp/libs/include)
include_directories(./cpp/tests/libs/src)

# ---- openpal library ----
file(GLOB_RECURSE openpal_SRC ./cpp/libs/src/openpal/*.cpp ./cpp/libs/src/openpal/*.h ./cpp/libs/include/openpal/*.h)
add_library(openpal ${LIB_TYPE} ${openpal_SRC})
install(TARGETS openpal DESTINATION lib)
set_target_properties(openpal PROPERTIES FOLDER libs)

if(TEST)

  enable_testing()
  
  # ----- openpal tests -----
  file(GLOB_RECURSE openpal_TESTSRC ./cpp/tests/openpaltests/src/*.cpp ./cpp/tests/openpaltests/src/*.h)
  add_executable (testopenpal ${openpal_TESTSRC})
  target_link_libraries (testopenpal LINK_PUBLIC testlib ${PTHREAD})
  set_target_properties(testopenpal PROPERTIES FOLDER tests)
  add_test(testopenpal testopenpal)  

endif()
