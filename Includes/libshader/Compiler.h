#pragma once
#if _WIN64
#    define EXPORT_DLL __declspec(dllexport)
#else
#    define EXPORT_DLL
#endif
#include <lstd/DataType.h>
#include <lstd/String.h>
#include <vector>

typedef struct glmErrorOrData
{
    bool isError = false;
    lstd::string error_msg = "";
    lstd::string data_msg = "";

    explicit glmErrorOrData() = default;
    glmErrorOrData(bool isError,lstd::string error_msg) : isError(isError),error_msg(error_msg){};
    glmErrorOrData(lstd::string data_msg) : data_msg(data_msg){};
} glmComplierError;

EXPORT_DLL const glmErrorOrData compileToSpirv(std::vector<lstd::string>,lstd::string);
EXPORT_DLL const glmErrorOrData compileToX86(std::vector<lstd::string>,lstd::string);
EXPORT_DLL const glmErrorOrData compileToAST(std::vector<lstd::string>,lstd::string);
