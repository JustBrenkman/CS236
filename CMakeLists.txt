cmake_minimum_required(VERSION 3.12)
project(lab2)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp
        FiniteStateMachine.h
        LexicalAnalyzer.h LexicalAnalyzer.cpp DataParser.cpp DataParser.h Grammar.cpp Grammar.h GrammarException.cpp GrammarException.h Schemes.cpp Schemes.h Facts.cpp Facts.h Rules.cpp Rules.h Queries.cpp Queries.h)

add_executable(lab2 ${SOURCE_FILES})