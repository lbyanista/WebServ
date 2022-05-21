#include <iostream>
#include <fstream>
#include <iostream>
#include <sstream> //std::stringstream

#include "Server.hpp"
#include "parser_config/include/Parser.hpp"


std::string fileToSring(const char *file)
{
    std::ifstream inFile;
    inFile.open(file); //open the input file

    std::stringstream strStream;
    strStream << inFile.rdbuf(); //read the file
    std::string str = strStream.str(); //str holds the content of the file

    inFile.close();
    return(str);
}

std::vector<ServerSetup> parseConfig(int argc, char **argv)
{
    std::string contents;
    if (argc == 2)
        contents = fileToSring(argv[1]);
    else
        contents = fileToSring(std::string("test.config").c_str());
     Lexer lexer(contents);
    // Token token(TOKEN_EOF, "\0");
    // while((token = lexer.getNextToken()).type != TOKEN_EOF)
    //     std::cout << "Token \"" << token.type << " | value = \"" << token.value << "\"" << std::endl;

    Parser parser(lexer);
    std::vector<ServerSetup> servers; 
    return (parser.parse());
}

int main(int argc, char *argv[])
{

    // ------------------- Parsing Config File ------------------- //

    std::vector<ServerSetup> servers = parseConfig(argc, argv);

    // --------------------- Test Parsing ------------------------ //

    // for (int i = 0; i < (int)servers.size() ;i++)
    //     std::cout << "Server: " << i
    //             << " | Server name1: " << servers[i].server_name[0]
    //             << " | Error pages: " <<  servers[i].error_pages[0].second
    //             << " port: "<< servers[i].listen.first << std::endl;

    // std::cout << "Server: 0 | " << servers[0].locations[1].path << std::endl;
    // std::cout << "Server: 0 | " << servers[0].locations[1].error_pages[0].second << std::endl;
        
    // --------------------- Run Server --------------------------- //

    // run();

    // ------------------------------------------------------------- //

    return (0);
}