set(CMAKE_CXX_STANDARD 17)

project(main)
include_directories(test_framework/)
add_executable(log w1/logger.cpp)