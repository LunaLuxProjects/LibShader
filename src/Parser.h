#pragma once
#include "Lexer.h"

typedef enum ASTTypeID 
{
    AST_ROOT = 0,
    AST_BLOCK = 1,
    AST_FUNC_DEF = 2,
    AST_FUNC_CALL = 3,
    AST_EXPRESSION = 4,
    AST_LITERAL = 5,
}ASTTypeID;

typedef enum ASTExpressionType
{
    ASTE_RETURN = 0,
    ASTE_VAR_DEFINED = 1
} ASTExpressionType;

typedef enum ASTDataType
{
    NONE_TYPE = 0,
    VOID_TYPE = 1,
    INT8_TYPE = 2,
    INT16_TYPE = 3,
    INT32_TYPE = 4,
    INT64_TYPE = 5,
    INT128_TYPE = 6,
    UINT8_TYPE = 7,
    UINT16_TYPE = 8,
    UINT32_TYPE = 9,
    UINT64_TYPE = 10,
    UINT128_TYPE = 11,
    FLOAT32_TYPE = 12,
    FLOAT64_TYPE = 13,
    FLOAT128_TYPE = 14,
    STR_TYPE = 15
} ASTDataType;

typedef enum ASTLiteralDataType
{
    VAR_TYPE = 0,
    INT_TYPE = 1,
    FLOAT_TYPE = 2,
    STRING_TYPE = 3
} ASTLiteralDataType;

struct ASTNode
{
    public:
    virtual const ASTTypeID getTypeID() const noexcept = 0;
};

struct ASTRoot : public ASTNode
{
    std::vector<const ASTNode *> children;
    const ASTTypeID getTypeID() const noexcept override { return AST_ROOT;}
};

struct ASTFuncDef : public ASTNode
{
    const std::string name;
    std::vector<const ASTNode *> args;
    std::vector<const ASTNode *> body;
    ASTDataType return_type;
    const ASTTypeID getTypeID() const noexcept override { return AST_FUNC_DEF;}
    explicit ASTFuncDef(const std::string name_in): name(std::move(name_in)){}
};

struct ASTExpression : public ASTNode
{
    std::vector<const ASTNode *> list;
    std::string name = "";
    ASTExpressionType type;
    const ASTTypeID getTypeID() const noexcept override { return AST_EXPRESSION;}
};

struct ASTLiteral : public ASTNode
{
    std::string value;
    ASTLiteralDataType type;
    ASTDataType data_type = NONE_TYPE;
    const ASTTypeID getTypeID() const noexcept override { return AST_LITERAL;}
};

class Parser
{
    LexStateMachine* lexer;
    Lex word_data;
    bool hold = false;
    Lex held_lex;
    [[noreturn]]void error(const char *) noexcept;
    [[nodiscard]]const bool isKeyword(const std::string_view) noexcept;
    [[nodiscard]]const bool isNumber() noexcept;
    [[nodiscard]]const ASTDataType getTypeID() noexcept;
    [[nodiscard]]const ASTDataType getFromHash(size) noexcept;
    const std::string_view getNextWord(bool ignore_newline = true) noexcept;
    [[nodiscard]]const std::vector<const ASTNode *> parseArgs();
    [[nodiscard]]const size getHash(std::string_view) noexcept;
    [[nodiscard]]const std::vector<const ASTNode *> parseBlock();
    [[nodiscard]]const bool isValidName() noexcept;
    public:
    explicit Parser(std::string_view source) : lexer(new LexStateMachine(std::move(source))){};
    const ASTNode* parse() noexcept;
};