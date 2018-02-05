#!/bin/bash
export CPLUS_INCLUDE_PATH=${PWD}/externals/mingw-std-threads:${PWD}:${CPLUS_INCLUDE_PATH}
make platform=linux
