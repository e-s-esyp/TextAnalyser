cmake_minimum_required(VERSION 3.9)
project(analizer)

set(CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_FLAGS "-pthread")

add_library(myStrings myStrings.h myStrings.cpp)

add_library(logger logger.h logger.cpp)

add_library(stringLogger stringLogger.h stringLogger.cpp)

add_library(lineParserChar lineParserChar.h lineParserChar.cpp)
target_link_libraries(lineParserChar stringLogger)

add_library(analyzer analyzer.h analyzer.cpp)
target_link_libraries(analyzer lineParserChar stringLogger)

add_library(dirAnalyzer dirAnalyzer.h dirAnalyzer.cpp)
target_link_libraries(dirAnalyzer myStrings)

add_executable(analizer main.cpp mainStructure.h)
target_link_libraries(analizer logger dirAnalyzer analyzer)