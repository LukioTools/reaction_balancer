cmake_minimum_required(VERSION 2.8)

project(main)
find_package(glm REQUIRED)

add_executable(main main.cpp)

target_link_libraries(main glm::glm)

project(test)
find_package(glm REQUIRED)

add_executable(test test.cpp)

target_link_libraries(test glm::glm)