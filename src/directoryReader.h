/********************************************************************* 
 *	File: directoryReader.h
 *	Authors:  Richard Teammco, Lee Page, Jonathan Miodownik
 *
 *	Description: provides a global interface for reading a directory of files
 *  into the specified list (std library list).
 *********************************************************************/

#ifndef DIRECTORY_READER_H
#define DIRECTORY_READER_H

// Include standard std::list
#include <vector>
#include <string>


// DirectoryReader class:
class DirectoryReader {


  public: // All static (globally accessible)
  
    // Populates the given list of strings with the paths of all file
    //  names in the given directory.
    static void getDirectoryFiles(
        std::string dirName,            // directory name
        std::vector<std::string> &list, // list to be populated
        std::string startsWith = "");   // optional startswith match filter
	
	
}; // end of DirectoryReader class


#endif
