cmake_minimum_required(VERSION 3.24)
project(astrotest)

add_subdirectory(gtest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(ASTROLIB_SRC_PATH ../src)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} ASTROTEST_SRC)

# sources for test
aux_source_directory(${ASTROLIB_SRC_PATH} ASTROLIB_SRC)

add_executable(${PROJECT_NAME} ${ASTROTEST_SRC} ${ASTROLIB_SRC})
target_link_libraries(${PROJECT_NAME} gtest gtest_main)

# declarations for test
target_include_directories(${PROJECT_NAME} PRIVATE ${ASTROLIB_SRC_PATH})
target_include_directories(${PROJECT_NAME} PRIVATE ${ASTROLIB_SRC_PATH}/include)