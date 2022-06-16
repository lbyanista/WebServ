#include "AutoIndex.hpp"

#include <fstream>
#include <dirent.h>
#include <unistd.h>

static void	LinkHref(std::fstream & index, struct dirent *direntp, std::string uri)
{
	if(strcmp(direntp->d_name, ".")){
		index << "<a href=\"";
		if (uri.length() > 1)
			index << uri + "/";
		index << direntp->d_name;
		if (direntp->d_type == DT_DIR)
			index << "/";
		index << "\">";
		index << direntp->d_name;
		index << "</a>";
	}
}

std::string autoIndexPath(std::string filePath, std::string uri)
{
	DIR*			dirp;
	struct dirent*	direntp;
    std::fstream    index_html(AUTO_INDEX_PATH, std::ios::out);

	dirp = opendir(filePath.c_str());
	if ( dirp != NULL )
	{
	    index_html << "<!DOCTYPE html>\n<html>\n\n<title>autoindex</title>\n\n<h1>Index of: " + filePath + "<hr width=\"100%\"></h1>";
        for(;;)
		{
            direntp = readdir( dirp );
            if ( direntp == NULL )
				break;
			index_html << "<h4>";
            //if u need to it's a file or dir or else just decomment lines bellow
			// if ( direntp->d_type == DT_DIR)
			// 	index += "_Directory    => ";
			// else if ( direntp->d_type == DT_REG)
			// 	index += "_File         => ";
			// else
			// 	index += "                ";
			LinkHref(index_html, direntp, uri);
			index_html << "</h4>\n";
		}
		index_html << "</html>";
		closedir( dirp );
	}
	return AUTO_INDEX_PATH;
}