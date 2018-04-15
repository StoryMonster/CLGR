@set CPLUS_INCLUDE_PATH=%CPLUS_INCLUDE_PATH%;%cd%\externals\mingw-std-threads;%cd%
@make platform=windows
@md build && md build\\bin
@move *.o build
@move CLGR.exe build\\bin
