# CLGR V4.1.0

dochen 2018/08/22

In this version, the cross platform function is tested successfully, both on linux and windows it works well.

install steps on windows:
1. go to this folder
2. run "./compile.bat"
then, you will get CLGR.exe in ./build/bin, and you can add CLGR.exe's path into PATH variable

install steps on linux:
1. go to this folder
2. run "./compile.sh"
then, you will get CLGR in ./build/bin, and you can add CLGR's path into PATH variable

advantages:
1. work on both linux and windows
2. provides text and file search functions
3. can specify the search filed to decrease the search time
4. text search is multi-thread search, and it's safe. file search is single-thread
5. add file filter function when text search, it helps decrease lots of time in searching
6. support self-define search options