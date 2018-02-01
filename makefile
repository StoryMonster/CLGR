objs = Clgr.o CommandLineParser.o FileBrowser.o utils.o
CLGR: ${objs}
	@echo "building CLGR"
	@g++ -std=c++11 -o CLGR ${objs}
	@echo "built CLGR"
utils.o: src/common/utils.cpp src/common/utils.hpp src/common/DeviceManager.hpp
	@echo "building utils.o"
	@g++ -std=c++11 -D__WINDOWS__ -c src/common/utils.cpp
CommandLineParser.o: src/common/CommandLineParser.cpp src/common/CommandLineParser.hpp src/types/SearchInfo.hpp
	@echo "building CommandLineParser.o"
	@g++ -std=c++11 -D__WINDOWS__ -c src/common/CommandLineParser.cpp
FileBrowser.o: src/common/FileBrowser.cpp src/types/FileInfo.hpp src/common/FileBrowser.hpp
	@echo "building FileBrowser.o"
	@g++ -std=c++11 -D__WINDOWS__ -c src/common/FileBrowser.cpp
Clgr.o: src/main/Clgr.cpp src/Common/Logger.hpp src/common/CommandLineParser.hpp src/types/SearchInfo.hpp \
        src/main/HelpDisplayer.hpp src/main/FileSearcher.hpp src/main/TextSearcher.hpp
	@echo "building Clgr.o"
	@g++ -std=c++11 -D__WINDOWS__ -c src/main/Clgr.cpp
clean:
	rm *.o
	rm CLGR.exe