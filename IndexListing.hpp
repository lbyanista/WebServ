#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>

class IndexListing
{
private:
    /* data */
public:
    IndexListing(/* args */);
    ~IndexListing();

    std::string get_current_dir();
    std::string get_current_dir(char *path);
    bool        File_Folder(const char * fileName);
    int         is_Folder(const char *File_name);
    int         Listing();
};
