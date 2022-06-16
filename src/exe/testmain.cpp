#include <gtest/gtest.h>
#include <LibShader.h>

TEST(AST,PARSE_MAIN)
{
    std::string source = "func main() -> int32 { ret 0}";
    const char* result =  "{\"type\":\"Program\",\"body\":[{\"type\":\"FunctionDef\",\"id\":\"main\",\"return_type\":\"int32\",\"parameters\":[],"
                        "\"body\":[{\"type\":\"Expression\",\"id\":\"ReturnType\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"IntegerLiteral\",\"value\""
                        ":\"0\"}]}]}],\"SourceType\":\"module\"}";
    auto data = compileToAST(std::vector<std::string>(),source);
    EXPECT_STREQ(data.data_msg.c_str(),result);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

TEST(AST,PARSE_VAR_UINT8_NO_VALUE)
{
    std::string source = "uint8 x";
    const char* result =  "{\"type\":\"Program\",\"body\":[{\"type\":\"Expression\",\"id\":\"VariableDefinition\",\"name\":\"x\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"uint8\",\"value\":\"0\"}]}],\"SourceType\":\"module\"}";
    auto data = compileToAST(std::vector<std::string>(),source);
    EXPECT_STREQ(data.data_msg.c_str(),result);
}

TEST(AST,PARSE_VAR_UINT16_NO_VALUE)
{
    std::string source = "uint16 x";
    const char* result =  "{\"type\":\"Program\",\"body\":[{\"type\":\"Expression\",\"id\":\"VariableDefinition\",\"name\":\"x\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"uint16\",\"value\":\"0\"}]}],\"SourceType\":\"module\"}";
    auto data = compileToAST(std::vector<std::string>(),source);
    EXPECT_STREQ(data.data_msg.c_str(),result);
}

TEST(AST,PARSE_VAR_UINT32_NO_VALUE)
{
    std::string source = "uint32 x";
    const char* result =  "{\"type\":\"Program\",\"body\":[{\"type\":\"Expression\",\"id\":\"VariableDefinition\",\"name\":\"x\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"uint32\",\"value\":\"0\"}]}],\"SourceType\":\"module\"}";
    auto data = compileToAST(std::vector<std::string>(),source);
    EXPECT_STREQ(data.data_msg.c_str(),result);
}

TEST(AST,PARSE_VAR_UINT64_NO_VALUE)
{
    std::string source = "uint64 x";
    const char* result =  "{\"type\":\"Program\",\"body\":[{\"type\":\"Expression\",\"id\":\"VariableDefinition\",\"name\":\"x\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"uint64\",\"value\":\"0\"}]}],\"SourceType\":\"module\"}";
    auto data = compileToAST(std::vector<std::string>(),source);
    EXPECT_STREQ(data.data_msg.c_str(),result);
}

TEST(AST,PARSE_VAR_UINT128_NO_VALUE)
{
    std::string source = "uint128 x";
    const char* result =  "{\"type\":\"Program\",\"body\":[{\"type\":\"Expression\",\"id\":\"VariableDefinition\",\"name\":\"x\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"uint128\",\"value\":\"0\"}]}],\"SourceType\":\"module\"}";
    auto data = compileToAST(std::vector<std::string>(),source);
    EXPECT_STREQ(data.data_msg.c_str(),result);
}

TEST(AST,PARSE_VAR_INT8_NO_VALUE)
{
    std::string source = "int8 x";
    const char* result =  "{\"type\":\"Program\",\"body\":[{\"type\":\"Expression\",\"id\":\"VariableDefinition\",\"name\":\"x\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"int8\",\"value\":\"0\"}]}],\"SourceType\":\"module\"}";
    auto data = compileToAST(std::vector<std::string>(),source);
    EXPECT_STREQ(data.data_msg.c_str(),result);
}

TEST(AST,PARSE_VAR_INT16_NO_VALUE)
{
    std::string source = "int16 x";
    const char* result =  "{\"type\":\"Program\",\"body\":[{\"type\":\"Expression\",\"id\":\"VariableDefinition\",\"name\":\"x\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"int16\",\"value\":\"0\"}]}],\"SourceType\":\"module\"}";
    auto data = compileToAST(std::vector<std::string>(),source);
    EXPECT_STREQ(data.data_msg.c_str(),result);
}

TEST(AST,PARSE_VAR_INT32_NO_VALUE)
{
    std::string source = "int32 x";
    const char* result =  "{\"type\":\"Program\",\"body\":[{\"type\":\"Expression\",\"id\":\"VariableDefinition\",\"name\":\"x\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"int32\",\"value\":\"0\"}]}],\"SourceType\":\"module\"}";
    auto data = compileToAST(std::vector<std::string>(),source);
    EXPECT_STREQ(data.data_msg.c_str(),result);
}

TEST(AST,PARSE_VAR_INT64_NO_VALUE)
{
    std::string source = "int64 x";
    const char* result =  "{\"type\":\"Program\",\"body\":[{\"type\":\"Expression\",\"id\":\"VariableDefinition\",\"name\":\"x\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"int64\",\"value\":\"0\"}]}],\"SourceType\":\"module\"}";
    auto data = compileToAST(std::vector<std::string>(),source);
    EXPECT_STREQ(data.data_msg.c_str(),result);
}

TEST(AST,PARSE_VAR_INT128_NO_VALUE)
{
    std::string source = "int128 x";
    const char* result =  "{\"type\":\"Program\",\"body\":[{\"type\":\"Expression\",\"id\":\"VariableDefinition\",\"name\":\"x\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"int128\",\"value\":\"0\"}]}],\"SourceType\":\"module\"}";
    auto data = compileToAST(std::vector<std::string>(),source);
    EXPECT_FALSE(data.isError);
    EXPECT_STREQ(data.data_msg.c_str(),result);
}


//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
TEST(AST,PARSE_VAR_UINT8_WITH_VALUE)
{
    std::string source = "uint8 x = 20";
    const char* result =  "{\"type\":\"Program\",\"body\":[{\"type\":\"Expression\",\"id\":\"VariableDefinition\",\"name\":\"x\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"uint8\",\"value\":\"20\"}]}],\"SourceType\":\"module\"}";
    auto data = compileToAST(std::vector<std::string>(),source);
    EXPECT_FALSE(data.isError);
    EXPECT_STREQ(data.data_msg.c_str(),result);
}

TEST(AST,PARSE_VAR_UINT16_WITH_VALUE)
{
    std::string source = "uint16 x = 20";
    const char* result =  "{\"type\":\"Program\",\"body\":[{\"type\":\"Expression\",\"id\":\"VariableDefinition\",\"name\":\"x\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"uint16\",\"value\":\"20\"}]}],\"SourceType\":\"module\"}";
    auto data = compileToAST(std::vector<std::string>(),source);
    EXPECT_FALSE(data.isError);
    EXPECT_STREQ(data.data_msg.c_str(),result);
}

TEST(AST,PARSE_VAR_UINT32_WITH_VALUE)
{
    std::string source = "uint32 x = 20";
    const char* result =  "{\"type\":\"Program\",\"body\":[{\"type\":\"Expression\",\"id\":\"VariableDefinition\",\"name\":\"x\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"uint32\",\"value\":\"20\"}]}],\"SourceType\":\"module\"}";
    auto data = compileToAST(std::vector<std::string>(),source);
    EXPECT_FALSE(data.isError);
    EXPECT_STREQ(data.data_msg.c_str(),result);
}

TEST(AST,PARSE_VAR_UINT64_WITH_VALUE)
{
    std::string source = "uint64 x = 20";
    const char* result =  "{\"type\":\"Program\",\"body\":[{\"type\":\"Expression\",\"id\":\"VariableDefinition\",\"name\":\"x\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"uint64\",\"value\":\"20\"}]}],\"SourceType\":\"module\"}";
    auto data = compileToAST(std::vector<std::string>(),source);
    EXPECT_FALSE(data.isError);
    EXPECT_STREQ(data.data_msg.c_str(),result);
}

TEST(AST,PARSE_VAR_UINT128_WITH_VALUE)
{
    std::string source = "uint128 x = 20";
    const char* result =  "{\"type\":\"Program\",\"body\":[{\"type\":\"Expression\",\"id\":\"VariableDefinition\",\"name\":\"x\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"uint128\",\"value\":\"20\"}]}],\"SourceType\":\"module\"}";
    auto data = compileToAST(std::vector<std::string>(),source);
    EXPECT_FALSE(data.isError);
    EXPECT_STREQ(data.data_msg.c_str(),result);
}

TEST(AST,PARSE_VAR_INT8_WITH_VALUE)
{
    std::string source = "int8 x = 20";
    const char* result =  "{\"type\":\"Program\",\"body\":[{\"type\":\"Expression\",\"id\":\"VariableDefinition\",\"name\":\"x\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"int8\",\"value\":\"20\"}]}],\"SourceType\":\"module\"}";
    auto data = compileToAST(std::vector<std::string>(),source);
    EXPECT_FALSE(data.isError);
    EXPECT_STREQ(data.data_msg.c_str(),result);
}

TEST(AST,PARSE_VAR_INT16_WITH_VALUE)
{
    std::string source = "int16 x = 20";
    const char* result =  "{\"type\":\"Program\",\"body\":[{\"type\":\"Expression\",\"id\":\"VariableDefinition\",\"name\":\"x\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"int16\",\"value\":\"20\"}]}],\"SourceType\":\"module\"}";
    auto data = compileToAST(std::vector<std::string>(),source);
    EXPECT_FALSE(data.isError);
    EXPECT_STREQ(data.data_msg.c_str(),result);
}

TEST(AST,PARSE_VAR_INT32_WITH_VALUE)
{
    std::string source = "int32 x = 20";
    const char* result =  "{\"type\":\"Program\",\"body\":[{\"type\":\"Expression\",\"id\":\"VariableDefinition\",\"name\":\"x\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"int32\",\"value\":\"20\"}]}],\"SourceType\":\"module\"}";
    auto data = compileToAST(std::vector<std::string>(),source);
    EXPECT_FALSE(data.isError);
    EXPECT_STREQ(data.data_msg.c_str(),result);
}

TEST(AST,PARSE_VAR_INT64_WITH_VALUE)
{
    std::string source = "int64 x = 20";
    const char* result =  "{\"type\":\"Program\",\"body\":[{\"type\":\"Expression\",\"id\":\"VariableDefinition\",\"name\":\"x\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"int64\",\"value\":\"20\"}]}],\"SourceType\":\"module\"}";
    auto data = compileToAST(std::vector<std::string>(),source);
    EXPECT_FALSE(data.isError);
    EXPECT_STREQ(data.data_msg.c_str(),result);
}

TEST(AST,PARSE_VAR_INT128_WITH_VALUE)
{
    std::string source = "int128 x = 20";
    const char* result =  "{\"type\":\"Program\",\"body\":[{\"type\":\"Expression\",\"id\":\"VariableDefinition\",\"name\":\"x\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"int128\",\"value\":\"20\"}]}],\"SourceType\":\"module\"}";
    auto data = compileToAST(std::vector<std::string>(),source);
    EXPECT_FALSE(data.isError);
    EXPECT_STREQ(data.data_msg.c_str(),result);
}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}