set(CMAKE_CXX_STANDARD 17)

project(main)
include_directories(test_framework/)
add_executable(log w1/logger.cpp)
add_executable(ticket w1/sort_by.cpp)
add_executable(update_field w1/update_field.cpp)