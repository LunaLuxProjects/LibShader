#pragma once
#if _WIN64
#    define EXPORT_DLL __declspec(dllexport)
#else
#    define EXPORT_DLL
#endif
#include <lstd/DataType.h>
#include <string>
#include <vector>

typedef struct glmErrorOrData
{
    bool isError = false;
    std::string error_msg;
    std::string data_msg;

    explicit glmErrorOrData() = default;
    glmErrorOrData(bool isError,std::string error_msg) : isError(isError),error_msg(error_msg){};
    glmErrorOrData(std::string data_msg) : data_msg(data_msg){};
} glmComplierError;

EXPORT_DLL const glmErrorOrData compileToSpirv(std::vector<std::string>,std::string);
EXPORT_DLL const glmErrorOrData compileToX86(std::vector<std::string>,std::string);
EXPORT_DLL const glmErrorOrData compileToAST(std::vector<std::string>,std::string);
