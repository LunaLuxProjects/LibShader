#include <LibShader.h>
#include <argparse/argparse.hpp>
#include <string>
#include <functional>
#include <fstream>
#include <streambuf>
#include <stdio.h>


int main(int argc, char **argv)
{
    argparse::ArgumentParser program("GlimmerCompiler");

    program.add_argument("-s","--source").help("source is needed to compile").required();
    program.add_argument("-o", "--output").default_value(std::string("-")).required().help("specify the output file. Don't add *.(any extension) to the output file");
    program.add_argument("-t", "--target").default_value(std::string("x86_64")).required().help("specify compile target");

    try 
    {
        program.parse_args(argc, argv);
    }
    catch (const std::runtime_error& err) 
    {
        std::cerr << err.what() << std::endl;
        std::cerr << program;
        std::exit(1);
    }

    std::ifstream t;
    try 
    {
        t = std::ifstream(program.get<std::string>("-s").c_str());
    }
    catch (const std::runtime_error& err) 
    {
        std::cerr << err.what() << std::endl;
        std::exit(1);
    }

    std::string str;
    t.seekg(0, std::ios::end);   
    str.reserve(t.tellg());
    t.seekg(0, std::ios::beg);
    str.assign((std::istreambuf_iterator<char>(t)),std::istreambuf_iterator<char>());


    glmErrorOrData data;
    uint32 hash = std::hash<std::string>{}(program.get<std::string>("-t"));
    std::vector<std::string> flags;

    switch(hash)
    {
        case 1900753072:
            data = compileToX86(flags,str);
        case 3689138625:
            data = compileToSpirv(flags,str);
        default:
        {
            std::cerr << "not a valid target: " << program.get<std::string>("-t")<< " of hash" << hash << std::endl;
            std::exit(1);
        }
    }
    return 0;
}