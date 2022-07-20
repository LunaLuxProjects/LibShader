#include "Parser.h"
#include <algorithm>

const size keyword_lookup[] = 
{
    std::hash<std::string>{}("func"),
    std::hash<std::string>{}("ret"),
    std::hash<std::string>{}("and"),
    std::hash<std::string>{}("or")
};

const std::tuple<size,ASTDataType> data_type_lookup[] = 
{
    {std::hash<std::string>{}("uint8"),UINT8_TYPE},
    {std::hash<std::string>{}("uint16"),UINT16_TYPE},
    {std::hash<std::string>{}("uint32"),UINT32_TYPE},
    {std::hash<std::string>{}("uint64"),UINT64_TYPE},
    {std::hash<std::string>{}("uint128"),UINT128_TYPE},
    {std::hash<std::string>{}("int8"),INT8_TYPE},
    {std::hash<std::string>{}("int16"),INT16_TYPE},
    {std::hash<std::string>{}("int32"),INT32_TYPE},
    {std::hash<std::string>{}("int64"),INT64_TYPE},
    {std::hash<std::string>{}("int128"),INT128_TYPE},
    {std::hash<std::string>{}("float32"),FLOAT32_TYPE},
    {std::hash<std::string>{}("float64"),FLOAT64_TYPE},
    {std::hash<std::string>{}("float128"),FLOAT128_TYPE}
};

bool Parser::isValidName(const lexToken& token) noexcept
{
    size view = std::hash<std::string>{}(lexer->refSource().substr(token.span.start, std::max<size>(1,token.span.end - token.span.start)));
    for(auto& item:keyword_lookup)
    {
        if(item == view) return false;
    }
    for(auto& item:data_type_lookup)
    {
        if(std::get<0>(item) == view) return false;
    }
    return true;
}

bool Parser::isDataType(const lexToken& token) noexcept
{
    size view = std::hash<std::string>{}(lexer->refSource().substr(token.span.start, std::max<size>(1,token.span.end - token.span.start)));
    for(auto& item:data_type_lookup)
    {
        if(std::get<0>(item) == view) return true;
    }
    return false;
}

ASTDataType Parser::parseDataType(const lexToken& token) noexcept
{
     size view = std::hash<std::string>{}(lexer->refSource().substr(token.span.start, std::max<size>(1,token.span.end - token.span.start)));
     for(auto& item:data_type_lookup)
     {
        if(std::get<0>(item) == view) return std::get<1>(item);
     }
     return NOT_DETERMINED_TYPE;
}

bool Parser::isInteger(const lexToken& token) noexcept
{
    std::string s = lexer->refSource().substr(token.span.start, std::max<size>(1,token.span.end - token.span.start));
    return std::all_of(s.begin(), s.end(),[](const int8 c) {return std::isdigit(c);});
}

void Parser::warn(const lexToken& tok,const char* msg_text) noexcept
{
    writer->StartObject();
    writer->Key("Type");
    writer->String("warning");
    writer->Key("Msg");
    writer->String(msg_text);
    writer->Key("Line");
    writer->Int64(tok.line);
    writer->Key("GlmSpan");
    writer->StartArray();
    writer->Int64(tok.span.start);
    writer->Int64(tok.span.end);
    writer->EndArray();
    writer->EndObject();
}

void Parser::error(const lexToken& tok,const char* msg_text) noexcept
{
    writer->StartObject();
    writer->Key("Type");
    writer->String("error");
    writer->Key("Msg");
    writer->String(msg_text);
    writer->Key("Line");
    writer->Int64(tok.line);
    writer->Key("GlmSpan");
    writer->StartArray();
    writer->Int64(tok.span.start);
    writer->Int64(tok.span.end);
    writer->EndArray();
    writer->EndObject();
    has_error = true;
}

ASTLiteral* Parser::parseLiteral() noexcept
{
    ASTLiteral* literal = new ASTLiteral();
    lexToken& current_token = lexer->getNextToken();
    if(current_token != T_QUOTE)
    {
        if(!isInteger(current_token))
            error(current_token,"this is not a valid numeric value");
        literal->value = std::move(lexer->refSource().substr(current_token.span.start, std::max<size>(1,current_token.span.end - current_token.span.start)));
        if(lexer->peekNextToken() == T_DOT)
        {
            lexer->skipNextToken();
            current_token = lexer->getNextToken();
            if(!isInteger(current_token))
                error(current_token,"this is not a valid numeric value");
            literal->value += '.';
            literal->value += std::move(lexer->refSource().substr(current_token.span.start, std::max<size>(1,current_token.span.end - current_token.span.start)));
        }
        else if(literal->data_type == FLOAT32_TYPE || literal->data_type == FLOAT64_TYPE || literal->data_type == FLOAT128_TYPE)
        {
            literal->value += ".0";
        }
    }
    else error(current_token,"we don't have string support yet");
    return std::move(literal);
}

const ASTExpression* Parser::parseVar(lexToken* current_token) noexcept
{
    ASTExpression* node = new ASTExpression();
    node->type = ASTE_VAR_DEFINED;
    ASTLiteral* literal;
    ASTDataType data_type = parseDataType(*current_token);

    if(!isValidName(*current_token = lexer->getNextToken()))
        error((*current_token),"this is not a valid param name");

    node->extra_data = std::move(lexer->refSource().substr((*current_token).span.start, std::max<size>(1,(*current_token).span.end - (*current_token).span.start)));

    if(lexer->peekNextToken() != T_EQUAL)
    {
        literal = new ASTLiteral();
        literal->data_type = data_type;
        if(literal->data_type >= 2 && literal->data_type <= 11)
            literal->value = "0";
        else if(literal->data_type >= 12 && literal->data_type <= 14)
            literal->value = "0.0";
        else literal->value = "";
    }
    else
    {
        lexer->skipNextToken();
        literal = std::move(parseLiteral());
        literal->data_type = data_type;
    }
    node->list.emplace_back(std::move(literal));
    return std::move(node);
}

const ASTExpression* Parser::parseArgs() noexcept
{
    ASTExpression* expression = new ASTExpression();
    expression->type = ASTE_PRAM_LIST;
    lexToken& current_token = lexer->getNextToken();
    while ((current_token = lexer->getNextToken()) != T_R_CURLY)
    {
        if(!isDataType(current_token))
            error(current_token,"this is not a supported data type");
        
        ASTLiteral* literal = new ASTLiteral();
        literal->data_type = std::move(parseDataType(current_token));

        if(!isValidName((current_token = lexer->getNextToken())))
            error(current_token,"this is not a valid param name");

        literal->value = lexer->refSource().substr(current_token.span.start, std::max<size>(1,current_token.span.end - current_token.span.start));

        expression->list.emplace_back(std::move(literal));

        if(lexer->peekNextToken() != T_COMMA) lexer->skipNextToken();
    }
    return std::move(expression);
}

const ASTBlock* Parser::parseBlock() noexcept
{
    ASTBlock* block = new ASTBlock();
    lexToken& current_token = lexer->getNextToken();
    while ((current_token = lexer->getNextToken()) != T_R_SQUIGGLY)
    {
        if(current_token == T_RET)
        {
            ASTExpression* node = new ASTExpression();
            node->type = ASTE_RETURN;
            if(isInteger(lexer->peekNextToken()))
                node->list.emplace_back(std::move(parseLiteral()));
            else error(lexer->peekNextToken(), "unsupported return expression data");
            block->list.emplace_back(std::move(node));
        }
        else if (isDataType(current_token))
            block->list.emplace_back(std::move(parseVar(&current_token)));
    }
    if(current_token == T_R_SQUIGGLY) lexer->skipNextToken();
    return std::move(block);
}

const ASTNode* Parser::parse() noexcept
{
    ASTRoot* root = new ASTRoot();
    while(lexer->eot())
    {
        lexToken& current_token = lexer->getNextToken();
        if(current_token == T_FUNC)
        {
            if(!isValidName(lexer->peekNextToken()))
                error(lexer->peekNextToken(),"this is not a valid function name");
            ASTFuncDef* node = new ASTFuncDef(lexer->getNextToken().extra_data);
            if(lexer->peekNextToken() != T_L_CURLY)
                error(lexer->peekNextToken(),"this is not a valid function args opener");
            node->args = std::move(parseArgs());
            if(lexer->peekNextToken() != T_SUB && lexer->peekNextToken(1) != T_L_ARROW)
            {
                warn(lexer->peekNextToken(), "no return type provided default to void");
                node->return_type = VOID_TYPE;
            }
            else
            {
                lexer->skipNextToken();
                lexer->skipNextToken();
                current_token = lexer->getNextToken();
                if(!isDataType(current_token))
                    error(current_token,"this is not a supported data type");
                node->return_type = std::move(parseDataType(current_token));
            }
            if(lexer->peekNextToken() != T_L_SQUIGGLY)
                error(lexer->peekNextToken(),"this is not a valid function block opener");
            node->body = std::move(parseBlock());
            root->children.emplace_back(std::move(node));
        }
        else if (isDataType(current_token))
            root->children.emplace_back(std::move(parseVar(&current_token)));
        else error(current_token,"this is not a valid in this scope");
    }
    return std::move(root);
}

