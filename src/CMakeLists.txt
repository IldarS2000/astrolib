cmake_minimum_required(VERSION 3.24)
project(astrolib)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} ASTROLIB_SRC)
add_library(${PROJECT_NAME} STATIC ${ASTROLIB_SRC})
target_include_directories(${PROJECT_NAME} PUBLIC .)
target_include_directories(${PROJECT_NAME} PUBLIC include)