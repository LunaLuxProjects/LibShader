#include "Parser.h"
#include <iostream>
#include <string_view>
#include <cstddef>
#include <algorithm>
#include <unordered_map>

const uint64 keywords_lookup[] = 
{
    std::hash<std::string_view>{}("func"),
    std::hash<std::string_view>{}("ret"),
    std::hash<std::string_view>{}("void"),
    std::hash<std::string_view>{}("int8"),
    std::hash<std::string_view>{}("int16"),
    std::hash<std::string_view>{}("int32"),
    std::hash<std::string_view>{}("int64"),
    std::hash<std::string_view>{}("int128"),
    std::hash<std::string_view>{}("uint8"),
    std::hash<std::string_view>{}("uint16"),
    std::hash<std::string_view>{}("uint32"),
    std::hash<std::string_view>{}("uint64"),
    std::hash<std::string_view>{}("uint128"),
    std::hash<std::string_view>{}("float32"),
    std::hash<std::string_view>{}("float64"),
    std::hash<std::string_view>{}("float128"),
    std::hash<std::string_view>{}("string"),
    std::hash<std::string_view>{}("for"),
    std::hash<std::string_view>{}("while"),
    std::hash<std::string_view>{}("if"),
    std::hash<std::string_view>{}("elif"),
};

[[noreturn]]void Parser::error(const char *message) noexcept
{
    std::cerr << "Error: " << message << std::endl;
    std::cerr << "At Lex Index: (" << word_data.start << "," << word_data.end << ")" << std::endl;
    std::cerr << "Word: " << lexer->getSubString(word_data.start, word_data.end) << std::endl;
    std::cerr << "Or Line: " << word_data.line << std::endl;
    std::abort();
}

[[nodiscard]]const bool Parser::isKeyword(const std::string_view word) noexcept
{
    auto hash = std::hash<std::string_view>{}(word);
    for(const auto& item: keywords_lookup)
    {
        if(hash == item) 
            return true;
    }
    return false;
}

[[nodiscard]]const ASTDataType Parser::getFromHash(const size hash) noexcept
{
    if(hash == keywords_lookup[2]) return VOID_TYPE;
    else if(hash == keywords_lookup[3]) return INT8_TYPE;
    else if(hash == keywords_lookup[4]) return INT16_TYPE;
    else if(hash == keywords_lookup[5]) return INT32_TYPE;
    else if(hash == keywords_lookup[6]) return INT64_TYPE;
    else if(hash == keywords_lookup[7]) return INT128_TYPE;
    else if(hash == keywords_lookup[8]) return UINT8_TYPE;
    else if(hash == keywords_lookup[9]) return UINT16_TYPE;
    else if(hash == keywords_lookup[10]) return UINT32_TYPE;
    else if(hash == keywords_lookup[11]) return UINT64_TYPE;
    else if(hash == keywords_lookup[12]) return UINT128_TYPE;
    else if(hash == keywords_lookup[13]) return FLOAT32_TYPE;
    else if(hash == keywords_lookup[14]) return FLOAT64_TYPE;
    else if(hash == keywords_lookup[15]) return FLOAT128_TYPE;
    else if(hash == keywords_lookup[16]) return STR_TYPE;
    else error("invalid type");
}

[[nodiscard]]const ASTDataType Parser::getTypeID() noexcept
{   
    return getFromHash(getHash(getNextWord()));
}

[[nodiscard]]const bool Parser::isNumber() noexcept
{
    std::string s = lexer->getSubRealString(word_data.start, word_data.end);
    return std::all_of(s.begin(), s.end(),[](char c){ return isdigit(c) || c == '.'; });
}

[[nodiscard]]const size Parser::getHash(std::string_view word) noexcept
{
    size hash = 0;
    if(word == "uint" || word == "int" || word == "float")
    {
        std::string str = lexer->getSubRealString(word_data.start, word_data.end);
        std::string_view number = getNextWord();
        str += lexer->getSubRealString(word_data.start, word_data.end);
        hash = std::hash<std::string>{}(str);
    }
    else hash = std::hash<std::string_view>{}(word);
    return hash;
}

const std::string_view Parser::getNextWord(bool ignore_newline) noexcept
{
    if(hold && held_lex.line != 0)
    {
        std::string_view str = lexer->getSubString(held_lex.start, held_lex.end);
        hold = false;
        held_lex.line = 0;
        return str;
    }

    Lex lex = lexer->getLexWord();
    if(!ignore_newline)
    {
        word_data = lex;
        Lex temp;
        std::string_view str = lexer->getSubString(lex.start, lex.end);
        
        while((str = lexer->getSubString(lex.start, lex.end)) != "\n")
        {
            if(temp.end == lex.end || str == "}")
            {
                hold = true;
                break;
            }
            temp = lex;
            lex = lexer->getLexWord();
        }
        if(hold)
            held_lex = lex;

        word_data.end = temp.end;
    } else word_data = lex;
    std::string_view result = lexer->getSubString(word_data.start, word_data.end);
    if(result == ";" || result == "\n")
        return getNextWord(ignore_newline);
    return result;
}

[[nodiscard]]const bool Parser::isValidName() noexcept
{
    std::string s = lexer->getSubRealString(word_data.start, word_data.end);
    return std::none_of(s.begin(),s.end(),[](char c){ return isalpha(c) || c == '_'; });
}

[[nodiscard]]const std::vector<const ASTNode *> Parser::parseArgs()
{
    std::vector<const ASTNode *> args;

    std::string_view word;
    while((word = getNextWord()) != ")")
    {
        error("todo args parsing");
    }

    return std::move(args);   
}

[[nodiscard]]const std::vector<const ASTNode *> Parser::parseBlock()
{
    std::vector<const ASTNode *> block;

    std::string_view word;
    while((word = getNextWord()) != "}")
    {
        auto hash = getHash(word);

        if(hash == keywords_lookup[1])
        {
            auto* node = new ASTExpression();
            node->type = ASTE_RETURN;
            word = getNextWord(false);
            auto* sub_node = new ASTLiteral();
            if(isNumber())
            {
                if(word.find('.') == std::string::npos)
                    sub_node->type = INT_TYPE;
                else
                   sub_node->type = FLOAT_TYPE;
            }
            else sub_node->type = VAR_TYPE;
            sub_node->value = std::move(lexer->getSubRealString(word_data.start, word_data.end));
            node->list.emplace_back(std::move(sub_node));
            block.emplace_back(std::move(node));
        }
    }

    return std::move(block);   
}

const ASTNode* Parser::parse() noexcept
{
    ASTRoot* root = new ASTRoot();
    bool save_word = false;
    std::string_view word;
    while(lexer->eof())
    {
        if(!save_word)
            word = getNextWord();
        else save_word = false;
        auto hash = getHash(word);

        if(isKeyword(word))
        {
            if(hash == keywords_lookup[0])
            {
                auto name = getNextWord();
                if(isKeyword(name))
                    error("tried to use a keyword as a function name");
                if(isValidName())
                    error(std::string("the name of function '" + lexer->getSubRealString(word_data.start,word_data.end) + "' is not a valid name").c_str());
                auto* node = new ASTFuncDef(std::move(lexer->getSubRealString(word_data.start, word_data.end)));
                if(getNextWord() != "(")
                    error("missing syntax for function args");
                node->args = std::move(parseArgs());
                auto returner = getNextWord();
                auto returner2 = getNextWord();
                if(returner != "-" || returner2 != ">")
                    error("missing syntax for function return value");
                node->return_type = getTypeID();
                if(getNextWord() != "{")
                    error("missing syntax for function args");
                node->body = std::move(parseBlock());
                root->children.emplace_back(std::move(node));
            }
    
            else error("unexpected keyword");
        }
        else if(hash == keywords_lookup[2] || hash == keywords_lookup[3] || hash == keywords_lookup[4] || 
                hash == keywords_lookup[5] || hash == keywords_lookup[6] || hash == keywords_lookup[7] ||
                hash == keywords_lookup[8] || hash == keywords_lookup[9] || hash == keywords_lookup[10]||
                hash == keywords_lookup[11]|| hash == keywords_lookup[12]|| hash == keywords_lookup[13]|| 
                hash == keywords_lookup[14]|| hash == keywords_lookup[15]|| hash == keywords_lookup[16])
        {
            ASTExpression* node = new ASTExpression();
            node->type = ASTE_VAR_DEFINED;
            auto name = getNextWord();
            if(isKeyword(name))
                error("tried to use a keyword as a variable name");
            if(isValidName())
                error(std::string("the name of variable '" + lexer->getSubRealString(word_data.start,word_data.end) + "' is not a valid name").c_str());
            node->name = std::move(lexer->getSubRealString(word_data.start, word_data.end));
            word = getNextWord();
            if(word != "=")
            {
                save_word = true;
                auto* sub_node = new ASTLiteral();
                sub_node->data_type = getFromHash(hash);
                switch (sub_node->data_type)
                {
                    case VOID_TYPE:{
                        error("tried to use void for variable this type is only allowed as a function return type");
                    }
                    case INT8_TYPE:
                    case INT16_TYPE:
                    case INT32_TYPE:
                    case INT64_TYPE:
                    case INT128_TYPE:
                    case UINT8_TYPE:
                    case UINT16_TYPE:
                    case UINT32_TYPE:
                    case UINT64_TYPE:
                    case UINT128_TYPE: {
                        sub_node->value = "0";
                        break;
                    }
                    case FLOAT32_TYPE:
                    case FLOAT64_TYPE:
                    case FLOAT128_TYPE: {
                        sub_node->value = "0.0";
                        break;
                    }
                default:
                    error("used a type supported by the language");
                }
                node->list.emplace_back(std::move(sub_node));
            }
            else if(word == "=")
            {
                auto* sub_node = new ASTLiteral();
                sub_node->data_type = getFromHash(hash);
                getNextWord(false);
                sub_node->value = std::move(lexer->getSubRealString(word_data.start, word_data.end));
                node->list.emplace_back(std::move(sub_node));
            }
            root->children.emplace_back(std::move(node));
        }
        else error("invalid syntax");
    }
    return std::move(root);
}

