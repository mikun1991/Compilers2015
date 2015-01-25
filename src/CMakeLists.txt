cmake_minimum_required(VERSION 3.0)

project(app_project)

add_subdirectory(scanner)


add_executable( mp MainDriver.cpp)

target_link_libraries(mp mpscanner)

install(TARGETS mp DESTINATION bin)
