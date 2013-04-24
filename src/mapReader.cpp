/*	File: mapReader.cpp
 *	Authors: teamKillYourself
 *
 *	Description: provides a global interface for reading the map coordinate
 *  file, and storing all of the coordinate data for all map game objects,
 *  such as buildings, trees, lamps, spawn points, etc. This data can be
 *  access globally (static).
 */

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

std::vector<Point> MapReader::enemySpawnPoints;
std::vector<RoadSpawnPoint> MapReader::vehicleSpawnPoints;


// Reads the coordinate file, and parses it. Populates the lists of
//  coordinates as dictated by the file. See documentation on the map
//  file for more information.
// TODO - make documentation for the map file.
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
        
        // ignore first character (type indicator)
        std::string ignore;
        std::istringstream lineParser(line);
        lineParser >> ignore;
        
        // Attempt to read the values
        float coordX, coordY;
        int id1, id2;
        if(type == 'p') { // if path value, read integer ID values
            lineParser >> id1;
            lineParser >> id2;
        }
        else { // otherwise, it will be a float coordinate value
            lineParser >> coordX;
            lineParser >> coordY;
        }
        
        // ignored for all types except road coords and spawn coords:
        int roadID;
        char spawnType;
        
        if(type == 'r') // if reading a road, also read the ID
            lineParser >> roadID;
        
        else if(type == 's'){ // if spawnpoint, also read spawn type + road id
            lineParser >> spawnType;
            lineParser >> roadID;
        }
        
        // If something failed, it's an invalid format, just skip.
        if(lineParser.fail()){
            std::cerr << "WARNING: Invalid entry in map file ("
                      << fileName << ", line " << curLine << "):" << std::endl
                      << "       " << line << std::endl;
            continue;
        }
        
        // Create the Point, scaled to the map's scale
        Point pos;
        pos.X = (farX * coordX) + xOffset;
        pos.Y = (farY * coordY) + yOffset;
        
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
            case 'f': // fire hydrant
                MapReader::fireHydrantCoords.push_back(pos);
                break;
            case 'r': // road intersection
            {
                // create a new road intersection struct
                RoadIntersection intersection;
                intersection.X = pos.X;
                intersection.Y = pos.Y;
                intersection.id = roadID;
                MapReader::roadIntersectionCoords.push_back(intersection);
            }
                break;
            case 'p': // path (connecting two road intersections)
            {
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
                
                // Assign intersections as interconnected (get references).
                MapReader::roadIntersectionCoords[index1].connections.push_back
                    (&(MapReader::roadIntersectionCoords[index2]));
                MapReader::roadIntersectionCoords[index2].connections.push_back
                    (&(MapReader::roadIntersectionCoords[index1]));
            }
                break;
            case 's': // spawnpoint (for enemies, vehicles, etc.)
            {
                switch(spawnType){
                    case 'v': // vehicle
                    {
                        // find road intersection with matching id
                        int numIntersections =
                            MapReader::roadIntersectionCoords.size();
                        int index;
                        for(index=0; index<numIntersections; ++index) {
                            if(MapReader::roadIntersectionCoords[index].id
                                == roadID)
                            {
                                break;
                            }
                        }
                        if(index >= numIntersections) // if out of bounds, gtfo
                            break;
                        
                        // create spawnpoint, and link initial connection to
                        //  the intersection by the located id.
                        RoadSpawnPoint spawnPoint;
                        spawnPoint.X = pos.X;
                        spawnPoint.Y = pos.Y;
                        spawnPoint.connection =
                            &(MapReader::roadIntersectionCoords[index]);
                        MapReader::vehicleSpawnPoints.push_back(spawnPoint);
                    }
                        break;
                    case 'e': // enemy - TODO
                        break;
                    default:
                        break;
                }
            }
                break;
            default:
                std::cerr << "WARNING: Unknown coordinate type in map file ("
                      << fileName << ", line " << curLine << "):" << std::endl
                      << "       " << line << std::endl;
                break;
        }
    }
}


// Clears off all coordinates and information about the map from the existing
//  lists. This should be done when a game is finished.
void MapReader::clearMap() {
    MapReader::buildingCoords.clear();
    MapReader::streetLampCoords.clear();
    MapReader::treeCoords.clear();
    MapReader::fireHydrantCoords.clear();
    MapReader::roadIntersectionCoords.clear();
    enemySpawnPoints.clear();
    vehicleSpawnPoints.clear();
}
