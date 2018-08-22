ifeq (${platform}, linux)
    opts = -std=c++11 -D__LINUX__ -lpthread
else
    opts = -std=c++11 -D__WINDOWS__
endif
objs = Clgr.o CommandLineParser.o FileBrowser.o utils.o Semaphore.o SearchFilterFactory.o
CLGR: ${objs}
	@echo "building CLGR"
	@g++ ${opts} -g ${objs} -o CLGR
	@echo "built CLGR"

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
SearchFilterFactory.o: src/types/SearchInfo.hpp src/common/SearchFilterFactory.cpp src/common/SearchFilterFactory.hpp src/common/utils.cpp
	@echo "building SearchFilterFactory.o"
	@g++ ${opts} -c src/common/SearchFilterFactory.cpp
Clgr.o: src/main/Clgr.cpp src/common/CommandLineParser.hpp src/types/SearchInfo.hpp \
        src/main/HelpDisplayer.hpp src/main/FileSearcher.hpp src/main/TextSearcher.hpp \
		src/common/TimerService.hpp
	@echo "building Clgr.o"
	@g++ ${opts} -c src/main/Clgr.cpp
clean:
	rm build/* -rf
