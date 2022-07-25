#include "Parser.h"
#include <lstd/LookUpTable.h>
#include <lstd/Util.h>

const data_size keyword_lookup[] = 
{
    lstd::hash<lstd::string>{}("func"),
    lstd::hash<lstd::string>{}("ret"),
    lstd::hash<lstd::string>{}("and"),
    lstd::hash<lstd::string>{}("or")
};

const lstd::ReadOnlyLookupTable<data_size, ASTDataType> data_type_lookup = {
    {lstd::hash<lstd::string>{}("uint8"),UINT8_TYPE},
    {lstd::hash<lstd::string>{}("uint16"),UINT16_TYPE},
    {lstd::hash<lstd::string>{}("uint32"),UINT32_TYPE},
    {lstd::hash<lstd::string>{}("uint64"),UINT64_TYPE},
    {lstd::hash<lstd::string>{}("int8"),INT8_TYPE},
    {lstd::hash<lstd::string>{}("int16"),INT16_TYPE},
    {lstd::hash<lstd::string>{}("int32"),INT32_TYPE},
    {lstd::hash<lstd::string>{}("int64"),INT64_TYPE},
    {lstd::hash<lstd::string>{}("float32"),FLOAT32_TYPE},
    {lstd::hash<lstd::string>{}("float64"),FLOAT64_TYPE},
};

bool Parser::isValidName(const lexToken& token) noexcept
{
    data_size view = lstd::hash<lstd::string>{}(
        lexer->refSource().substr(token.span.start, lstd::max<data_size>(1, token.span.end - token.span.start)));
    for(auto& item:keyword_lookup)
    {
        if(item == view) return false;
    }
    for(auto& item:data_type_lookup)
    {
        if(item == view) return false;
    }
    return true;
}

bool Parser::isDataType(const lexToken& token) noexcept
{
    data_size view = lstd::hash<lstd::string>{}(
        lexer->refSource().substr(token.span.start, lstd::max<data_size>(1, token.span.end - token.span.start)));
    for(auto& item:data_type_lookup)
    {
        if(item == view) return true;
    }
    return false;
}

ASTDataType Parser::parseDataType(const lexToken& token) noexcept
{
    data_size view = lstd::hash<lstd::string>{}(
        lexer->refSource().substr(token.span.start, lstd::max<data_size>(1, token.span.end - token.span.start)));
     for(auto& item:data_type_lookup)
     {
        if(item == view) return item.value;
     }
     return NOT_DETERMINED_TYPE;
}

bool Parser::isInteger(const lexToken& token) noexcept
{
    lstd::string str =  lexer->refSource().substr(token.span.start, lstd::max<data_size>(1, token.span.end - token.span.start));
    bool found = false;
    for (const char l :str)
        if (!std::isdigit(l))
            found = true;
    return !found;
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
        literal->value = lexer->refSource().substr(current_token.span.start, lstd::max<data_size>(1,current_token.span.end - current_token.span.start));
        if(lexer->peekNextToken() == T_DOT)
        {
            lexer->skipNextToken();
            current_token = lexer->getNextToken();
            if(!isInteger(current_token))
                error(current_token,"this is not a valid numeric value");
            literal->value += '.';
            literal->value += lexer->refSource().substr(
                current_token.span.start, lstd::max<data_size>(1, current_token.span.end - current_token.span.start));
        }
        else if(literal->data_type == FLOAT32_TYPE || literal->data_type == FLOAT64_TYPE)
        {
            literal->value += ".0";
        }
    }
    else error(current_token,"we don't have string support yet");
    return lstd::move(literal);
}

const ASTExpression* Parser::parseVar(lexToken* current_token) noexcept
{
    ASTExpression* node = new ASTExpression();
    node->type = ASTE_VAR_DEFINED;
    ASTLiteral* literal;
    ASTDataType data_type = parseDataType(*current_token);

    if(!isValidName(*current_token = lexer->getNextToken()))
        error((*current_token),"this is not a valid param name");

    node->extra_data = lexer->refSource().substr((*current_token).span.start, lstd::max<data_size>(1, (*current_token).span.end - (*current_token).span.start));

    if(lexer->peekNextToken() != T_EQUAL)
    {
        literal = new ASTLiteral();
        literal->data_type = data_type;
        if(literal->data_type >= INT8_TYPE && literal->data_type <= UINT64_TYPE)
            literal->value = "0";
        else if(literal->data_type >= FLOAT32_TYPE && literal->data_type <= FLOAT64_TYPE)
            literal->value = "0.0";
        else literal->value = "";
    }
    else
    {
        lexer->skipNextToken();
        literal = parseLiteral();
        literal->data_type = data_type;
    }
    node->list.emplace_back(lstd::move(literal));
    return lstd::move(node);
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
        literal->data_type =parseDataType(current_token);

        if(!isValidName((current_token = lexer->getNextToken())))
            error(current_token,"this is not a valid param name");

        literal->value = lexer->refSource().substr(current_token.span.start, lstd::max<data_size>(1,current_token.span.end - current_token.span.start));

        expression->list.emplace_back(lstd::move(literal));

        if(lexer->peekNextToken() != T_COMMA) lexer->skipNextToken();
    }
    return lstd::move(expression);
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
                node->list.emplace_back(parseLiteral());
            else error(lexer->peekNextToken(), "unsupported return expression data");
            block->list.emplace_back(lstd::move(node));
        }
        else if (isDataType(current_token))
            block->list.emplace_back(parseVar(&current_token));
    }
    if(current_token == T_R_SQUIGGLY) lexer->skipNextToken();
    return lstd::move(block);
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
            node->args = parseArgs();
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
                node->return_type = parseDataType(current_token);
            }
            if(lexer->peekNextToken() != T_L_SQUIGGLY)
                error(lexer->peekNextToken(),"this is not a valid function block opener");
            node->body = parseBlock();
            root->children.emplace_back(lstd::move(node));
        }
        else if (isDataType(current_token))
            root->children.emplace_back(parseVar(&current_token));
        else error(current_token,"this is not a valid in this scope");
    }
    return lstd::move(root);
}

