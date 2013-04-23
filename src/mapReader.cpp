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
std::vector<RoadIntersection> MapReader::roadIntersectionCoords;


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
	int curLine = 0;
    for(std::string line; getline(mapfile, line); ) {
        if(line.size() == 0) // skip empty lines
            continue;
        
        // Get type of coordinate.
        char type = line[0];
        
        // If line is commented, skip it.
        if(type == '#')
            continue;
        
        // Increment curLine for error printing.
        curLine++;
        
        // Attempt to read the two coordinates (x, y)
        std::string ignore;
        float coordX, coordY;
        std::istringstream lineParser(line);
        lineParser >> ignore;
        lineParser >> coordX;
        lineParser >> coordY;
        
        int roadID; // ignored unless reading a road coordinate
        if(type == 'r') // if reading a road, also read the ID
            lineParser >> roadID;
        
        // If something failed, it's an invalid format, just skip.
        if(lineParser.fail()){
            std::cerr << "WARNING: Invalid entry in map file ("
                      << fileName << ", line " << curLine << "):" << std::endl
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
            {
                // create a new road intersection struct
                RoadIntersection intersection;
                intersection.x = pos.x;
                intersection.y = pos.y;
                intersection.id = roadID;
                MapReader::roadIntersectionCoords.push_back(intersection);
            }
                break;
            case 'p': // path (connecting two road intersections)
            {
                int id1 = (int)coordX;
                int id2 = (int)coordX;
                int numIntersections = MapReader::roadIntersectionCoords.size();
                
                // find road intersection w/ id1
                int index1;
                for(index1=0; index1<numIntersections; ++index1){
                    if(MapReader::roadIntersectionCoords[index1].id == id1)
                        break;
                }
                // if index out of bounds, not found, so there was a problem.
                if(index1 >= numIntersections)
                    break;
                
                // find road intersection w/ id2
                int index2;
                for(index2=0; index2<numIntersections; ++index2){
                    if(MapReader::roadIntersectionCoords[index2].id == id2)
                        break;
                }
                // if index out of bounds, not found, so there was a problem.
                if(index2 >= numIntersections)
                    break;
                
                // assign intersections as interconnected
                MapReader::roadIntersectionCoords[index1].connections.push_back
                    (MapReader::roadIntersectionCoords[index2]);
                MapReader::roadIntersectionCoords[index2].connections.push_back
                    (MapReader::roadIntersectionCoords[index1]);
            }
                break;
            case 'f': // fire hydrant
                MapReader::fireHydrantCoords.push_back(pos);
                break;
            default:
                std::cerr << "WARNING: Unknown coordinate type in map file ("
                      << fileName << ", line " << curLine << "):" << std::endl
                      << "       " << line << std::endl;
                break;
        }
    }
}
