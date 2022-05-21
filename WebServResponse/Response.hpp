#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <iostream>
#include <map>
#include <string>

#define cout std::cout
#define endl std::endl
#define string std::string

class Response
{
private:
    string _body;
    std::map<string, string> _headers;

public:
    string code_status;
    string phrase_status;
    Response();
    Response(string status);
    ~Response();

    void    append_header(string fst, string scd);
	int     Get_body_size();

	void    make_body_status();
	void    make_body_status(string url);
	string  make_header();
	string  serialize();

};

#endif // !RESPONSE_HPP
