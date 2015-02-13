# Micro Pascal Parser


cmake_minimum_required(VERSION 3.0)
 

FILE(GLOB MP_PARSER_HEADERS *.h)

FILE(GLOB MP_PARSER_SOURCES *.cpp)




add_library( mpparser STATIC ${MP_PARSER_HEADERS} ${MP_PARSER_SOURCES} )


install( TARGETS mpparser DESTINATION lib )

install( FILES MP_SCANNER_HEADERS DESTINATION include)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}) #source path
include_directories(${CMAKE_CURRENT_BINARY_DIR}) #build path

source_group(Headers FILES ${MP_PARSER_HEADERS})
source_group(Sources FILES ${MP_PARSER_SOURCES})