#include <iostream>
#include <string>
#include <fstream>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>

class IndexListing
{
    private:

    public:


};

std::string get_current_dir() {
   char buff[FILENAME_MAX]; //create string buffer to hold path
   getcwd( buff, FILENAME_MAX );
   std::string current_working_dir(buff);
   return current_working_dir;
}

std::string get_current_dir(char *path) {
//    char buff[FILENAME_MAX]; //create string buffer to hold path
   getcwd( path, sizeof(path) );
   std::string current_working_dir(path);
   return current_working_dir;
}

bool File_Folder(const char *fileName){
    std::ifstream infile(fileName);
    return infile.good();
}


struct  states
{
    std::string name;
    int size;
    std::string date;
} s_state;


int is_Folder(const char *File_name){
    struct stat stats;
    std::ifstream inFile(File_name);
    if(File_Folder(File_name)){
        if(stat(File_name, &stats) == 0 && stats.st_mode == 16877)
            return (2); // is folder
        else 
            return (1); // is File
        // return (inFile.good());
    }
    return (-1);
}

int main(){
    std::string str;
    std::string code_status = "200";

    std::ofstream IndexHtml("IndexListing.html");

    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    str.append("<!DOCTYPE html>\n<html>\n<head>\n<meta charset=\"UTF-8\"/>\n<title>Indexing</title>\n<link rel=\"stylesheet\" href>\n</head>\n");
	str.append("<body>\n");
	str.append("<h1> Index of " + get_current_dir() + "<hr width=\"100%\"></h1>\n");
    if(d) {
        str.append("<ul>\n");
        while((dir = readdir(d)) != NULL){
            if(is_Folder(dir->d_name) == 1)
                str.append("<li>\n<a href=" + get_current_dir() + "/" + dir->d_name + "> " + dir->d_name + " </a>\n</li>\n");
            // std::cout << dir->d_name << std::endl;
        }
        str.append("</ul>\n");
    }
    
    

    // str.append("<a href=\"/Users/mlabrayj/42_Cursus/WebServ/include\"> include</a>\n");
	// // str.append("<h3>" + phrase_status + "</h3>");
    // //if return to home oplig decomment the line buttom
	// // str.append("<p>Click <a href=\"/\">here</a> to return home.</p>");
	str.append("</body>\n</html>");
	
	// _body = str;
    IndexHtml << str;
    closedir(d);
    IndexHtml.close();
    return 0;
}