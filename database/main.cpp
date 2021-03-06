/*
Ben Brenkman, Section 3, JustBrenkman@gmail.com
Purpose: Creates a list of inputs based on the input file
*/

#include <string>
#include <iostream>
#include <fstream>
#include "LexicalAnalyzer.h"
#include "DataParser.h"
#include "Interpreter.h"

// Just some constants for niceties
const int FILE_INPUT = 1;

int main(int argc, char **argv) {

    try {
        if (argc > 1) {
            // Create a file stream to pull in the file data
            std::ifstream file(argv[FILE_INPUT]);

            //std::cout << "Opening File: " << argv[FILE_INPUT] << std::endl;

            std::string str;
            // Copy over the whole file into the string we just created
            file.seekg(0, std::ios::end);
            str.reserve(static_cast<unsigned long>((int) file.tellg()));
            file.seekg(0, std::ios::beg);

            //std::cout << "Copying file over..." << std::endl;
            str.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

            // Create our Lexical Analyzer and proccess the string
            auto *lex = new LexicalAnalyzer;
            lex->proccessInput(str);

            // Output the values generated by the lexical analyzer
//            std::cout << *lex << std::endl;

            // Checking the validity of the input file according to our grammar
            DataParser dataParser(lex);
            try {
                // This checks the validity and throws an error if not
                dataParser.checkValidity();
            } catch (std::string &e) {
                std::cout << "Invalid: " << e << std::endl;
            }

            dataParser.clean();
            lex->clean();
            delete lex;

        } else {
            std::cout << "No input file specified" << std::endl;
        }
    }
    catch (std::string &e) {
        // If there was an error with the lex or FSM ouput it here
        std::cout << e << std::endl;
    }

    return 0;
}
