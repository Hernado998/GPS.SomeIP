cmake_minimum_required(VERSION 3.19)
set(LIB_NMEA_DIR ${CMAKE_CURRENT_LIST_DIR}/NemaTode)
set(LIB_NMEA NemaTode)
include(${LIB_NMEA_DIR}/CMakeLists.txt)

if (TEST_BUILD)
    
    include(${CMAKE_CURRENT_LIST_DIR}/test/CMakeLists.txt)
    
else()

set (VSOMEIP_NAME vsomeip3)
set (VSOMEIP_COMPAT_NAME vsomeip)

set (VSOMEIP_MAJOR_VERSION 3)
set (VSOMEIP_MINOR_VERSION 1)
include_directories(
        ${Boost_INCLUDE_DIR}
    	${VSOMEIP_INCLUDE_DIRS}
)
include_directories(${VSOMEIP_INCLUDE_DIRS})

find_package(PkgConfig) #finding pkg-config is a helper tool
find_package( Boost 1.71 COMPONENTS system thread log REQUIRED )
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")   
add_executable(service-gps
    ${CMAKE_CURRENT_LIST_DIR}/src/gpsdconnector.h
    ${CMAKE_CURRENT_LIST_DIR}/src/gpsdconnector.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/gpsservice.h
    ${CMAKE_CURRENT_LIST_DIR}/src/gpsservice.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/gpssocketreader.h
    ${CMAKE_CURRENT_LIST_DIR}/src/gpssocketreader.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/gpsstorage.h
    ${CMAKE_CURRENT_LIST_DIR}/src/gpsstorage.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/igpssocketreaderlistener.h
    ${CMAKE_CURRENT_LIST_DIR}/src/igpsstoragelistener.h
    ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
)
add_executable(client-gps
    ${CMAKE_CURRENT_LIST_DIR}/src1/gpssomeipclient.h
    ${CMAKE_CURRENT_LIST_DIR}/src1/gpssomeipclient.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src1/gpscontroller.h
    ${CMAKE_CURRENT_LIST_DIR}/src1/gpscontroller.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src1/igpssomeipclientlistener.h
    ${CMAKE_CURRENT_LIST_DIR}/src1/main.cpp
)
target_include_directories(service-gps PRIVATE ${LIB_NMEA_DIR}/include)
target_link_libraries(service-gps vsomeip3 ${VSOMEIP_NAME} ${Boost_LIBRARIES} ${DL_LIBRARY} gps ${LIB_NMEA})
target_link_libraries(client-gps vsomeip3 ${VSOMEIP_NAME} ${Boost_LIBRARIES} ${DL_LIBRARY} gps ${LIB_NMEA})

endif()
