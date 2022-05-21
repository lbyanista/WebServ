#include "Response.hpp"

Response::Response(){

}

Response::~Response(){

}

// string Response::NotFound(string s_line){
//     _s_line = s_line;
// }

string Response::Get_Sline(void){
    std::fstream myfile("testreq.txt");
    if(myfile.good()){
        getline(myfile, _s_line);
    }
    return (_s_line);
}

void Response::Set_Sline(string s_line){
    _s_line = s_line;
}