/*	File: directoryReader.h
 *	Authors: teamKillYourself
 *
 *	Description: provides a global interface for reading a directory of files
 *  into the specified list (std library list).
 */

#include "directoryReader.h"

// c++ headers for reading directory
#include <dirent.h>
#include <iostream>

using namespace std;


void DirectoryReader::getDirectoryFiles(
    string dirName,                     // directory name
    std::vector<const char *> &list, // list to be populated
    string startsWith)                  // optional regex to filter values
{
    DIR *dp;
    struct dirent *dirp;
    
    // Try to open directory. If failed, print error and return.
    if((dp = opendir(dirName.c_str())) == NULL) {
        cerr << "ERROR: Can't open directory \"" << dirName << "\"." << endl;
        return;
    }
    
    // Make sure "/" is at the end of the directory name.
    if(dirName.length() > 0 && dirName[dirName.length() - 1] != '/')
        dirName += "/";
    
    while((dirp = readdir(dp)) != NULL) {
        // Make sure file name is correctly named / long enough.
        string fileName(dirp->d_name);
        if(fileName.length() == 0 || fileName.length() < startsWith.length())
            continue;
        
        // Make sure first part of file name matches the startsWith string.
        string test = fileName.substr(0, startsWith.length());
        if(test != startsWith)
            continue;
        
        // If all went well, add the string to the list.
        list.push_back((string(dirName + "/" + dirp->d_name).c_str()));
    }
    
    closedir(dp);
}
