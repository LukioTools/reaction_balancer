cmake_minimum_required(VERSION 2.8)

project(main)



set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")


find_package(glm REQUIRED)

add_executable(main main.cpp)

target_link_libraries(main glm::glm)