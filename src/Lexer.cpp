#include "Lexer.h"
#include <cstring>

bool LexStateMachine::isOp(const char& c) noexcept
{
    switch(c)
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
        case '>':
        case '<':
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
        case '^':
        case ':':
        case '#':
        case '.': {
            current_state = State::OP_MODE;
            did_state_change = true;
            return true;
        }
        default: 
            return false;
    }
}
bool LexStateMachine::isWhitespace(const char& c) noexcept
{
    switch(c)
    {
        case ' ':
        case '\n':
        case '\r':
        case '\t': {
            current_state = State::WHITESPACE_MODE;
            did_state_change = true;
            return true;
        }
        default: return false;
    }
}

void LexStateMachine::handleState(const char& c) noexcept
{
    did_state_change = false;
    if(c == '\n' && current_state != State::STRING_MODE)
        line++;
    switch (current_state)
    {
        case State::LETTER_MODE: {
            if(isOp(c))
                return;
            if(isWhitespace(c))
                return;
            if(std::isdigit(c))
            {
                current_state = State::NUMBER_MODE;
                did_state_change = true;
                return;
            }
            if(c == '\"' || c == '\'')
            {
                current_state = State::STRING_MODE;
                did_state_change = true;
                return;
            }
            return;
        }
        case State::STRING_MODE: {
            if(c == '\"' || c == '\'')
            {
                current_state = State::LETTER_MODE;
                did_state_change = true;
                return;
            }
            return;
        }
        case State::OP_MODE: {
            if(isWhitespace(c))
                return;
            if(std::isalpha(c))
            {
                current_state = State::LETTER_MODE;
                did_state_change = true;
                return;
            }
            if(std::isdigit(c))
            {
                current_state = State::NUMBER_MODE;
                did_state_change = true;
                return;
            }
            if(c == '\"' || c == '\'')
            {
                current_state = State::STRING_MODE;
                did_state_change = true;
                return;
            }
            return;
        }
        case State::NUMBER_MODE: {
            if(isWhitespace(c))
                return;
            if(isOp(c))
                return;
            if(std::isalpha(c))
            {
                current_state = State::LETTER_MODE;
                did_state_change = true;
                return;
            }
            if(c == '\"' || c == '\'')
            {
                current_state = State::STRING_MODE;
                did_state_change = true;
                return;
            }
            return;
        }
        case State::WHITESPACE_MODE: {
            if(isOp(c))
                return;
            if(std::isdigit(c))
            {
                current_state = State::NUMBER_MODE;
                did_state_change = true;
                return;
            }
            if(std::isalpha(c))
            {
                current_state = State::LETTER_MODE;
                did_state_change = true;
                return;
            }
            if(c == '\"' || c == '\'')
            {
                current_state = State::STRING_MODE;
                did_state_change = true;
                return;
            }
        }
    }
}

const bool LexStateMachine::_break(const char& next_c) noexcept 
{ 
    switch (current_state)
    {
    case State::LETTER_MODE: {
        handleState(next_c);
        if(did_state_change)
            return true;
        return false;
    }
    case State::STRING_MODE: {
        handleState(next_c);
        return false;
    }
    case State::OP_MODE: {
        handleState(next_c);
        return true;
    }
    case State::NUMBER_MODE: {
        handleState(next_c);
        if(did_state_change)
            return true;
        return false;
    }
    case State::WHITESPACE_MODE: {
        handleState(next_c);
        return true;
    }
    default: return false;
    }
}

const Lex LexStateMachine::getLexWord()
{
    Lex lex;
    lex.start = index;
    [[unlikely]]if(index == 0)
        (void)_break(source[0]);

    while(index < source_size)
    {
        if(_break(source[std::min<uint64>((source_size - 1),(index++) + 1)]))
            break;
    }
    lex.line = line;
    lex.end = index;
    if(getSubString(lex.start, lex.end) == " ")
        lex = getLexWord();
    return std::move(lex);   
}

const std::string_view LexStateMachine::getSubString(const uint64 start, const uint64 end) noexcept
{
    return source.substr(start, std::max<const uint64>(end - start,1));
}

const std::string LexStateMachine::getSubRealString(const uint64 start,const uint64 end) noexcept
{
    std::string result;
    size true_size =  std::max<uint64>(end - start,1) + start;
    for(size i = start; i < true_size; i++) 
        result += source.at(i);
    return std::move(result);
}