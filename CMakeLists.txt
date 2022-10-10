cmake_minimum_required(VERSION 3.21)
project(daily_practice)

set(CMAKE_CXX_STANDARD 20)
#set(BOOST_ROOT "/opt/homebrew/Cellar/boost/1.76.0")
#include_directories(/opt/homebrew/Cellar/boost/1.76.0/include)
#link_directories(/opt/homebrew/Cellar/boost/1.76.0/lib)
#find_package(Boost 1.76.0 COMPONENTS system thread serialization)
#find_package(Boost 1.76.0 COMPONENTS ALL)
#[[
if (Boost_FOUND)
    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    MESSAGE(STATUS "boost library found")
    message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION: ${Boost_VERSION}")
    include_directories(${Boost_INCLUDE_DIRS})
else(Boost_FOUND)
    MESSAGE(FATAL_ERROR  "boost library not found")
endif (Boost_FOUND)
]]#
include_directories(utils)
add_executable(main main.cpp)
#target_link_libraries(untitled boost_thread-mt boost_system)

#target_link_libraries(untitled ${Boost_LIBRARIES})

message(STATUS ${CMAKE_VERSION})