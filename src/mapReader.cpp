#include "mapReader.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>


// Define the static values here.
std::vector<Point> MapReader::buildingCoords;
std::vector<Point> MapReader::streetLampCoords;
std::vector<Point> MapReader::treeCoords;
std::vector<Point> MapReader::fireHydrantCoords;
std::vector<Point> MapReader::roadIntersectionCoords;


// Reads the coordinate file.
void MapReader::readCoordFile(const char *fileName){
    // TODO - make this global or returned from Terrain map object
    const int farX = 20400.0f;
	const int farY = 20400.0f;//19840.0f;
	const int xOffset = -190;
	const int yOffset = -190; // TODO: what the hell?
	
	// Try to open the map coordinate file.
	std::ifstream mapfile(fileName);
	if(mapfile.fail()){
	    std::cerr << "ERROR: Cannot open map file." << std::endl;
	    return;
	}
	
	// If the file is readable, read it line by line.
    for(std::string line; getline(mapfile, line); ) {
        if(line.size() == 0) // skip empty lines
            continue;
        
        // Get type of coordinate.
        char type = line[0];
        
        // Attempt to read the two coordinates (x, y)
        std::string ignore;
        float coordX, coordY;
        std::istringstream lineParser(line);
        lineParser >> ignore;
        lineParser >> coordX;
        lineParser >> coordY;
        // If something failed, it's an invalid format, just skip.
        if(lineParser.fail()){
            std::cerr << "ERROR: Invalid line in map file:" << std::endl
                      << "       " << line << std::endl;
            continue;
        }
        
        // Create the Point, scaled to the map's scale
        Point pos;
        pos.x = (farX * coordX) + xOffset;
        pos.y = (farY * coordY) + yOffset;
        
        // Push the coordinates to the correct list, based on type.
        switch(type){
            case 'b': // building
                MapReader::buildingCoords.push_back(pos);
                break;
            case 'l': // street lamp
                MapReader::streetLampCoords.push_back(pos);
                break;
            case 't': // tree
                MapReader::treeCoords.push_back(pos);
                break;
            case 'r': // road intersection
                MapReader::roadIntersectionCoords.push_back(pos);
                break;
            case 'f': // fire hydrant
                MapReader::fireHydrantCoords.push_back(pos);
                break;
            default:
                break;
        }
    }
}
