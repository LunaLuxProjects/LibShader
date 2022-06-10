#include <LibShader.h>
#include "Lexer.h"
#include <chrono>
#include <future>
#include <iostream>

#define TO_STRING_CASE(x) case x: return #x;

const char * toString (TokenKey key)
{
    switch (key)
    {
        TO_STRING_CASE(WORD_KEY)
        TO_STRING_CASE(NUMBER_KEY)
        TO_STRING_CASE(KEYWORD_KEY)
        TO_STRING_CASE(OP_KEY)
        TO_STRING_CASE(STR_KEY)
        TO_STRING_CASE(NAMESPACE_KEY)
        default: return "";
    }
}


void sharedStages(std::string& source)
{
    auto start = std::chrono::steady_clock::now();
    auto tokens = lex(source);
    auto end = std::chrono::steady_clock::now();
    lexCheck(tokens);
    for(auto& t : tokens)
    {
        std::printf("TOKEN: (token_key - %s,token_value - \"%s\" )\n",toString(t.key),t.value.c_str());
    }
    
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
    std::exit(0);
}

const glmErrorOrData compileToSpirv(std::vector<std::string>,std::string& source)
{
    sharedStages(source);
    return glmErrorOrData(true,"not implemented");
}

const glmErrorOrData compileToX86(std::vector<std::string> flags,std::string& source)
{
    sharedStages(source);
    return glmErrorOrData(true,"not implemented");
}
