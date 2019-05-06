final: plagiarismCatcher.o FileChunks.o getFileNames.o Output.o
	g++ -std=c++11 -o plagiarismCatcher plagiarismCatcher.o FileChunks.o getFileNames.o Output.o
driver: plagiarismCatcher.cpp plagiarismCatcher.h
	g++ -o plagiarismCatcher.o -c -std=c++11 plagiarismCatcher.cpp
FileChunks.o: FileChunks.cpp FileChunks.h
	g++ -o FileChunks.o -c -std=c++11 FileChunks.cpp
getFileNames.o: getFileNames.cpp getFileNames.h
	g++ -o getFileNames.o -c -std=c++11 getFileNames.cpp
Output.o: Output.cpp Output.h
	g++ -o Output.o -c -std=c++11 Output.cpp

