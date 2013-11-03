cmake_minimum_required(VERSION 2.8)

project(FortranToCHeaders CXX)
set(EXECUTABLE "FortranToCHeaders")

include_directories("${CMAKE_SOURCE_DIR}/include")

file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src" "*.cpp")

message(STATUS "sources = ${SOURCES}")

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.48.0 COMPONENTS program_options)
if (Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIR})
else()
  message(FATAL_ERROR "boost is not found")
endif()

add_executable(${EXECUTABLE} ${SOURCES} )
target_link_libraries(${EXECUTABLE} ${Boost_LIBRARIES} )
