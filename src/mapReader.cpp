/*	File: mapReader.cpp
 *	Authors: teamKillYourself
 *
 *	Description: provides a global interface for reading the map coordinate
 *  file, and storing all of the coordinate data for all map game objects,
 *  such as buildings, trees, lamps, spawn points, etc. This data can be
 *  access globally (static).
 */

#include "mapReader.h"
#include "mapSearcher.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;


// Constructor:
// Reads the coordinate file, and parses it. Populates the lists of
//  coordinates as dictated by the file. See documentation on the map
//  file for more information.
// TODO - make documentation for the map file.
MapReader::MapReader(const char *fileName){
    // TODO - make this global or returned from Terrain map object
    const int farX = 20400.0f;
	const int farY = 20400.0f;
	
	// Try to open the map coordinate file.
	ifstream mapfile(fileName);
	if(mapfile.fail()){
	    cerr << "ERROR: Cannot open map file." << endl;
	    return;
	}
	
	// If the file is readable, read it line by line.
	int curLine = 0;
    for(string line; getline(mapfile, line); ) {
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
        string ignore;
        istringstream lineParser(line);
        lineParser >> ignore;
        
        // If line is 'i' (image/texture directory path), read and continue
        if(type == 'i') {
            lineParser >> mapTextureDirectory;
            if(lineParser.fail()){
                cerr << "WARNING: Invalid entry in map file ("
                          << fileName << ", line " << curLine << "):" << endl
                          << "       " << line << endl;
                // reset directory
                mapTextureDirectory = "assets/textures/";
            }
            continue;
        }
        
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
            cerr << "WARNING: Invalid entry in map file ("
                      << fileName << ", line " << curLine << "):" << endl
                      << "       " << line << endl;
            continue;
        }
        
        // Create the Point, scaled to the map's scale
        Point pos;
        pos.X = (farX * coordX);
        pos.Y = (farY * coordY);
        
        // Push the coordinates to the correct list, based on type.
        switch(type){
            case 'b': // building
                buildingCoords.push_back(pos);
                break;
            case 'l': // street lamp
                streetLampCoords.push_back(pos);
                break;
            case 't': // tree
                treeCoords.push_back(pos);
                break;
            case 'f': // fire hydrant
                fireHydrantCoords.push_back(pos);
                break;
            case 'r': // road intersection
            {
                // create a new road intersection struct
                RoadIntersection intersection;
                intersection.X = pos.X;
                intersection.Y = pos.Y;
                intersection.id = roadID;
                roadIntersectionCoords.push_back(intersection);
            }
                break;
            case 'p': // path (connecting two road intersections)
            {
                int numIntersections = roadIntersectionCoords.size();
                
                // find road intersection w/ id1
                int index1;
                for(index1=0; index1<numIntersections; ++index1){
                    if(roadIntersectionCoords[index1].id == id1)
                        break;
                }
                // if index out of bounds, not found, so there was a problem.
                if(index1 >= numIntersections)
                    break;
                
                // find road intersection w/ id2
                int index2;
                for(index2=0; index2<numIntersections; ++index2){
                    if(roadIntersectionCoords[index2].id == id2)
                        break;
                }
                // if index out of bounds, not found, so there was a problem.
                if(index2 >= numIntersections)
                    break;
                
                // Assign intersections as interconnected (get references).
                roadIntersectionCoords[index1].connections.push_back
                    (&(roadIntersectionCoords[index2]));
                roadIntersectionCoords[index2].connections.push_back
                    (&(roadIntersectionCoords[index1]));
            }
                break;
            case 's': // spawnpoint (for enemies, vehicles, etc.)
            {
                switch(spawnType){
                    case 'v': // vehicle spawn point
                    {
                        // find road intersection with matching id
                        int numIntersections =
                            roadIntersectionCoords.size();
                        int index;
                        for(index=0; index<numIntersections; ++index) {
                            if(roadIntersectionCoords[index].id
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
                            &(roadIntersectionCoords[index]);
                        vehicleSpawnPoints.push_back(spawnPoint);
                    }
                        break;
                    case 'e': // enemy spawn point
                        enemySpawnPoints.push_back(pos);
                        break;
                    default:
                        break;
                }
            }
                break;
            default:
                cerr << "WARNING: Unknown coordinate type in map file ("
                      << fileName << ", line " << curLine << "):" << endl
                      << "       " << line << endl;
                break;
        }
    }
}


MapSearcher* MapReader::getMapSearcher(){
    return new MapSearcher(this);
}
