#pragma once
#include <vector>
#include <string>

typedef enum ASTTypeID 
{
    AST_ROOT = 0,
    AST_BLOCK = 1,
    AST_FUNC_DEF = 2,
    AST_FUNC_CALL = 3,
    AST_EXPRESSION = 4,
    AST_BINARY = 5,
    AST_LITERAL = 6,
} ASTTypeID;

typedef enum ASTExpressionType
{
    ASTE_RETURN = 0,
    ASTE_VAR_DEFINED = 1,
    ASTE_PRAM_LIST = 2,
} ASTExpressionType;

typedef enum ASTDataType
{
    NOT_DETERMINED_TYPE = 0,
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
    FLOAT128_TYPE = 14
} ASTDataType;

typedef enum ASTOperatorType
{
    ADD_TYPE = 0,
    SUB_TYPE = 1,
    DIV_TYPE = 2,
    MUL_TYPE = 3,
    AND_TYPE = 4,
    OR_TYPE = 5,
} ASTOperatorType;

struct ASTNode
{
    public:
    virtual ASTTypeID getTypeID() const noexcept = 0;
};

struct ASTRoot : public ASTNode
{
    std::vector<const ASTNode *> children;
    ASTTypeID getTypeID() const noexcept override { return AST_ROOT;}
};

struct ASTExpression : public ASTNode
{
    std::vector<const ASTNode *> list;
    ASTExpressionType type;
    std::string extra_data;
    ASTTypeID getTypeID() const noexcept override { return AST_EXPRESSION;}
};

struct ASTBlock : public ASTNode
{
    std::vector<const ASTNode *> list;
    ASTTypeID getTypeID() const noexcept override { return AST_BLOCK;}
};

struct ASTFuncDef : public ASTNode
{
    const std::string name;
    const ASTExpression * args;
    const ASTBlock * body;
    ASTDataType return_type;
    ASTTypeID getTypeID() const noexcept override { return AST_FUNC_DEF;}
    explicit ASTFuncDef(const std::string name_in): name(std::move(name_in)){}
};



struct ASTBinaryExpression : public ASTNode
{
    const ASTNode * right;
    const ASTNode * left;
    ASTOperatorType op;
    ASTTypeID getTypeID() const noexcept override { return AST_BINARY;}
};

struct ASTLiteral : public ASTNode
{
    std::string value;
    ASTDataType data_type = NOT_DETERMINED_TYPE;
    ASTTypeID getTypeID() const noexcept override { return AST_LITERAL;}
};