# Mirco Pascal Scanner

cmake_minimum_required(VERSION 3.0)
 

FILE(GLOB MP_SCANNER_HEADERS *.h)

FILE(GLOB MP_SCANNER_SOURCES *.cpp)


add_library( mpscanner STATIC ${MP_SCANNER_SOURCES} ${MP_SCANNER_HEADERS} ) 

install( TARGETS mpscanner DESTINATION lib)
install( FILES MP_SCANNER_HEADERS DESTINATION include)


include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(TestScanner)

source_group(Headers FILES ${MP_SCANNER_HEADERS})
source_group(Sources FILES ${MP_SCANNER_SOURCES})