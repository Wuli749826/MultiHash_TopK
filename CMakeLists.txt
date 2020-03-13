CMAKE_MINIMUM_REQUIRED(VERSION 3.10) 
PROJECT(TopK)    

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")
SET(CMAKE_C_COMPILER "/usr/bin/gcc") 
SET(CMAKE_CXX_COMPILER "/usr/bin/g++") 


INCLUDE_DIRECTORIES(
   "${PROJECT_SOURCE_DIR}"
   "${PROJECT_SOURCE_DIR}/include" 
   "${PROJECT_SOURCE_DIR}/src")

AUX_SOURCE_DIRECTORY("${PROJECT_SOURCE_DIR}/src" main)
AUX_SOURCE_DIRECTORY("${PROJECT_SOURCE_DIR}/test" tests)

link_libraries(
   "${PROJECT_SOURCE_DIR}/lib/libgtest.a"
   "${PROJECT_SOURCE_DIR}/lib/libgtest_main.a"
   pthread)

add_executable(TopK
    ${main}
)

add_executable(unit_tests
    ${tests}
)