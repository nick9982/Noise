cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(This hm)

set(CMAKE_CXX_FLAGS "-O3")

project(${This} CXX C)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    /usr/include
    include
)

link_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/lib
)
add_executable(${PROJECT_NAME} heightmap.cpp  main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE lodepng)
