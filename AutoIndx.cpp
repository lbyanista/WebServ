#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <unistd.h>

static void	LinkHref(std::string & index, struct dirent *direntp)
{
	index += "<a href=\"";
	index += direntp->d_name;
	if (direntp->d_type == DT_DIR)
		index += "/";
	index += "\">";
	index += direntp->d_name;
	index += "</a>";
}

std::string autoIndex(std::string filePath)
{
	DIR*			dirp;
	struct dirent*	direntp;
	std::string		index;
	char			buffer[PATH_MAX];
	std::string		path;
    std::ofstream IndexingHtml("AutoIndexPage.html");

	path = getcwd(buffer, PATH_MAX);
	path += "/";
	path += filePath;
	dirp = opendir(path.c_str());
	if( dirp != NULL )
	{
	    index += "<!DOCTYPE html>\n<html>\n\n<title>autoindex</title>\n\n<h1>Index of: " + path + "/<hr width=\"100%\"></h1>";
        for(;;)
		{
            direntp = readdir( dirp );
            if ( direntp == NULL )
				break;
			index += "<h4>";
            //if u need to it's a file or dir or else just decomment lines bellow
			// if ( direntp->d_type == DT_DIR)
			// 	index += "_Directory    => ";
			// else if ( direntp->d_type == DT_REG)
			// 	index += "_File         => ";
			// else
			// 	index += "                ";
			LinkHref(index, direntp);
			index += "</h4>\n";
		}
		index += "</html>";
		closedir( dirp );
	}
    IndexingHtml << index;
    IndexingHtml.close();
	return index;
}