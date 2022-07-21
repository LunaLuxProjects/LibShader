#include <gtest/gtest.h>
#include <libshader/Compiler.h>
#include <lstd/Util.h>

// global variables
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

TEST(AST,PARSE_VAR_UINT8_NO_VALUE)
{
    lstd::string source = "uint8 x";
    const char* result =  "{\"type\":\"Program\",\"body\":[{\"type\":\"Expression\",\"id\":\"VariableDefinition\",\"name\":\"x\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"uint8\",\"value\":\"0\"}]}],\"SourceType\":\"module\"}";
    auto data = compileToAST(std::vector<lstd::string>(),lstd::move(source));
    if(data.isError) printf("Compiler Test: %s", data.error_msg.c_str());
    EXPECT_FALSE(data.isError);
    EXPECT_STREQ(data.data_msg.c_str(),result);
}

TEST(AST,PARSE_VAR_UINT16_NO_VALUE)
{
    lstd::string source = "uint16 x";
    const char* result =  "{\"type\":\"Program\",\"body\":[{\"type\":\"Expression\",\"id\":\"VariableDefinition\",\"name\":\"x\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"uint16\",\"value\":\"0\"}]}],\"SourceType\":\"module\"}";
    auto data = compileToAST(std::vector<lstd::string>(),lstd::move(source));
    if(data.isError) printf("Compiler Test: %s", data.error_msg.c_str());
    EXPECT_FALSE(data.isError);
    EXPECT_STREQ(data.data_msg.c_str(),result);
}

TEST(AST,PARSE_VAR_UINT32_NO_VALUE)
{
    lstd::string source = "uint32 x";
    const char* result =  "{\"type\":\"Program\",\"body\":[{\"type\":\"Expression\",\"id\":\"VariableDefinition\",\"name\":\"x\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"uint32\",\"value\":\"0\"}]}],\"SourceType\":\"module\"}";
    auto data = compileToAST(std::vector<lstd::string>(),lstd::move(source));
    if(data.isError) printf("Compiler Test: %s", data.error_msg.c_str());
    EXPECT_FALSE(data.isError);
    EXPECT_STREQ(data.data_msg.c_str(),result);
}

TEST(AST,PARSE_VAR_UINT64_NO_VALUE)
{
    lstd::string source = "uint64 x";
    const char* result =  "{\"type\":\"Program\",\"body\":[{\"type\":\"Expression\",\"id\":\"VariableDefinition\",\"name\":\"x\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"uint64\",\"value\":\"0\"}]}],\"SourceType\":\"module\"}";
    auto data = compileToAST(std::vector<lstd::string>(),lstd::move(source));
    if(data.isError) printf("Compiler Test: %s", data.error_msg.c_str());
    EXPECT_FALSE(data.isError);
    EXPECT_STREQ(data.data_msg.c_str(),result);
}

TEST(AST,PARSE_VAR_INT8_NO_VALUE)
{
    lstd::string source = "int8 x";
    const char* result =  "{\"type\":\"Program\",\"body\":[{\"type\":\"Expression\",\"id\":\"VariableDefinition\",\"name\":\"x\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"int8\",\"value\":\"0\"}]}],\"SourceType\":\"module\"}";
    auto data = compileToAST(std::vector<lstd::string>(),lstd::move(source));
    if(data.isError) printf("Compiler Test: %s", data.error_msg.c_str());
    EXPECT_FALSE(data.isError);
    EXPECT_STREQ(data.data_msg.c_str(),result);
}

TEST(AST,PARSE_VAR_INT16_NO_VALUE)
{
    lstd::string source = "int16 x";
    const char* result =  "{\"type\":\"Program\",\"body\":[{\"type\":\"Expression\",\"id\":\"VariableDefinition\",\"name\":\"x\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"int16\",\"value\":\"0\"}]}],\"SourceType\":\"module\"}";
    auto data = compileToAST(std::vector<lstd::string>(),lstd::move(source));
    if(data.isError) printf("Compiler Test: %s", data.error_msg.c_str());
    EXPECT_FALSE(data.isError);
    EXPECT_STREQ(data.data_msg.c_str(),result);
}

TEST(AST,PARSE_VAR_INT32_NO_VALUE)
{
    lstd::string source = "int32 x";
    const char* result =  "{\"type\":\"Program\",\"body\":[{\"type\":\"Expression\",\"id\":\"VariableDefinition\",\"name\":\"x\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"int32\",\"value\":\"0\"}]}],\"SourceType\":\"module\"}";
    auto data = compileToAST(std::vector<lstd::string>(),lstd::move(source));
    if(data.isError) printf("Compiler Test: %s", data.error_msg.c_str());
    EXPECT_FALSE(data.isError);
    EXPECT_STREQ(data.data_msg.c_str(),result);
}

TEST(AST,PARSE_VAR_INT64_NO_VALUE)
{
    lstd::string source = "int64 x";
    const char* result =  "{\"type\":\"Program\",\"body\":[{\"type\":\"Expression\",\"id\":\"VariableDefinition\",\"name\":\"x\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"int64\",\"value\":\"0\"}]}],\"SourceType\":\"module\"}";
    auto data = compileToAST(std::vector<lstd::string>(),lstd::move(source));
    if(data.isError) printf("Compiler Test: %s", data.error_msg.c_str());
    EXPECT_FALSE(data.isError);
    EXPECT_STREQ(data.data_msg.c_str(),result);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
TEST(AST,PARSE_VAR_UINT8_WITH_VALUE)
{
    lstd::string source = "uint8 x = 20";
    const char* result =  "{\"type\":\"Program\",\"body\":[{\"type\":\"Expression\",\"id\":\"VariableDefinition\",\"name\":\"x\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"uint8\",\"value\":\"20\"}]}],\"SourceType\":\"module\"}";
    auto data = compileToAST(std::vector<lstd::string>(),lstd::move(source));
    if(data.isError) printf("Compiler Test: %s", data.error_msg.c_str());
    EXPECT_FALSE(data.isError);
    EXPECT_STREQ(data.data_msg.c_str(),result);
}

TEST(AST,PARSE_VAR_UINT16_WITH_VALUE)
{
    lstd::string source = "uint16 x = 20";
    const char* result =  "{\"type\":\"Program\",\"body\":[{\"type\":\"Expression\",\"id\":\"VariableDefinition\",\"name\":\"x\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"uint16\",\"value\":\"20\"}]}],\"SourceType\":\"module\"}";
    auto data = compileToAST(std::vector<lstd::string>(),lstd::move(source));
    if(data.isError) printf("Compiler Test: %s", data.error_msg.c_str());
    EXPECT_FALSE(data.isError);
    EXPECT_STREQ(data.data_msg.c_str(),result);
}

TEST(AST,PARSE_VAR_UINT32_WITH_VALUE)
{
    lstd::string source = "uint32 x = 20";
    const char* result =  "{\"type\":\"Program\",\"body\":[{\"type\":\"Expression\",\"id\":\"VariableDefinition\",\"name\":\"x\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"uint32\",\"value\":\"20\"}]}],\"SourceType\":\"module\"}";
    auto data = compileToAST(std::vector<lstd::string>(),lstd::move(source));
    if(data.isError) printf("Compiler Test: %s", data.error_msg.c_str());
    EXPECT_FALSE(data.isError);
    EXPECT_STREQ(data.data_msg.c_str(),result);
}

TEST(AST,PARSE_VAR_UINT64_WITH_VALUE)
{
    lstd::string source = "uint64 x = 20";
    const char* result =  "{\"type\":\"Program\",\"body\":[{\"type\":\"Expression\",\"id\":\"VariableDefinition\",\"name\":\"x\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"uint64\",\"value\":\"20\"}]}],\"SourceType\":\"module\"}";
    auto data = compileToAST(std::vector<lstd::string>(),lstd::move(source));
    if(data.isError) printf("Compiler Test: %s", data.error_msg.c_str());
    EXPECT_FALSE(data.isError);
    EXPECT_STREQ(data.data_msg.c_str(),result);
}

TEST(AST,PARSE_VAR_INT8_WITH_VALUE)
{
    lstd::string source = "int8 x = 20";
    const char* result =  "{\"type\":\"Program\",\"body\":[{\"type\":\"Expression\",\"id\":\"VariableDefinition\",\"name\":\"x\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"int8\",\"value\":\"20\"}]}],\"SourceType\":\"module\"}";
    auto data = compileToAST(std::vector<lstd::string>(),lstd::move(source));
    if(data.isError) printf("Compiler Test: %s", data.error_msg.c_str());
    EXPECT_FALSE(data.isError);
    EXPECT_STREQ(data.data_msg.c_str(),result);
}

TEST(AST,PARSE_VAR_INT16_WITH_VALUE)
{
    lstd::string source = "int16 x = 20";
    const char* result =  "{\"type\":\"Program\",\"body\":[{\"type\":\"Expression\",\"id\":\"VariableDefinition\",\"name\":\"x\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"int16\",\"value\":\"20\"}]}],\"SourceType\":\"module\"}";
    auto data = compileToAST(std::vector<lstd::string>(),lstd::move(source));
    if(data.isError) printf("Compiler Test: %s", data.error_msg.c_str());
    EXPECT_FALSE(data.isError);
    EXPECT_STREQ(data.data_msg.c_str(),result);
}

TEST(AST,PARSE_VAR_INT32_WITH_VALUE)
{
    lstd::string source = "int32 x = 20";
    const char* result =  "{\"type\":\"Program\",\"body\":[{\"type\":\"Expression\",\"id\":\"VariableDefinition\",\"name\":\"x\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"int32\",\"value\":\"20\"}]}],\"SourceType\":\"module\"}";
    auto data = compileToAST(std::vector<lstd::string>(),lstd::move(source));
    if(data.isError) printf("Compiler Test: %s", data.error_msg.c_str());
    EXPECT_FALSE(data.isError);
    EXPECT_STREQ(data.data_msg.c_str(),result);
}

TEST(AST,PARSE_VAR_INT64_WITH_VALUE)
{
    lstd::string source = "int64 x = 20";
    const char* result =  "{\"type\":\"Program\",\"body\":[{\"type\":\"Expression\",\"id\":\"VariableDefinition\",\"name\":\"x\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"int64\",\"value\":\"20\"}]}],\"SourceType\":\"module\"}";
    auto data = compileToAST(std::vector<lstd::string>(),lstd::move(source));
    if(data.isError) printf("Compiler Test: %s", data.error_msg.c_str());
    EXPECT_FALSE(data.isError);
    EXPECT_STREQ(data.data_msg.c_str(),result);
}

// function return tests 
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

TEST(AST,PARSE_MAIN)
{
    lstd::string source = "func main() -> int32 { ret 0}";
    const char* result =    "{\"type\":\"Program\",\"body\":[{\"type\":\"FunctionDef\",\"id\":\"main\",\"return_type\":\"int32\",\"parameters\""
                            ":{\"type\":\"Expression\",\"id\":\"ParameterList\",\"declarations\":[]},\"body\":{\"type\":\"ExecutionBlock\",\"execution\""
                            ":[{\"type\":\"Expression\",\"id\":\"ReturnType\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"To Be Determined\""
                            ",\"value\":\"0\"}]}]}}],\"SourceType\":\"module\"}";
    auto data = compileToAST(std::vector<lstd::string>(),lstd::move(source));
    if(data.isError) printf("Compiler Test: %s", data.error_msg.c_str());
    EXPECT_FALSE(data.isError);
    EXPECT_STREQ(data.data_msg.c_str(),result);
}

TEST(AST,PARSE_MAIN_WITH_VAR_UINT8_WITH_VALUE)
{
    lstd::string source = "func main() -> int32 { uint8 x = 30 ret 0}";
    const char* result = "{\"type\":\"Program\",\"body\":[{\"type\":\"FunctionDef\",\"id\":\"main\",\"return_type\":\"int32\",\"parameters\":{\"type\":\"Expression\",\"id\":\"ParameterList\",\"declarations\":[]},\"body\":{\"type\":\"ExecutionBlock\",\"execution\":[{\"type\":\"Expression\",\"id\":\"VariableDefinition\",\"name\":\"x\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"uint8\",\"value\":\"30\"}]},{\"type\":\"Expression\",\"id\":\"ReturnType\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"To Be Determined\",\"value\":\"0\"}]}]}}],\"SourceType\":\"module\"}";
    auto data = compileToAST(std::vector<lstd::string>(),lstd::move(source));
    if(data.isError) printf("Compiler Test: %s", data.error_msg.c_str());
    EXPECT_FALSE(data.isError);
    EXPECT_STREQ(data.data_msg.c_str(),result);
}

TEST(AST,PARSE_MAIN_WITH_VAR_UINT16_WITH_VALUE)
{
    lstd::string source = "func main() -> int32 { uint16 x = 30 ret 0}";
    const char* result = "{\"type\":\"Program\",\"body\":[{\"type\":\"FunctionDef\",\"id\":\"main\",\"return_type\":\"int32\",\"parameters\":{\"type\":\"Expression\",\"id\":\"ParameterList\",\"declarations\":[]},\"body\":{\"type\":\"ExecutionBlock\",\"execution\":[{\"type\":\"Expression\",\"id\":\"VariableDefinition\",\"name\":\"x\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"uint16\",\"value\":\"30\"}]},{\"type\":\"Expression\",\"id\":\"ReturnType\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"To Be Determined\",\"value\":\"0\"}]}]}}],\"SourceType\":\"module\"}";
    auto data = compileToAST(std::vector<lstd::string>(),lstd::move(source));
    if(data.isError) printf("Compiler Test: %s", data.error_msg.c_str());
    EXPECT_FALSE(data.isError);
    EXPECT_STREQ(data.data_msg.c_str(),result);
}

TEST(AST,PARSE_MAIN_WITH_VAR_UINT32_WITH_VALUE)
{
    lstd::string source = "func main() -> int32 { uint32 x = 30 ret 0}";
    const char* result = "{\"type\":\"Program\",\"body\":[{\"type\":\"FunctionDef\",\"id\":\"main\",\"return_type\":\"int32\",\"parameters\":{\"type\":\"Expression\",\"id\":\"ParameterList\",\"declarations\":[]},\"body\":{\"type\":\"ExecutionBlock\",\"execution\":[{\"type\":\"Expression\",\"id\":\"VariableDefinition\",\"name\":\"x\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"uint32\",\"value\":\"30\"}]},{\"type\":\"Expression\",\"id\":\"ReturnType\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"To Be Determined\",\"value\":\"0\"}]}]}}],\"SourceType\":\"module\"}";
    auto data = compileToAST(std::vector<lstd::string>(),lstd::move(source));
    if(data.isError) printf("Compiler Test: %s", data.error_msg.c_str());
    EXPECT_FALSE(data.isError);
    EXPECT_STREQ(data.data_msg.c_str(),result);
}

TEST(AST,PARSE_MAIN_WITH_VAR_UINT64_WITH_VALUE)
{
    lstd::string source = "func main() -> int32 { uint64 x = 30 ret 0}";
    const char* result = "{\"type\":\"Program\",\"body\":[{\"type\":\"FunctionDef\",\"id\":\"main\",\"return_type\":\"int32\",\"parameters\":{\"type\":\"Expression\",\"id\":\"ParameterList\",\"declarations\":[]},\"body\":{\"type\":\"ExecutionBlock\",\"execution\":[{\"type\":\"Expression\",\"id\":\"VariableDefinition\",\"name\":\"x\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"uint64\",\"value\":\"30\"}]},{\"type\":\"Expression\",\"id\":\"ReturnType\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"To Be Determined\",\"value\":\"0\"}]}]}}],\"SourceType\":\"module\"}";
    auto data = compileToAST(std::vector<lstd::string>(),lstd::move(source));
    if(data.isError) printf("Compiler Test: %s", data.error_msg.c_str());
    EXPECT_FALSE(data.isError);
    EXPECT_STREQ(data.data_msg.c_str(),result);
}

TEST(AST,PARSE_MAIN_WITH_VAR_INT8_WITH_VALUE)
{
    lstd::string source = "func main() -> int32 { int8 x = 30 ret 0}";
    const char* result = "{\"type\":\"Program\",\"body\":[{\"type\":\"FunctionDef\",\"id\":\"main\",\"return_type\":\"int32\",\"parameters\":{\"type\":\"Expression\",\"id\":\"ParameterList\",\"declarations\":[]},\"body\":{\"type\":\"ExecutionBlock\",\"execution\":[{\"type\":\"Expression\",\"id\":\"VariableDefinition\",\"name\":\"x\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"int8\",\"value\":\"30\"}]},{\"type\":\"Expression\",\"id\":\"ReturnType\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"To Be Determined\",\"value\":\"0\"}]}]}}],\"SourceType\":\"module\"}";
    auto data = compileToAST(std::vector<lstd::string>(),lstd::move(source));
    if(data.isError) printf("Compiler Test: %s", data.error_msg.c_str());
    EXPECT_FALSE(data.isError);
    EXPECT_STREQ(data.data_msg.c_str(),result);
}

TEST(AST,PARSE_MAIN_WITH_VAR_INT16_WITH_VALUE)
{
    lstd::string source = "func main() -> int32 { int16 x = 30 ret 0}";
    const char* result = "{\"type\":\"Program\",\"body\":[{\"type\":\"FunctionDef\",\"id\":\"main\",\"return_type\":\"int32\",\"parameters\":{\"type\":\"Expression\",\"id\":\"ParameterList\",\"declarations\":[]},\"body\":{\"type\":\"ExecutionBlock\",\"execution\":[{\"type\":\"Expression\",\"id\":\"VariableDefinition\",\"name\":\"x\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"int16\",\"value\":\"30\"}]},{\"type\":\"Expression\",\"id\":\"ReturnType\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"To Be Determined\",\"value\":\"0\"}]}]}}],\"SourceType\":\"module\"}";
    auto data = compileToAST(std::vector<lstd::string>(),lstd::move(source));
    if(data.isError) printf("Compiler Test: %s", data.error_msg.c_str());
    EXPECT_FALSE(data.isError);
    EXPECT_STREQ(data.data_msg.c_str(),result);
}

TEST(AST,PARSE_MAIN_WITH_VAR_INT32_WITH_VALUE)
{
    lstd::string source = "func main() -> int32 { int32 x = 30 ret 0}";
    const char* result = "{\"type\":\"Program\",\"body\":[{\"type\":\"FunctionDef\",\"id\":\"main\",\"return_type\":\"int32\",\"parameters\":{\"type\":\"Expression\",\"id\":\"ParameterList\",\"declarations\":[]},\"body\":{\"type\":\"ExecutionBlock\",\"execution\":[{\"type\":\"Expression\",\"id\":\"VariableDefinition\",\"name\":\"x\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"int32\",\"value\":\"30\"}]},{\"type\":\"Expression\",\"id\":\"ReturnType\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"To Be Determined\",\"value\":\"0\"}]}]}}],\"SourceType\":\"module\"}";
    auto data = compileToAST(std::vector<lstd::string>(),lstd::move(source));
    if(data.isError) printf("Compiler Test: %s", data.error_msg.c_str());
    EXPECT_FALSE(data.isError);
    EXPECT_STREQ(data.data_msg.c_str(),result);
}

TEST(AST,PARSE_MAIN_WITH_VAR_INT64_WITH_VALUE)
{
    lstd::string source = "func main() -> int32 { int64 x = 30 ret 0}";
    const char* result = "{\"type\":\"Program\",\"body\":[{\"type\":\"FunctionDef\",\"id\":\"main\",\"return_type\":\"int32\",\"parameters\":{\"type\":\"Expression\",\"id\":\"ParameterList\",\"declarations\":[]},\"body\":{\"type\":\"ExecutionBlock\",\"execution\":[{\"type\":\"Expression\",\"id\":\"VariableDefinition\",\"name\":\"x\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"int64\",\"value\":\"30\"}]},{\"type\":\"Expression\",\"id\":\"ReturnType\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"To Be Determined\",\"value\":\"0\"}]}]}}],\"SourceType\":\"module\"}";
    auto data = compileToAST(std::vector<lstd::string>(),lstd::move(source));
    if(data.isError) printf("Compiler Test: %s", data.error_msg.c_str());
    EXPECT_FALSE(data.isError);
    EXPECT_STREQ(data.data_msg.c_str(),result);
}

TEST(AST,PARSE_MAIN_WITH_VAR_UINT8_WITHOUT_VALUE)
{
    lstd::string source = "func main() -> int32 { uint8 x ret 0}";
    const char* result = "{\"type\":\"Program\",\"body\":[{\"type\":\"FunctionDef\",\"id\":\"main\",\"return_type\":\"int32\",\"parameters\":{\"type\":\"Expression\",\"id\":\"ParameterList\",\"declarations\":[]},\"body\":{\"type\":\"ExecutionBlock\",\"execution\":[{\"type\":\"Expression\",\"id\":\"VariableDefinition\",\"name\":\"x\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"uint8\",\"value\":\"0\"}]},{\"type\":\"Expression\",\"id\":\"ReturnType\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"To Be Determined\",\"value\":\"0\"}]}]}}],\"SourceType\":\"module\"}";
    auto data = compileToAST(std::vector<lstd::string>(),lstd::move(source));
    if(data.isError) printf("Compiler Test: %s", data.error_msg.c_str());
    EXPECT_FALSE(data.isError);
    EXPECT_STREQ(data.data_msg.c_str(),result);
}

TEST(AST,PARSE_MAIN_WITH_VAR_UINT16_WITHOUT_VALUE)
{
    lstd::string source = "func main() -> int32 { uint16 x ret 0}";
    const char* result = "{\"type\":\"Program\",\"body\":[{\"type\":\"FunctionDef\",\"id\":\"main\",\"return_type\":\"int32\",\"parameters\":{\"type\":\"Expression\",\"id\":\"ParameterList\",\"declarations\":[]},\"body\":{\"type\":\"ExecutionBlock\",\"execution\":[{\"type\":\"Expression\",\"id\":\"VariableDefinition\",\"name\":\"x\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"uint16\",\"value\":\"0\"}]},{\"type\":\"Expression\",\"id\":\"ReturnType\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"To Be Determined\",\"value\":\"0\"}]}]}}],\"SourceType\":\"module\"}";
    auto data = compileToAST(std::vector<lstd::string>(),lstd::move(source));
    if(data.isError) printf("Compiler Test: %s", data.error_msg.c_str());
    EXPECT_FALSE(data.isError);
    EXPECT_STREQ(data.data_msg.c_str(),result);
}

TEST(AST,PARSE_MAIN_WITH_VAR_UINT32_WITHOUT_VALUE)
{
    lstd::string source = "func main() -> int32 { uint32 x ret 0}";
    const char* result = "{\"type\":\"Program\",\"body\":[{\"type\":\"FunctionDef\",\"id\":\"main\",\"return_type\":\"int32\",\"parameters\":{\"type\":\"Expression\",\"id\":\"ParameterList\",\"declarations\":[]},\"body\":{\"type\":\"ExecutionBlock\",\"execution\":[{\"type\":\"Expression\",\"id\":\"VariableDefinition\",\"name\":\"x\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"uint32\",\"value\":\"0\"}]},{\"type\":\"Expression\",\"id\":\"ReturnType\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"To Be Determined\",\"value\":\"0\"}]}]}}],\"SourceType\":\"module\"}";
    auto data = compileToAST(std::vector<lstd::string>(),lstd::move(source));
    if(data.isError) printf("Compiler Test: %s", data.error_msg.c_str());
    EXPECT_FALSE(data.isError);
    EXPECT_STREQ(data.data_msg.c_str(),result);
}

TEST(AST,PARSE_MAIN_WITH_VAR_UINT64_WITHOUT_VALUE)
{
    lstd::string source = "func main() -> int32 { uint64 x ret 0}";
    const char* result = "{\"type\":\"Program\",\"body\":[{\"type\":\"FunctionDef\",\"id\":\"main\",\"return_type\":\"int32\",\"parameters\":{\"type\":\"Expression\",\"id\":\"ParameterList\",\"declarations\":[]},\"body\":{\"type\":\"ExecutionBlock\",\"execution\":[{\"type\":\"Expression\",\"id\":\"VariableDefinition\",\"name\":\"x\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"uint64\",\"value\":\"0\"}]},{\"type\":\"Expression\",\"id\":\"ReturnType\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"To Be Determined\",\"value\":\"0\"}]}]}}],\"SourceType\":\"module\"}";
    auto data = compileToAST(std::vector<lstd::string>(),lstd::move(source));
    if(data.isError) printf("Compiler Test: %s", data.error_msg.c_str());
    EXPECT_FALSE(data.isError);
    EXPECT_STREQ(data.data_msg.c_str(),result);
}

TEST(AST,PARSE_MAIN_WITH_VAR_INT8_WITHOUT_VALUE)
{
    lstd::string source = "func main() -> int32 { int8 x ret 0}";
    const char* result = "{\"type\":\"Program\",\"body\":[{\"type\":\"FunctionDef\",\"id\":\"main\",\"return_type\":\"int32\",\"parameters\":{\"type\":\"Expression\",\"id\":\"ParameterList\",\"declarations\":[]},\"body\":{\"type\":\"ExecutionBlock\",\"execution\":[{\"type\":\"Expression\",\"id\":\"VariableDefinition\",\"name\":\"x\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"int8\",\"value\":\"0\"}]},{\"type\":\"Expression\",\"id\":\"ReturnType\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"To Be Determined\",\"value\":\"0\"}]}]}}],\"SourceType\":\"module\"}";
    auto data = compileToAST(std::vector<lstd::string>(),lstd::move(source));
    if(data.isError) printf("Compiler Test: %s", data.error_msg.c_str());
    EXPECT_FALSE(data.isError);
    EXPECT_STREQ(data.data_msg.c_str(),result);
}

TEST(AST,PARSE_MAIN_WITH_VAR_INT16_WITHOUT_VALUE)
{
    lstd::string source = "func main() -> int32 { int16 x ret 0}";
    const char* result ="{\"type\":\"Program\",\"body\":[{\"type\":\"FunctionDef\",\"id\":\"main\",\"return_type\":\"int32\",\"parameters\":{\"type\":\"Expression\",\"id\":\"ParameterList\",\"declarations\":[]},\"body\":{\"type\":\"ExecutionBlock\",\"execution\":[{\"type\":\"Expression\",\"id\":\"VariableDefinition\",\"name\":\"x\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"int16\",\"value\":\"0\"}]},{\"type\":\"Expression\",\"id\":\"ReturnType\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"To Be Determined\",\"value\":\"0\"}]}]}}],\"SourceType\":\"module\"}";
    auto data = compileToAST(std::vector<lstd::string>(),lstd::move(source));
    if(data.isError) printf("Compiler Test: %s", data.error_msg.c_str());
    EXPECT_FALSE(data.isError);
    EXPECT_STREQ(data.data_msg.c_str(),result);
}

TEST(AST,PARSE_MAIN_WITH_VAR_INT32_WITHOUT_VALUE)
{
    lstd::string source = "func main() -> int32 { int32 x ret 0}";
    const char* result = "{\"type\":\"Program\",\"body\":[{\"type\":\"FunctionDef\",\"id\":\"main\",\"return_type\":\"int32\",\"parameters\":{\"type\":\"Expression\",\"id\":\"ParameterList\",\"declarations\":[]},\"body\":{\"type\":\"ExecutionBlock\",\"execution\":[{\"type\":\"Expression\",\"id\":\"VariableDefinition\",\"name\":\"x\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"int32\",\"value\":\"0\"}]},{\"type\":\"Expression\",\"id\":\"ReturnType\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"To Be Determined\",\"value\":\"0\"}]}]}}],\"SourceType\":\"module\"}";
    auto data = compileToAST(std::vector<lstd::string>(),lstd::move(source));
    if(data.isError) printf("Compiler Test: %s", data.error_msg.c_str());
    EXPECT_FALSE(data.isError);
    EXPECT_STREQ(data.data_msg.c_str(),result);
}

TEST(AST,PARSE_MAIN_WITH_VAR_INT64_WITHOUT_VALUE)
{
    lstd::string source = "func main() -> int32 { int64 x ret 0}";
    const char* result = "{\"type\":\"Program\",\"body\":[{\"type\":\"FunctionDef\",\"id\":\"main\",\"return_type\":\"int32\",\"parameters\":{\"type\":\"Expression\",\"id\":\"ParameterList\",\"declarations\":[]},\"body\":{\"type\":\"ExecutionBlock\",\"execution\":[{\"type\":\"Expression\",\"id\":\"VariableDefinition\",\"name\":\"x\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"int64\",\"value\":\"0\"}]},{\"type\":\"Expression\",\"id\":\"ReturnType\",\"declarations\":[{\"type\":\"Literal\",\"data_type\":\"To Be Determined\",\"value\":\"0\"}]}]}}],\"SourceType\":\"module\"}";
    auto data = compileToAST(std::vector<lstd::string>(),lstd::move(source));
    if(data.isError) printf("Compiler Test: %s", data.error_msg.c_str());
    EXPECT_FALSE(data.isError);
    EXPECT_STREQ(data.data_msg.c_str(),result);
}


//TODO: add float32, float64
int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}