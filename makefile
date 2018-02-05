ifeq (${platform}, linux)
    opts = -std=c++11 -D__LINUX__ -lpthread
else
    opts = -std=c++11 -D__WINDOWS__
endif
objs = Clgr.o CommandLineParser.o FileBrowser.o utils.o Semaphore.o
CLGR: ${objs}
	@echo "building CLGR"
	@g++ ${opts} -g ${objs} -o CLGR 
	@echo "built CLGR"
    ifeq (${platform}, linux)
		@mkdir -p build build/bin
		@mv *.o build/
		@mv CLGR build/bin
    else
		@md build build/bin
		@move *.o build/*.o
		@move CLGR.exe build/bin/CLGR.exe
    endif
	
Semaphore.o: src/common/Semaphore.cpp src/common/Semaphore.hpp
	@echo "building Semaphore.o"
	@g++ ${opts} -c src/common/Semaphore.cpp
utils.o: src/common/utils.cpp src/common/utils.hpp src/common/DeviceManager.hpp
	@echo "building utils.o"
	@g++ ${opts} -c src/common/utils.cpp
CommandLineParser.o: src/common/CommandLineParser.cpp src/common/CommandLineParser.hpp src/types/SearchInfo.hpp
	@echo "building CommandLineParser.o"
	@g++ ${opts} -c src/common/CommandLineParser.cpp
FileBrowser.o: src/common/FileBrowser.cpp src/types/FileInfo.hpp src/common/FileBrowser.hpp
	@echo "building FileBrowser.o"
	@g++ ${opts} -c src/common/FileBrowser.cpp
Clgr.o: src/main/Clgr.cpp src/common/CommandLineParser.hpp src/types/SearchInfo.hpp \
        src/main/HelpDisplayer.hpp src/main/FileSearcher.hpp src/main/TextSearcher.hpp
	@echo "building Clgr.o"
	@g++ ${opts} -c src/main/Clgr.cpp
clean:
	rm build/* -rf
