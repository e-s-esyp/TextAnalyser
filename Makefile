complete:
	g++ -c -std=gnu++14 -O3 myStrings.cpp -o myStrings.o
	g++ -c -std=gnu++14 -O3 logger.cpp -o logger.o
	g++ -c -std=gnu++14 -O3 lineParserChar.cpp -o lineParserChar.o
	g++ -c -std=gnu++14 -O3 analyzer.cpp -o analyzer.o
	g++ -c -std=gnu++14 -O3 dirAnalyzer.cpp -o  dirAnalyzer.o
	g++ -c -std=gnu++14 -O3 main.cpp -o  main.o
	g++ main.o myStrings.o logger.o lineParserChar.o analyzer.o dirAnalyzer.o -o analyzer.elf
all:
	g++ -std=gnu++14 -O3 main.cpp myStrings.cpp logger.cpp lineParserChar.cpp analyzer.cpp dirAnalyzer.cpp -o analyzer.elf
clean:
	rm -rf *.o analyzer.elf