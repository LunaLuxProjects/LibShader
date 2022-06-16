#pragma once
#if __has_include(<Components/Defines.h>)
#include <Components/Defines.h>
#else
#if _WIN64
#    define EXPORT_DLL __declspec(dllexport)
#else
#    define EXPORT_DLL
#endif
#include <cstdint>
#include <cstddef>
typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint16_t losUnicode;
typedef uint32_t uint32;
typedef uint64_t uint64;
typedef size_t size;

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef float float32;
typedef double float64;
#endif
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

EXPORT_DLL const glmErrorOrData compileToSpirv(std::vector<std::string>,std::string&);
EXPORT_DLL const glmErrorOrData compileToX86(std::vector<std::string>,std::string&);
EXPORT_DLL const glmErrorOrData compileToAST(std::vector<std::string>,std::string&);
