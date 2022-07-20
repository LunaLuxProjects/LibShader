#include "Parser.h"

char Lexer::getNextChar() noexcept
{
    return source[std::min<size>(index++,source.size())];
}

char Lexer::peekNextChar() const noexcept
{
    return source[std::min<size>(index,source.size())];
}

bool Lexer::_break(const char c) noexcept
{
    if(!eof()) return true;
    switch (c)
    {
        case '+':
        case '&':
        case '%':
        case '/':
        case '*':
        case '-':
        case '=':
        case ' ':
        case '\n':
        case '(':
        case ')':
        case '{':
        case '}':
        case '[':
        case ']':
        case ':':
        case ';':
        case ',':
        case '.': 
        case '\"':
        case '\'':
            return true;
        default:
            return false;
    }
}

GmlSpan Lexer::parseSpanNextToken() noexcept
{
    uint64 start = index;
    while (eof())
    {
        if(_break(getNextChar())) break;
        if(_break(peekNextChar())) break;
    }
    uint64 offset = index;
    return {start,offset};
}

Lexer::Lexer(std::string source_in)
{
    source = std::move(source_in);
    uint64 line = 0;
    
    const size reject_lookup[] = 
    {
        std::hash<std::string>{}(" "),
        std::hash<std::string>{}("\n"),
        std::hash<std::string>{}("\r"),
        std::hash<std::string>{}("\t"),
        std::hash<std::string>{}(";")
    };
    const std::tuple<size,LexTokenEnum> lookup[] = 
    {
        {std::hash<std::string>{}("func"),T_FUNC},
        {std::hash<std::string>{}("ret"),T_RET},
        {std::hash<std::string>{}("{"),T_L_SQUIGGLY},
        {std::hash<std::string>{}("}"),T_R_SQUIGGLY},
        {std::hash<std::string>{}("("),T_L_CURLY},
        {std::hash<std::string>{}(")"),T_R_CURLY},
        {std::hash<std::string>{}(","),T_COMMA},
        {std::hash<std::string>{}("."),T_DOT},
        {std::hash<std::string>{}("+"),T_ADD},
        {std::hash<std::string>{}("-"),T_SUB},
        {std::hash<std::string>{}("/"),T_DIV},
        {std::hash<std::string>{}("*"),T_MUL},
        {std::hash<std::string>{}("="),T_EQUAL},
        {std::hash<std::string>{}("and"),T_AND},
        {std::hash<std::string>{}("or"),T_OR},
        {std::hash<std::string>{}(">"),T_L_ARROW},
        {std::hash<std::string>{}("<"),T_R_ARROW},
        {std::hash<std::string>{}("%"),T_MODULO},
        {std::hash<std::string>{}("\""),T_QUOTE},
        {std::hash<std::string>{}("\'"),T_SINGLE_LETTER_QUOTE},
    };

    while(eof())
    {
        GmlSpan span = parseSpanNextToken();
        size view = std::hash<std::string>{}(source.substr(span.start, std::max<size>(1,span.end - span.start)));
        bool found = false;
        for(auto& item:reject_lookup)
        {
            if(item == view)
            {
                found = true;
                break;
            }
        }
        if(view == reject_lookup[1]) line++;
        if(found) continue;
        lexToken token;
        token.line = line;
        token.span = std::move(span);
            
        for(auto& item:lookup)
        {
            if(std::get<0>(item) == view)
            {
                token.token = std::get<1>(item);
                found = true;
                break;
            }
        }
        if(!found)
        {
            token.token = T_IDENTIFIER;
            token.extra_data = std::move(source.substr(span.start, std::max<size>(1,span.end - span.start)));
        }
        tokens.emplace_back(std::move(token));
    }
    index = 0;
};