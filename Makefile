all:
	g++ -pthread -std=gnu++14 -O3 main.cpp myStrings.cpp logger.cpp stringLogger.cpp lineParserChar.cpp analyzer.cpp dirAnalyzer.cpp -o analyzer.elf
clean:
	rm -rf *.o analyzer.elf