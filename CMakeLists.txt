cmake_minimum_required(VERSION 3.9)
project(analizer)

set(CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_FLAGS "-pthread")

add_library(logger logger.h logger.cpp)

add_library(stringLogger stringLogger.h stringLogger.cpp)

add_library(lineParserChar lineParserChar.h lineParserChar.cpp myStrings.cpp)
target_link_libraries(lineParserChar stringLogger)

add_library(parserAnalyzer analyzer.h analyzer.cpp)
target_link_libraries(parserAnalyzer lineParserChar stringLogger)

add_library(dirAnalyzer dirAnalyzer.h dirAnalyzer.cpp myStrings.cpp)

add_executable(analyzer main.cpp mainStructure.h)
target_link_libraries(analyzer logger dirAnalyzer parserAnalyzer)