# CLGR V4.1.0

dochen 2019-01-14


### How to build
**windows**
```
mkdir build; cd build
cmake -G "MinGW Makefile" -DCMAKE_SH="CMAKE_SH-NOTFOUND" -DWINDOWS=ON ..
make
```
**linux**
```
mkdir build && cd build
cmake ..
make
```