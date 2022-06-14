#include <string_view>
#include <LibShader.h>



struct Lex
{
    uint64 line = 0;
    uint64 start = 0;
    uint64 end = 0;
};

class LexStateMachine
{
    enum class State
    {
        LETTER_MODE,
        STRING_MODE,
        OP_MODE,
        NUMBER_MODE,
        WHITESPACE_MODE,
    };

    State current_state = State::LETTER_MODE;
    std::string_view source;
    uint64 index = 0;
    uint64 line = 1;
    bool did_state_change = false;

    inline const bool _break(const char&) noexcept;
    inline bool isOp(const char&) noexcept;
    inline bool isWhitespace(const char&) noexcept;
    void handleState(const char&) noexcept;

    public:
    explicit LexStateMachine(std::string_view source_in) : source(std::move(source_in)) {};
    inline bool eof() const noexcept { return (index + 1) < source.length();}
    const Lex getLexWord();
};