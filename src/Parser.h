#pragma once
#include "Lexer.h"
#include "AST.h"
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
class Parser
{
    bool has_error = false;
    Lexer* lexer;
    rapidjson::StringBuffer msg;
    rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer;
    [[nodiscard]]ASTLiteral* parseLiteral() noexcept;
    [[nodiscard]]const ASTExpression* parseVar(lexToken* current_token) noexcept;
    [[nodiscard]]const ASTExpression* parseArgs() noexcept;
    [[nodiscard]]const ASTBlock* parseBlock() noexcept;
    [[nodiscard]]bool isValidName(const lexToken&) noexcept;
    [[nodiscard]]bool isDataType(const lexToken&) noexcept;
    [[nodiscard]]bool isInteger(const lexToken&) noexcept;
    [[nodiscard]]ASTDataType parseDataType(const lexToken&) noexcept;
    void error(const lexToken&,const char*) noexcept;
    void warn(const lexToken&,const char*) noexcept;
    public:
    explicit Parser(std::string source) noexcept : lexer(new Lexer(std::move(source))), writer(new rapidjson::PrettyWriter<rapidjson::StringBuffer>(msg))
    {
        writer->StartObject();
        writer->Key("List");
        writer->StartArray();
    };
    [[nodiscard]]bool hadError() const noexcept { return has_error; };
    [[nodiscard]]const char* getMsg() noexcept 
    {
        writer->EndArray();
        writer->EndObject();
        return msg.GetString();
    }
    [[nodiscard]]const ASTNode* parse() noexcept;
};