cmake_minimum_required(VERSION 3.22.0)
project(libshader CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_CXX_EXTENSIONS ON)

#options
option(USE_SANATIZER ON)

#find_package(LLVM CONFIG REQUIRED)
#list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")
#include(HandleLLVMOptions)
#add_definitions(${LLVM_DEFINITIONS})

# add non auto includes here
include_directories(${PROJECT_SOURCE_DIR}/Includes)


set(sources
    src/Complier.cpp
    src/Lexer.cpp
    src/Parser.cpp)

#llvm_map_components_to_libnames(llvm_libs -c)
add_library(libshader SHARED ${sources})
target_include_directories(libshader PRIVATE ${LLVM_INCLUDE_DIRS}  ${PROJECT_SOURCE_DIR}/rapidjson/include STATIC)
if(MSVC)
  target_compile_options(libshader PRIVATE /W4 /WX /EHsc) # /Ofast
else()
  target_compile_options(libshader PRIVATE -Wall -Wextra -Wpedantic -Werror) # -Ofast -fno-exceptions -finline-functions -march=intel
endif()

if(${USE_SANATIZER})
if(MSVC)
  target_compile_options(libshader PRIVATE /fsanitize=address)
else()
  target_compile_options(libshader PRIVATE -fsanitize=address,alignment,bounds,null,unreachable,integer -fno-omit-frame-pointer)
endif()
endif()
if(${LIBSHADER_TESTS})
    add_executable(GlimmerCompiler src/exe/main.cpp)
    target_include_directories(GlimmerCompiler PRIVATE)
    if(MSVC)
      target_compile_options(GlimmerCompiler PRIVATE /EHsc)
    endif()
    target_link_libraries(GlimmerCompiler PRIVATE libshader)
    target_include_directories(GlimmerCompiler PRIVATE  ${PROJECT_SOURCE_DIR}/argparse/include STATIC)

    #add_executable(GlimmerTest src/exe/testmain.cpp)
    #target_link_libraries(GlimmerTest PRIVATE libshader GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main)
endif()