#include "../include/Utils.hpp"
#include <string>

bool    samePort(std::vector<struct sockaddr_in> v_address){

    if (v_address.size() > 1){

        std::vector<struct sockaddr_in>::iterator it_b(v_address.begin());
        std::vector<struct sockaddr_in>::iterator it_e(v_address.end());

        struct sockaddr_in _address = *(--it_e);
        
        while(it_b != it_e){
            if (_address.sin_port == (*it_b++).sin_port)
                return true;
        }
    }
    return false;
}

void set_fds(fd_set &CurrentSockets, std::vector<int> server_fds){

  size_t size = server_fds.size();
  std::vector<int>::iterator it(server_fds.begin());

  FD_ZERO(&CurrentSockets);
  for (size_t i = 0; i < size; i++)
    FD_SET((*it++), &CurrentSockets);
}

//pair<is_find , pair<server_fd, possition>>
std::pair<bool, std::pair<int, size_t> >  find_fd(int fd, std::vector<int> server_fds){
    size_t size = server_fds.size();
    std::vector<int>::iterator it(server_fds.begin());

    for (size_t i = 0; i < size; i++)
    {
      if (fd == *it)
        return  std::make_pair(true, std::make_pair(*it, i));
      it++;
    }
    return std::make_pair(false, std::make_pair(0, 0));
}

int     stringToInt(const std::string s)
{
    for (int i = 0; i < (int)s.length() ; i++)
    {
        if (!std::isdigit(s[i]))
        {
            std::cerr << "\"" << s << "\" Not a valid Number!" << std::endl;
            exit(EXIT_FAILURE);
        }
    }   
    return (atoi(s.c_str()));
}

bool isNumber(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

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

// Split a string to vector of string by a delimter string
std::vector<std::string> split(std::string s, std::string del = " ")
{

    std::vector<std::string> values;

    int start = 0;
    int end = s.find(del);
    while (end != -1) {
        values.push_back(s.substr(start, end - start));
        start = end + del.size();
        end = s.find(del, start);
    }
    values.push_back(s.substr(start, end - start));
    return (values);
}