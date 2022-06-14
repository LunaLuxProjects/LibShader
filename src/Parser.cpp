#include "Parser.h"

const char* keywords[] = {"void","int8","int16","int32","int64","int128","uint8","uint16","uint32","uint64","uint128","string","func","ret","input","output","import","public","for","while","if","elif"};

const ASTRootNode Parser::parse() noexcept
{
    ASTRootNode root;

    return std::move(root);
}

