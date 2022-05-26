#include "Response.hpp"

Response::Response(){

}

Response::Response(std::string status){
    code_status = status.substr(0, 3);
    phrase_status = status.substr(4);
}

Response::~Response(){

}

void Response::append_header(std::string fst, std::string scd){
    _headers.insert(std::make_pair(fst, scd));
}

int Response::Get_body_size(){
    return(_body.size());
}

std::string Response::make_header(){
    std::string rst;
    //"HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!
    rst.append("HTTP/1.1" + code_status + " OK" + "\r\n" + "Content-Type: text/html\r\n");
    for (std::map<std::string, std::string>::iterator itr = _headers.begin(); itr != _headers.end(); itr++)
        rst.append((*itr).first + ": " + (*itr).second + "\r\n");
    rst.append("\r\n");
    return (rst);
}

void Response::make_body_status(){
	
    _body.clear();
    
    std::string rst;

    rst.append("<!DOCTYPE html><html><head><meta charset=\"UTF-8\"/><title>WebServ</title></head>");
	rst.append("<body>");
	rst.append("<h1>" + code_status + "</h1>");
	rst.append("<h3>" + phrase_status + "</h3>");
    //if return to home oplig decomment the line buttom
	// rst.append("<p>Click <a href=\"/\">here</a> to return home.</p>");
	rst.append("</body></html>");
	
	_body = rst;
}

void Response::make_body_status(std::string url){
    _body.clear();
    std::string rst;

    rst.append(url);
    _body = rst;
}

std::string Response::serialize(){
    std::string rst;

    rst.append("HTTP/1.1 " + code_status + " OK" + "\n" + "Content-Type: text/plain\n" + "Content-Length: 1\n");
    for (std::map<std::string, std::string>::iterator itr = _headers.begin(); itr != _headers.end(); itr++)
        rst.append((*itr).first + ": " + (*itr).second + "\n");
    rst.append("\n");
    rst.append(_body);

    return (rst);
    
}

std::string  Response::handleResponse(RequestInfo request_info, ServerSetup server_setup){
    //  code_status = "200";
    // std::ofstream Myfile("ResponseFile.txt");
    // append_header("Host", "127.0.0.1:8000");
    // make_header();
    // make_body_status();
    // _body = "Hello world!";
    // Myfile << Resp.serialize();
    // Myfile.close();
    // return(serialize());

    //1 -  verify any method (GET POST DELETE) //     // and exist in config file 


    // Verifiez extention of file if exist
    std::string response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: ";

    // verifier root && the file if exist

    // calculate Lenght of the file;
    
    // verify any method (GET POST DELETE) 
    if (request_info.getRequest_method() == "GET")
    {   
        std::string path;
        // if root
        if (request_info.getRequest_target() == "/about")
            path = server_setup.getRoot() + "/" + server_setup.getLocations()[0].index[0];
        else // if location
            path = server_setup.getRoot() + "/" + server_setup.getIndex().at(0);
        
        std::ifstream index_file(path);

        if (!index_file.is_open())
            return (0);
    
        std::cout << "\n\n/<< ****************** Index Content : ********************* >>"<< std:: endl;
        std::string response_line;
        std::string body;
        int         size_body = 0;
        while (std::getline(index_file, response_line))
        {
            // std::istringstream iss(response_line);
            // int a, b;
            // if (!(iss >> a >> b)) { break; } // error
            body.append(response_line);
            size_body += response_line.length();
            if (!index_file.eof())
            {
                body.append("\n");
                size_body++;
            }
        }
        response.append(std::to_string(size_body));
        response.append("\r\n\r\n");
        response.append(body);
    }
    return (response);

}