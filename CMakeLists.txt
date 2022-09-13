cmake_minimum_required(VERSION 3.15)
project(simple_atm_controller CXX)

set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_BUILD_TYPE Release CACHE)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING
            "Default build type: RelWithDebInfo" FORCE)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
# set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        main
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

if(NOT EXISTS ${CMAKE_FIND_PACKAGE_REDIRECTS_DIR}/gtest-config.cmake
   AND NOT EXISTS ${CMAKE_FIND_PACKAGE_REDIRECTS_DIR}/GTestConfig.cmake)
  file(
    WRITE ${CMAKE_FIND_PACKAGE_REDIRECTS_DIR}/gtest-config.cmake
    [=[
include(CMakeFindDependencyMacro)
find_dependency(googletest)
if(NOT TARGET GTest::GTest)
  add_library(GTest::GTest INTERFACE IMPORTED)
  target_link_libraries(GTest::GTest INTERFACE GTest::gtest)
endif()
if(NOT TARGET GTest::Main)
  add_library(GTest::Main INTERFACE IMPORTED)
  target_link_libraries(GTest::Main INTERFACE GTest::gtest_main)
endif()
]=])
endif()

if(NOT EXISTS ${CMAKE_FIND_PACKAGE_REDIRECTS_DIR}/gtest-config-version.cmake
   AND NOT EXISTS ${CMAKE_FIND_PACKAGE_REDIRECTS_DIR}/GTestConfigVersion.cmake)
  file(
    WRITE ${CMAKE_FIND_PACKAGE_REDIRECTS_DIR}/gtest-config-version.cmake
    [=[
include(${CMAKE_FIND_PACKAGE_REDIRECTS_DIR}/googletest-config-version.cmake OPTIONAL)
if(NOT PACKAGE_VERSION_COMPATIBLE)
  include(${CMAKE_FIND_PACKAGE_REDIRECTS_DIR}/googletestConfigVersion.cmake OPTIONAL)
endif()
]=])
endif()

include_directories(src)

# add_libary(${PROJECT_NAME}_lib SHARED simple_atm.hpp)

# find_package(googletest CONFIG REQUIRED HINTS ${CMAKE_CURRENT_SOURCE_DIR}/googletest)

add_library(lib${PROJECT_NAME} STATIC src/simple_atm.cpp)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

enable_testing()
# if (GTest_Found)
    message("GTest Available")
    set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
    set(BUILD_GTEST ON CACHE BOOL "" FORCE)
    include_directories(googletest/include)
    add_executable(unit_test ${CMAKE_CURRENT_SOURCE_DIR}/test/test.cpp )
    target_link_libraries(unit_test lib${PROJECT_NAME} GTest::gtest_main)
    include(GoogleTest)
    gtest_discover_tests(unit_test)
# endif()
