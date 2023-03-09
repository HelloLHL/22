cmake_minimum_required(VERSION 3.21)
project(daily_practice)

set(CMAKE_CXX_STANDARD 20)

#[[]]#

add_executable(main myServer.cpp)
#target_link_libraries(untitled boost_thread-mt boost_system)

message(STATUS ${CMAKE_VERSION})