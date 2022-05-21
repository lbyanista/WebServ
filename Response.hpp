#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <iostream>
#include <fstream>
#define string std::string
#define cout std::cout
#define endl std::endl

class Response
{
private:
    string _s_line;
public:
    Response(/* args */);
    ~Response();
    // string NotFound(string s_line);
    void Set_Sline(string s_line);
    string Get_Sline(void);
};



#endif