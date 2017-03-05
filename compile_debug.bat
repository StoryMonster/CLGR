@echo off
del build\\bin\\CLGR_debug.exe
echo -- 10%%
g++ -std=c++11 src/Clgr.cpp -D_DEBUG -o build/bin/CLGR_debug.exe -g -Wall
echo -- 100%%
echo -- CLGR_debug.exe compile complete, and is saved into ./build/bin
pause