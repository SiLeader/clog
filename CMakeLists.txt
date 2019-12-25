cmake_minimum_required(VERSION 3.5)
project(clog)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

add_executable(clog test.cpp include/clog/logger.hpp include/clog/base.hpp include/clog/loggers/stdout.hpp)