cmake_minimum_required(VERSION 3.1)


project(CLGR VERSION 1.0
        DESCRIPTION "this is an interesting project"
        LANGUAGES CXX)

set(HEADERS src/search/FileSearcher.hpp
            src/search/TextSearcher.hpp
            src/search/ClgrSearcher.hpp
            src/common/functions.hpp
            src/common/MatchedLine.hpp
            src/threads/FileQueue.hpp
            src/threads/Pool.hpp
            src/args/Args.hpp)

set(SOURCES src/main.cpp
            src/search/FileSearcher.cpp
            src/search/TextSearcher.cpp
            src/search/ClgrSearcher.cpp
            src/common/functions.cpp
            src/threads/FileQueue.cpp
            src/threads/Pool.cpp
            src/args/Args.cpp)

#add_definitions(-D __WINDOWS__)
add_compile_options(-std=c++14 -g)
add_executable(clgr ${HEADERS} ${SOURCES})
target_link_libraries(clgr pthread)