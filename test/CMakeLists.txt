cmake_minimum_required(VERSION 3.5)

find_package(GTest CONFIG REQUIRED)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
enable_testing()

set(SRCS
    ${CMAKE_CURRENT_LIST_DIR}/test_service.cpp
    ${CMAKE_CURRENT_LIST_DIR}/doubles.cpp
    
    ${CMAKE_CURRENT_SOURCE_DIR}/service/src/gpsdconnector.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/service/src/gpsstorage.cpp
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/service/src
    ${LIB_NMEA_DIR}/include
)

add_executable(test_service ${SRCS})
target_link_libraries(test_service PRIVATE gtest_main gtest pthread ${LIB_NMEA})

include(GoogleTest)
gtest_discover_tests(test_service)
