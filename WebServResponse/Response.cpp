#include "Response.hpp"

Response::Response(){

}

Response::Response(string status){
    code_status = status.substr(0, 3);
    phrase_status = status.substr(4);
}

Response::~Response(){

}

void Response::append_header(string fst, string scd){
    _headers.insert(std::make_pair(fst, scd));
}

int Response::Get_body_size(){
    return(_body.size());
}

string Response::make_header(){
    string rst;

    rst.append("HTTP/1.1" + code_status + "\r\n");
    for (std::map<string, string>::iterator itr = _headers.begin(); itr != _headers.end(); itr++)
        rst.append((*itr).first + ": " + (*itr).second + "\r\n");
    rst.append("\r\n");
    return (rst);
}

void Response::make_body_status(){
	
    _body.clear();
    
    string rst;

    rst.append("<!DOCTYPE html><html><head><meta charset=\"UTF-8\"/><title>WebServ</title></head>");
	rst.append("<body>");
	rst.append("<h1>" + code_status + "</h1>");
	rst.append("<h3>" + phrase_status + "</h3>");
    //if return to home oplig decomment the line buttom
	// rst.append("<p>Click <a href=\"/\">here</a> to return home.</p>");
	rst.append("</body></html>");
	
	_body = rst;
}

void Response::make_body_status(string url){
    _body.clear();
    string rst;

    rst.append(url);
    _body = rst;
}

string Response::serialize(){
    string rst;

    rst.append("HTTP/1.1" + code_status + "\r\n");
    for (std::map<string, string>::iterator itr = _headers.begin(); itr != _headers.end(); itr++)
        rst.append((*itr).first + ": " + (*itr).second + "\r\n");
    rst.append("\r\n");
    rst.append(_body);

    return (rst);
    
}

int main(){
    Response Resp;
    Resp.append_header("Host", "127.0.0.1:8000");
    Resp.make_header();
    Resp.make_body_status();

    cout << Resp.serialize();
    return 0;
}