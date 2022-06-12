#include <string>
#include <vector>

typedef enum TokenKey : uint8_t
{
    WORD_KEY = 0x01,
    NUMBER_KEY = 0x02,
    KEYWORD_KEY = 0x03,
    OP_KEY = 0x04,
    STR_KEY = 0x05,
    NAMESPACE_KEY = 0x06,
} TokenKey;

struct Token
{
    TokenKey key;
    std::string value;

    Token(){};
    Token(TokenKey key, std::string value): key(key), value(value){};
};

const std::vector<Token> lex(std::string&) noexcept;
void lexCheck(const std::vector<Token>&) noexcept;