all:
	g++ -pthread -std=gnu++14 -O3 pngWriter.cpp main.cpp myStrings.cpp logger.cpp stringLogger.cpp lineParserChar.cpp analyzer.cpp dirAnalyzer.cpp -lpng -lX11 -o analyzer.elf
clean:
	rm -rf *.o analyzer.elf