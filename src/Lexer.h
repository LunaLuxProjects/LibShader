#pragma once
#include <LibShader/Compiler.h>
#include <lstd/DataType.h>
#include <lstd/String.h>
#include <lstd/ClibLink.h>
#include <vector>
typedef enum LexTokenEnum : uint16
{
    T_NONE = 0,
    T_IDENTIFIER = 1,
    T_FUNC = 2,
    T_RET = 3,
    T_R_SQUIGGLY = 4,
    T_L_SQUIGGLY = 5,
    T_R_CURLY = 6,
    T_L_CURLY = 7,
    T_COMMA = 8,
    T_DOT = 9,
    T_ADD = 10,
    T_SUB = 11,
    T_MUL = 12,
    T_DIV = 13,
    T_AND = 14,
    T_EQUAL = 15,
    T_OR = 16,
    T_R_ARROW = 17,
    T_L_ARROW = 18,
    T_MODULO = 19,
    T_QUOTE = 20,
    T_SINGLE_LETTER_QUOTE = 21,
}LexTokenEnum;

typedef struct GmlSpan 
{
    data_size start;
    data_size end;
}GmlSpan;

typedef struct lexToken
{
    LexTokenEnum token = T_NONE;
    lstd::string extra_data = "";
    uint64 line = 0;
    GmlSpan span = {0,0};

    inline bool operator != (const uint16 tok) const
    {
        return token != tok;
    }

    inline bool operator == (const uint16 tok) const
    {
        return token == tok;
    }
} lexToken;

class Lexer
{
    std::vector<lexToken> tokens;
    lstd::string source;
    data_size index = 0;
    [[nodiscard]]inline bool eof() const noexcept { return index <= source.size(); };
    [[nodiscard]]char getNextChar() noexcept;
    [[nodiscard]]inline char peekNextChar()const noexcept;
    [[nodiscard]]GmlSpan parseSpanNextToken() noexcept;
    [[nodiscard]]bool _break(const char c) noexcept;
    public:
    explicit Lexer(lstd::string source_in);
    [[nodiscard]]inline bool eot() const noexcept { return index < tokens.size(); };
    inline void skipNextToken() noexcept { index++; };
    [[nodiscard]] lexToken &getNextToken() noexcept
    {
        return tokens[lstd::min<data_size>(index++, tokens.size())];
    };
    [[nodiscard]] const lexToken &peekNextToken(uint64 offset = 0) const noexcept
    {
        return tokens[lstd::min<data_size>(index + offset, tokens.size() - 1)];
    };
    [[nodiscard]]inline const lstd::string& refSource() const noexcept { return source;}; 
};