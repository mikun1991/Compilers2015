# Mirco Pascal Scanner

cmake_minimum_required(VERSION 3.0)
 

FILE(GLOB MP_SCANNER_HEADERS *.h)

FILE(GLOB MP_SCANNER_SOURCES *.cpp)


set( MP_SCANNER_FILES 
${MP_SCANNER_SOURCES} 
${MP_SCANNNER_HEADERS}
)


add_library( mpscanner STATIC ${MP_SCANNER_FILES}) 

install( TARGETS mpscanner DESTINATION lib)
install( FILES MP_SCANNER_HEADERS DESTINATION include)

include_directories(${CMAKE_SOURCE_DIR}) #source root
include_directories(${CMAKE_BINARY_DIR}) #build root
include_directories(${CMAKE_CURRENT_SOURCE_DIR}) #source path
include_directories(${CMAKE_CURRENT_BINARY_DIR}) #build path
include_directories("${PROJECT_BINARY_DIR}/src")
include_directories(${CORE_DIR})
include_directories(${PRECOMPILED_INCLUDE_DIR})

source_group("Headers" FILES ${MP_SCANNER_HEADERS})
source_group("Sources" FILES ${MP_SCANNER_SOURCES})