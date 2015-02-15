# Mirco Pascal Scanner Tests

cmake_minimum_required(VERSION 3.0)



FILE(GLOB MP_SCANNER_TEST_HEADERS *.h)

FILE(GLOB MP_SCANNER_TEST_SOURCES *.cpp)

FILE(GLOB MP_SCANNER_HEADERS ../*.h)

FILE(GLOB MP_SCANNER_SOURCES ../*.cpp)


add_executable( testmp ${MP_SCANNER_TEST_SOURCES} ${MP_SCANNER_TEST_HEADERS} ${MP_SCANNER_SOURCES} ${MP_SCANNER_HEADERS} ) 

install(TARGETS testmp DESTINATION bin)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}) #source path
include_directories(${CMAKE_CURRENT_BINARY_DIR}) #build path

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../) #source path
include_directories(${CMAKE_CURRENT_BINARY_DIR}/../) #build path

source_group(Headers FILES ${MP_SCANNER_TEST_HEADERS})
source_group(Sources FILES ${MP_SCANNER_TEST_SOURCES})