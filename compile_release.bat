@echo off
del .\\build\\bin\\CLGR.exe
echo -- 10%%
g++ -std=c++11 ./src/Clgr.cpp -o ./build/bin/CLGR.exe -Wall -g
echo -- 100%%

echo clgr.exe compile complete, and is saved into ./build/bin
pause