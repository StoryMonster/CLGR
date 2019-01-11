cmake_minimum_required(VERSION 3.4)

SET(PROJECT_NAME CLGR)
SET(CMAKE_MAKE_PROGRAM "MinGW Makefiles")
SET(CMAKE_CXX_COMPILER "$ENV{MINGW_HOME}/bin/g++.exe")
include_directories(${CMAKE_SOURCE_DIR})

project(${PROJECT_NAME})

set(SOURCES src/common/CommandLineParser.cpp
            src/common/FileBrowser.cpp
            src/common/SearchFilterFactory.cpp
            src/common/Semaphore.cpp
            src/common/utils.cpp
            src/main/Clgr.cpp)

set(HEADERS src/common/CommandLineParser.hpp
            src/common/DeviceManager.hpp
            src/common/FileBrowser.hpp
            src/common/FileReader.hpp
            src/common/SearchFilterFactory.hpp
            src/common/Semaphore.hpp
            src/common/TimerService.hpp
            src/common/utils.hpp
            src/exceptions/FileError.hpp
            src/exceptions/ParserError.hpp
            src/exceptions/SemaphoreError.hpp
            src/main/FileSearcher.hpp
            src/main/HelpDisplayer.hpp
            src/main/TextSearcher.hpp
            src/main/VersionControler.hpp
            src/types/FileInfo.hpp
            src/types/LinesContainer.hpp
            src/types/SearchInfo.hpp)
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -D__WINDOWS__ -Wall -std=c++14 -g")
add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})
