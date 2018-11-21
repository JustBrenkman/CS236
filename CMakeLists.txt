cmake_minimum_required(VERSION 3.12)
#project(DataParser/lab2)
#
#set(CMAKE_CXX_STANDARD 17)
#
#set(SOURCE_FILES DataParser/main.cpp
#        DataParser/FiniteStateMachine.h
#        DataParser/LexicalAnalyzer.h DataParser/LexicalAnalyzer.cpp DataParser/DataParser.cpp DataParser/DataParser.h DataParser/Grammar.cpp DataParser/Grammar.h DataParser/GrammarException.cpp DataParser/GrammarException.h DataParser/Schemes.cpp DataParser/Schemes.h DataParser/Facts.cpp DataParser/Facts.h DataParser/Rules.cpp DataParser/Rules.h DataParser/Queries.cpp DataParser/Queries.h DataParser/Utilities.cpp DataParser/Utilities.h DataParser/Operator.cpp DataParser/Operator.h DataParser/Expression.cpp DataParser/Expression.h DataParser/Parameter.cpp DataParser/Parameter.h DataParser/DLString.cpp DataParser/DLString.h DataParser/Id.cpp DataParser/Id.h DataParser/Predicate.cpp DataParser/Predicate.h DataParser/HeadPredicate.cpp DataParser/HeadPredicate.h DataParser/Query.cpp DataParser/Query.h DataParser/Rule.cpp DataParser/Rule.h DataParser/Fact.cpp DataParser/Fact.h DataParser/Scheme.cpp DataParser/Scheme.h DataParser/Domain.cpp DataParser/Domain.h)
#
#
#add_executable(lab2 ${SOURCE_FILES})
#
#
## Lab3 stuff
#project(lab3)
#set(CMAKE_CXX_STANDARD 17)
#if (NOT WIN32)
#    set(CMAKE_CXX_FLAGS -Werror)
#endif(NOT WIN32)
#
#file(GLOB SOURCE_FILES database/*.cpp database/*.h)
#
#add_executable(lab3 ${SOURCE_FILES} database/Interpreter.cpp database/Interpreter.h)

# Lab4 stuff
project(lab4)
set(CMAKE_CXX_STANDARD 17)
if (NOT WIN32)
    set(CMAKE_CXX_FLAGS -Werror)
endif(NOT WIN32)

file(GLOB SOURCE_FILES lab4/*.cpp lab4/*.h)
add_executable(lab4 ${SOURCE_FILES})