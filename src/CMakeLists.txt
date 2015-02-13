cmake_minimum_required(VERSION 3.0)

project(app_project)

add_subdirectory(scanner)

add_subdirectory(parser)

add_executable( mp MainDriver.cpp)

target_link_libraries(mp mpparser)

install(TARGETS mp DESTINATION bin)

#try this
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/scanner/) 
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/parser/) 