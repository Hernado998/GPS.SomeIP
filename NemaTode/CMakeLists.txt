cmake_minimum_required(VERSION 3.19)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RELEASE_POSTFIX "" CACHE STRING "Add postfix to target for Release build.")
set(CMAKE_DEBUG_POSTFIX "d" CACHE STRING "Add postfix to target for Debug build.")
set(CMAKE_RELWITHDEBINFO_POSTFIX "rd" CACHE STRING "Add postfix to target for RelWithDebInfo build.")
set(CMAKE_MINSIZEREL_POSTFIX "s" CACHE STRING "Add postfix to target for MinSizeRel build")

set(headers
	${CMAKE_CURRENT_LIST_DIR}/include/nmeaparse/Event.h
	${CMAKE_CURRENT_LIST_DIR}/include/nmeaparse/GPSFix.h
	${CMAKE_CURRENT_LIST_DIR}/include/nmeaparse/GPSService.h
	${CMAKE_CURRENT_LIST_DIR}/include/nmeaparse/nmea.h
	${CMAKE_CURRENT_LIST_DIR}/include/nmeaparse/NMEACommand.h
	${CMAKE_CURRENT_LIST_DIR}/include/nmeaparse/NMEAParser.h
	${CMAKE_CURRENT_LIST_DIR}/include/nmeaparse/NumberConversion.h
)

set(sources
	${CMAKE_CURRENT_LIST_DIR}/src/GPSFix.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/GPSService.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/NMEACommand.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/NMEAParser.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/NumberConversion.cpp
)

add_library(NemaTode STATIC ${headers} ${sources})

target_include_directories(NemaTode PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
	$<INSTALL_INTERFACE:include>
)

#include(GNUInstallDirs)
#set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake)

#install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# We have no other dependencies, so we export direct to NemaTodeConfig
# instead of using write_basic_package_version_file to generate a helper file
#install(TARGETS NemaTode
#	EXPORT NemaTodeConfig
#	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
#	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
#	PUBLIC_HEADER DESTINATION include
#)

#install(EXPORT NemaTodeConfig
#	DESTINATION ${INSTALL_CONFIGDIR}
#	NAMESPACE NemaTode::
#)

#include(CMakePackageConfigHelpers)
#write_basic_package_version_file(
#	${CMAKE_CURRENT_BINARY_DIR}/NemaTodeVersion.cmake
#	COMPATIBILITY SameMajorVersion
#)
#install(
#	FILES ${CMAKE_CURRENT_BINARY_DIR}/NemaTodeVersion.cmake
#	DESTINATION ${INSTALL_CONFIGDIR}
#)

# build demo_advanced
#add_executable(demo_advanced demo_advanced.cpp)
#target_link_libraries(demo_advanced NemaTode)

# build demo_simple
#add_executable(demo_simple demo_simple.cpp)
#target_link_libraries(demo_simple NemaTode)
