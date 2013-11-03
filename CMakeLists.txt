cmake_minimum_required(VERSION 2.8)

# setup project variables
set(PROJECT_NAME FortranToCHeaders)
set(EXT_PROJECTS_DIR external)
set(LIBRARY ${PROJECT_NAME}_lib)
set(EXECUTABLE ${PROJECT_NAME})
project(${PROJECT_NAME} CXX)

# find boost
set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.48.0 COMPONENTS program_options)
if (Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIR})
else()
  message(FATAL_ERROR "boost is not found")
endif()

# add include dirs
include_directories("${CMAKE_SOURCE_DIR}/include")

# build library
file(GLOB_RECURSE LIBRARY_SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")
message(STATUS "library sources = ${LIBRARY_SOURCES}")
add_library(${LIBRARY} SHARED ${LIBRARY_SOURCES})
target_link_libraries(${LIBRARY} ${Boost_LIBRARIES} )


# build program
file(GLOB_RECURSE EXECUTABLE_SOURCES "${CMAKE_SOURCE_DIR}/program/*.cpp")
message(STATUS "executable sources = ${EXECUTABLE_SOURCES}")
add_executable(${EXECUTABLE} ${EXECUTABLE_SOURCES} )
target_link_libraries(${EXECUTABLE} ${LIBRARY} )


# build tests (if enabled)
if (BUILD_TESTS)
  add_subdirectory(${EXT_PROJECTS_DIR}/gtest)
  
  enable_testing()
  set(TESTS ${PROJECT_NAME}_test)
  include_directories(${GTEST_INCLUDE_DIRS})
  
  file(GLOB TEST_SRC_FILES ${CMAKE_SOURCE_DIR}/test/*.cpp)
  add_executable(${TESTS} ${TEST_SRC_FILES})
  add_dependencies(${TESTS} googletest)
  
  
  if(NOT WIN32)
    #target_link_libraries(${TESTS} pthread)
    target_link_libraries(${TESTS}
      ${LIBRARY}
      ${GTEST_LIBS_DIR}/libgtest.a
      ${GTEST_LIBS_DIR}/libgtest_main.a)
  else()
    target_link_libraries(${TESTS}
      debug ${GTEST_LIBS_DIR}/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_FIND_LIBRARY_SUFFIXES}
      optimized ${GTEST_LIBS_DIR}/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_FIND_LIBRARY_SUFFIXES})
    target_link_libraries(${TESTS}
      debug ${GTEST_LIBS_DIR}/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES}
      optimized ${GTEST_LIBS_DIR}/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES})
  endif()
  
  add_test(AllTests ${TESTS})
endif()

