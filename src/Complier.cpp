#include <LibShader.h>
#include "Parser.h"
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include <iostream>
#include <chrono>
using namespace rapidjson;

const char * idToString(const ASTTypeID& id) noexcept
{
    switch (id)
    {
    case AST_ROOT: return "Program";
    case AST_FUNC_DEF: return "FunctionDef";
    case AST_FUNC_CALL: return "FunctionCall";
    case AST_EXPRESSION: return "Expression";
    case AST_LITERAL: return "Literal";
    default: return "unknown";
    }
}

const char * idToStringL(const ASTLiteralDataType& id) noexcept
{
    switch (id)
    {
    case   VAR_TYPE:
        return "VariableLiteral";
    case INT_TYPE:
        return "IntegerLiteral";
    case FLOAT_TYPE:
        return "FloatLiteral";
    case STRING_TYPE:
        return "StringLiteral";
    default: return "unknown";
    }
}

const char * idToStringT(const ASTDataType& id) noexcept
{
    switch (id)
    {
    case NONE_TYPE: return "None";
    case VOID_TYPE: return "Void";
    case INT8_TYPE: return "int8";
    case INT16_TYPE: return "int16";
    case INT32_TYPE: return "int32";
    case INT64_TYPE: return "int64";
    case INT128_TYPE: return "int128";
    case UINT8_TYPE: return "uint8";
    case UINT16_TYPE: return "uint16";
    case UINT32_TYPE: return "uint32";
    case UINT64_TYPE: return "uint64";
    case UINT128_TYPE: return "uint128";
    case FLOAT32_TYPE: return "float32";
    case FLOAT64_TYPE: return "float64";
    case FLOAT128_TYPE: return "float128";
    case STR_TYPE: return "string";
    default: return "unknown";
    }
}

const char * idToStringE(const ASTExpressionType& id) noexcept
{
    switch (id)
    {
    case ASTE_RETURN: return "ReturnType";
    case ASTE_VAR_DEFINED : return "VariableDefinition";
    default: return "unknown";
    }
}

template<class T>
void writeBranch(T* writer,const ASTNode* node)
{
    writer->StartObject();
    writer->Key("type");
    writer->String(idToString(node->getTypeID()));
    switch(node->getTypeID())
    {
        case AST_ROOT:{
            const ASTRoot* real_node = static_cast<const ASTRoot*>(node);
            writer->Key("body");
            writer->StartArray();
            for(const ASTNode* child: real_node->children)
                writeBranch<T>(writer,child);
            writer->EndArray();
            writer->Key("SourceType");
            writer->String("module");
            break;
        }
        case AST_FUNC_DEF: {
            const ASTFuncDef* real_node = static_cast<const ASTFuncDef*>(node);
            writer->Key("id");
            writer->String(real_node->name.c_str());
            writer->Key("return_type");
            writer->String(idToStringT(real_node->return_type));
            writer->Key("parameters");
            writer->StartArray();
            for(const ASTNode* child: real_node->args)
                writeBranch<T>(writer,child);
            writer->EndArray();
            writer->Key("body");
            writer->StartArray();
            for(const ASTNode* child: real_node->body)
                writeBranch(writer,child);
            writer->EndArray();
            break;
        }
        case AST_FUNC_CALL: {
            
        }
        case AST_EXPRESSION: {
            const ASTExpression* real_node = static_cast<const ASTExpression*>(node);
            writer->Key("id");
            writer->String(idToStringE(real_node->type));
            if(!real_node->name.empty())
            {
                writer->Key("name");
                writer->String(real_node->name.c_str());
            }
            writer->Key("declarations");
            writer->StartArray();
            for(const ASTNode* child: real_node->list)
                writeBranch<T>(writer,child);
            writer->EndArray();
            break;
            
        }
        case AST_LITERAL: {
            const ASTLiteral* real_node = static_cast<const ASTLiteral*>(node);
            writer->Key("data_type");
            if(real_node->data_type == NONE_TYPE)
                writer->String(idToStringL(real_node->type));
            else
                writer->String(idToStringT(real_node->data_type));
            writer->Key("value");
            writer->String(real_node->value.c_str());

        }
        default: break;
    }
    writer->EndObject();
}

void sharedStages(std::string& source)
{ 
    StringBuffer s,s2;
    PrettyWriter<StringBuffer> writer(s);
    Writer<StringBuffer> swriter(s2);
    auto start = std::chrono::steady_clock::now();
    const ASTNode* ast = Parser(source).parse();
    auto end = std::chrono::steady_clock::now();
    writeBranch<PrettyWriter<StringBuffer>>(&writer, ast);
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << s.GetString() << std::endl;
    std::cout << "-------squashed----------" << std::endl;
    writeBranch<Writer<StringBuffer>>(&swriter, ast);
    std::cout << s2.GetString() << std::endl;
    std::cout << "---------time------------" << std::endl;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
    std::exit(0);
}


const glmErrorOrData compileToAST(std::vector<std::string>,std::string& source)
{
    StringBuffer s;
    PrettyWriter<StringBuffer> writer(s);
    const ASTNode* ast = Parser(source).parse();
    writeBranch<Writer<StringBuffer>>(&writer, ast);
    return glmErrorOrData(s.GetString());
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
