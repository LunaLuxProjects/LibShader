#pragma once
#include "Lexer.h"

struct ASTRootNode
{

};

class Parser
{
    LexStateMachine* lexer;

    public:
    explicit Parser(std::string_view source) : lexer(new LexStateMachine(std::move(source))){};
    const ASTRootNode parse() noexcept;
};