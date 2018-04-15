#!/bin/bash
export CPLUS_INCLUDE_PATH=${PWD}/externals/mingw-std-threads:${PWD}:${CPLUS_INCLUDE_PATH}
make platform=linux
mkdir build && mkdir build/bin
mv *.o build/
mv CLGR build/bin/
