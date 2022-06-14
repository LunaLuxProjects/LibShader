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
    while(eof())
    {
        if(_break(source[(index++) + 1]))
            break;
    }
    lex.line = line;
    lex.end = index;
    return std::move(lex);   
}