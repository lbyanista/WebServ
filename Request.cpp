#include "include/Request.hpp"
#include "include/Utils.hpp"


Request::Request()
{
    _content_length = 0;
    _readed_body = 0;
    _buffer = "";
    _isHeaderReaded = false;
}

int         Request::getContentLength()
{
    return (this->_content_length);
}


int         Request::getReadBody()
{
    return (this->_readed_body);
}


std::string Request::getBuffer()
{
    return (this->_buffer);
}

void        Request::setHeaderReaded(bool isHeaderReaded)
{
    this->_isHeaderReaded = isHeaderReaded;
}

// Member functions
void        Request::appandBuffer(char * buffer, int length)
{
    this->_buffer.append(std::string(buffer, length));
    if (this->_isHeaderReaded == false)
    {
        this->_readed_body += calculateReadedBody(buffer, length);
        this->_isHeaderReaded = true;
        return ;
    }
    this->_readed_body += length;
}

bool        Request::isHeaderReaded()
{
    return (this->_isHeaderReaded);
}

int         Request::calculateReadedBody(char *buffer, int length)
{
	for (int i = 0; i < (length - 3); i++)
	{
		if (buffer[i] == '\r' && buffer[i + 1] == '\n' && buffer[i + 2] == '\r' && buffer[i + 3] == '\n')
			return (length - i - 4);
	}
	return (0);
}

void         Request::setContentLength(char *buffer)
{
    LexerRe lexer(buffer);
	ParserRe parser(lexer);
	RequestInfo request_info = parser.parse();

	if (request_info.getHeaders().find("Content-Length") != request_info.getHeaders().end())
		this->_content_length =  stringToInt(request_info.getHeaders()["Content-Length"]);
    else
	    this->_content_length = 0;
}

