#include "Lexer.h"
#include <iostream>
#include <future>
#include <ranges>
#include <stdio.h>


const std::string keywords[] = {"void","int8","int16","int32","int64","int128","uint8","uint16","uint32","uint64","uint128","string","func","ret","input","output","import","public","for","while","if","elif"};

void split(const std::string & original, char separator, std::vector<std::string> * results )
{
    std::string::const_iterator start = original.begin();
    std::string::const_iterator end = original.end();
    std::string::const_iterator next = std::find( start, end, separator );
    while ( next != end ) 
    {
        results->push_back( std::string( start, next ) );
        start = next + 1;
        next = std::find( start, end, separator );
    }
    results->push_back( std::string( start, next ) );
}

inline const bool isOp(const std::string & str) noexcept
{
    if( str.size() > 2)
        return false;

    switch(str[0])
    {
        case '|':
        case '<':
        case '>':
        case '.':
        case '&':
        case '%':
        case '*':
        case '/':
        case '+':
        case '-':
        case '=':
            return true;
        default:
            return false;
    }
}

inline const bool isKeyword(const std::string & str) noexcept
{
    for(auto& keyword: keywords)
    {
        if(keyword == str)
            return true;
    }
    return false;
}

inline const bool canBeSingle(const char letter) noexcept
{
    switch(letter)
    {
        case '&':
        case '!':
        case '(':
        case ')':
        case '{':
        case '}':
        case '[':
        case ']':
        case ';':
        case ',':
        case '\"':
        case '\'':
        case '\\':
            return true;
        default:
            return false;
    }
}

Token lexToken(const std::string& str) noexcept
{
    TokenKey key;
    if(isKeyword(str))
    {
        key = KEYWORD_KEY;
        goto done;
    }
    else if(std::all_of(str.begin(), str.end(),[](char c){ return std::isdigit(c) != 0; }))
    {
        key = NUMBER_KEY;
        goto done;
    }
    else if(isOp(str))
    {
         key = OP_KEY;
         goto done;
    }
    else if(str[0] == '\"')
    {
        key = STR_KEY;
        goto done;
    }
    else if(str == "::")
    {
        key = NAMESPACE_KEY;
        goto done;
    }
    else
    {
         key = WORD_KEY;
         goto done;
    }
    done:
    
    return Token(key,str);
}

std::string lexLine(const std::string& str) noexcept
{
    std::string result;
    for(size_t i = 0; i < str.size(); i++)
    {
        const char& c = str[i];

        if(std::isspace(c) || std::isalnum(c) || c == '_')
            result += c;
        else
        {
            result += ' ';
            result += c;
            [[unlikely]]if(!std::isspace(str[i + 1]) && !std::isalnum(str[i + 1]) && !canBeSingle(str[i + 1]))
                result += str[++i];
            result += ' ';
        }
    }
    return result;
}

const std::vector<Token> lex(std::string& source)
{
    std::vector<Token> result;
    std::vector<std::string> lines;
    split(source, '\n',&lines);

    std::vector<std::string> words;
    {
        std::vector<std::future<std::string>> fixed_lines;

        for (auto line : lines)
            fixed_lines.emplace_back(std::async(lexLine, std::move(line)));

        for (auto& fixed_line : fixed_lines)
        {
            std::vector<std::string> words_;
            split(fixed_line.get(), ' ',&words_);
            std::string result;
            bool inQuote = false,special = false;
            for (auto& word : words_)
            {
                if(word[0] == '\\')
                {
                    std::cout << word << std::endl;
                    special = true;
                }

                if(word[0] == '"')
                {
                    if(!special)
                    {
                        if(inQuote)
                        {
                            result = result.substr(0,result.size() - 1);
                            if(result[0] == ' ')
                                result = result.substr(1,result.size());
                        }
                        inQuote = !inQuote;
                    }
                    
                }
                
                if(word[0] != ';')
                    result += word;
                
                if(inQuote && !special)
                    result += ' ';
                
                if(word[0] == '"')
                    special = false;
                
                if(!inQuote && !special)
                {
                    words.emplace_back(result);
                    result.clear();
                }
            }
        }
    }

    std::vector<std::future<Token>> tokens;

    for (auto& word : words)
    {
        if (!word.empty())
            tokens.emplace_back(std::async(lexToken, word));
    }

    for (auto& f_result : tokens)
    {
        f_result.wait();
        result.emplace_back(f_result.get());
    }
    return result;
}

void lexCheck(const std::vector<Token>& tokens) noexcept
{
    for(size_t i = 0; i < tokens.size(); i++)
    {
        if((tokens[i].key == KEYWORD_KEY) && (tokens[i + 1].key == KEYWORD_KEY))
        {
            std::cerr << "ERROR: tried using: \"" << tokens[i + 1].value << "\" as a declaration for - " << tokens[i].value << std::endl;
            std::exit(1);
        }
    }
}