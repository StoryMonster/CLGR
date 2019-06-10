cmake_minimum_required(VERSION 3.4)

SET(PROJECT_NAME CLGR)
project(${PROJECT_NAME})

if (WINDOWS)
    message("build ${PROJECT_NAME} on windows")
    SET(CMAKE_MAKE_PROGRAM "MinGW Makefiles")
    SET(CMAKE_CXX_COMPILER "$ENV{MINGW_HOME}/bin/g++.exe")
    SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -D__WINDOWS__ -Wall -std=c++14")
    include_directories(externals/mingw-std-threads)
else()
    message("build ${PROJECT_NAME} on linux")
    SET(CMAKE_CXX_COMPILER g++)
    SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -D__LINUX__ -Wall -std=c++14")
endif()

include_directories(${CMAKE_SOURCE_DIR})

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
add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})

if (WINDOWS)
    message("no need to link thread libraries in windows")
elseif ()
    target_link_libraries(${PROJECT_NAME} pthread)
endif ()

