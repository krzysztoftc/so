#cmake_minimum_required(VERSION 3.5)
project(ncurses)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lncurses -lpthread")
find_package(Curses REQUIRED)
find_package(Threads REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(dir ${CMAKE_CURRENT_SOURCE_DIR}/Compile)
find_package(Curses REQUIRED)
find_package(Threads REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
set(SOURCE_FILES
        main.cpp
        src/Client.cpp
        src/Client.h
        src/Station.cpp
        src/Station.h src/mutex.h src/place.h)

set(EXECUTABLE_OUTPUT_PATH ${dir} CACHE PATH "Build directory" FORCE)
set(LIBRARY_OUTPUT_PATH ${dir} CACHE PATH "Build directory" FORCE)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${dir})
set(CMAKE_BUILD_FILES_DIRECTORY ${dir})
set(CMAKE_BUILD_DIRECTORY ${dir})
set(CMAKE_BINARY_DIR  ${dir})
SET(EXECUTABLE_OUTPUT_PATH ${dir})
SET(LIBRARY_OUTPUT_PATH ${dir}lib)
SET(CMAKE_CACHEFILE_DIR ${dir})
add_executable(ncurses ${SOURCE_FILES})
target_link_libraries(ncurses ${CURSES_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})






