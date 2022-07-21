#include "Parser.h"
#include <lstd/LookUpTable.h>
#include <lstd/Util.h>
#include <string>
std::string x();

char Lexer::getNextChar() noexcept
{
    return source[lstd::min<data_size>(index++, source.size())];
}

char Lexer::peekNextChar() const noexcept
{
    return source[lstd::min<data_size>(index, source.size())];
}

bool Lexer::_break(const char c) noexcept
{
    if (!eof())
        return true;
    switch (c)
    {
    case '\0':
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
        if (_break(getNextChar()))
            break;
        if (_break(peekNextChar()))
            break;
    }
    uint64 offset = index;
    return {start, offset};
}

const data_size reject_lookup[] = {lstd::hash<lstd::string>{}("\n"), lstd::hash<lstd::string>{}(" "),
                                   lstd::hash<lstd::string>{}("\r"), lstd::hash<lstd::string>{}("\t"),
                                   lstd::hash<lstd::string>{}(";")};

const lstd::ReadOnlyLookupTable<data_size, LexTokenEnum> lookup = {
    {lstd::hash<lstd::string>{}("func"), T_FUNC},    {lstd::hash<lstd::string>{}("ret"), T_RET},
    {lstd::hash<lstd::string>{}("{"), T_L_SQUIGGLY}, {lstd::hash<lstd::string>{}("}"), T_R_SQUIGGLY},
    {lstd::hash<lstd::string>{}("("), T_L_CURLY},    {lstd::hash<lstd::string>{}(")"), T_R_CURLY},
    {lstd::hash<lstd::string>{}(","), T_COMMA},      {lstd::hash<lstd::string>{}("."), T_DOT},
    {lstd::hash<lstd::string>{}("+"), T_ADD},        {lstd::hash<lstd::string>{}("-"), T_SUB},
    {lstd::hash<lstd::string>{}("/"), T_DIV},        {lstd::hash<lstd::string>{}("*"), T_MUL},
    {lstd::hash<lstd::string>{}("="), T_EQUAL},      {lstd::hash<lstd::string>{}("and"), T_AND},
    {lstd::hash<lstd::string>{}("or"), T_OR},        {lstd::hash<lstd::string>{}(">"), T_L_ARROW},
    {lstd::hash<lstd::string>{}("<"), T_R_ARROW},    {lstd::hash<lstd::string>{}("%"), T_MODULO},
    {lstd::hash<lstd::string>{}("\""), T_QUOTE},     {lstd::hash<lstd::string>{}("\'"), T_SINGLE_LETTER_QUOTE},
};

Lexer::Lexer(lstd::string source_in)
{
    source = lstd::move(source_in);
    uint64 line = 0;
    while (eof())
    {
        GmlSpan span = parseSpanNextToken();
        lstd::string word = source.substr(span.start, lstd::max<data_size>(1, span.end - span.start));
        if(word == '\0') continue;
        data_size view = lstd::hash<lstd::string>{}(word);
        bool found = false;
        for (auto &item : reject_lookup)
        {
            if (item == view)
            {
                found = true;
                break;
            }
        }
        if (view == reject_lookup[0])
            line++;
        if (found)
            continue;
        lexToken token;
        token.line = line;
        token.span = lstd::move(span);

        for (auto &item : lookup)
        {
            if (item == view)
            {
                token.token = item.value;
                found = true;
                break;
            }
        }
        if (!found)
        {
            token.token = T_IDENTIFIER;
            token.extra_data = source.substr(span.start, lstd::max<data_size>(1, span.end - span.start));
        }
        tokens.emplace_back(std::move(token));
    }
    index = 0;
};