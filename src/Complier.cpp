#include <LibShader.h>
#include "Parser.h"
//#include <chrono>
#include <iostream>

void printSubstring(std::string& str, const uint64 start, const uint64 end)
{
    std::cout << "LEX: Data - ";
    for(uint64 i = start; i < end; i++)
        std::cout << str[i];
    std::cout << "|\n";
    std::cout << std::endl;
}

void sharedStages(std::string& source)
{ 
    //auto start = std::chrono::steady_clock::now();
    ASTRootNode ast = Parser(source).parse();
    //auto end = std::chrono::steady_clock::now();
    //std::chrono::duration<double> elapsed_seconds = end-start;
    //std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
    std::exit(0);
}

const glmErrorOrData compileToSpirv(std::vector<std::string>,std::string& source)
{
    sharedStages(source);
    return glmErrorOrData(true,"not implemented");
}

const glmErrorOrData compileToX86(std::vector<std::string>,std::string& source)
{
    sharedStages(source);
    return glmErrorOrData(true,"not implemented");
}
