# CLGR V4.1.0

dochen 2018/12/26

In this version, the cross platform function is tested successfully, both on linux and windows it works well.

advantages:
1. work on both linux and windows
2. provides text and file search functions
3. can specify the search filed to decrease the search time
4. text search is multi-thread search, and it's safe. file search is single-thread
5. add file filter function when text search, it helps decrease lots of time in searching
6. support self-define search options


### How to build
**windows**
```
mkdir build; cd build
cmake -G "MinGW Makefile" ..
make
```
**linux**
```
mkdir build && cd build
cmake ..
make
```