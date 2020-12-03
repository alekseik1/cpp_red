cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 17)

project(w1)
include_directories(test_framework/)
#add_executable(log w1/logger.cpp)
add_executable(ticket w1/sort_by.cpp)
add_executable(update_field w1/update_field.cpp)
add_executable(bad_macros w1/bad_macros.cpp)
add_executable(deque w1/deque.cpp)
add_executable(paginator w1/paginator.cpp)

project(w2)
add_executable(sort_students w2/sort_students.cpp)