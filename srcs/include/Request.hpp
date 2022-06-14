#ifndef __REQUEST_HPP__
#define __REQUEST_HPP__

#include <iostream>
#include "../parser_request/include/ParserRe.hpp"

class Request
{
    private:
    int         _content_length;
    int         _readed_body;
    std::string _buffer;
    bool        _isHeaderReaded;
    bool        _is_chanked;

    public:
    Request();

    // Getters && Setters
    int         getContentLength();
    void        setContentLength(int content_length);
    int         getReadBody();
    std::string getBuffer();
    void        setHeaderReaded(bool isHeaderReaded);

    // Member functions
    void        appandBuffer(char * buffer, int length);
    bool        isHeaderReaded();
    int		    calculateReadedBody(char *buffer, int length);
    int         setHeaders(char *buffer);
    bool        isChanked();
    void        deleteDelimeter(bool begin);

};

#endif