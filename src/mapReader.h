/*	File: mapReader.h
 *	Authors: teamKillYourself
 *
 *	Description: provides a global interface for reading the map coordinate
 *  file, and storing all of the coordinate data for all map game objects,
 *  such as buildings, trees, lamps, spawn points, etc. This data can be
 *  access globally (static).
 */

#ifndef MAP_READER_H
#define MAP_READER_H


// include cpp standard library objects
#include <vector>
#include <string>


// Basic x, y point object.
struct Point {
    int X;
    int Y;
};

// Road object with connected nodes list.
struct RoadIntersection {
    int X;
    int Y;
    int id;
    std::vector<RoadIntersection *> connections;
};

// Basic x, y point, but attached with a reference to the road intersection
//  that the spawned object will first travel to in order to connect to the
//  road graph (network of interconnected road intersections).
struct RoadSpawnPoint {
    int X;
    int Y;
    RoadIntersection *connection;
};


// MapReader class:
class MapReader {


  public: // All static (globally accessible)
  
    // Map texture directory path:
    static std::string mapTextureDirectory;
  
    // Non-moving object coordinates:
	static std::vector<Point> buildingCoords;
	static std::vector<Point> streetLampCoords;
	static std::vector<Point> treeCoords;
	static std::vector<Point> fireHydrantCoords;
	static std::vector<RoadIntersection> roadIntersectionCoords;
	
	// Spawn point coordinates:
	static std::vector<Point> enemySpawnPoints;
	static std::vector<RoadSpawnPoint> vehicleSpawnPoints;
	
	
	// Function that reads a correctly-formatted coordinate file and
	//  adds all values to the static lists. This should be done before
	//  a game starts.
	static void readCoordFile(const char *fileName);
	
	// Clears out all of the coordinate lists so that they can be
	//  over-written. This should be done when a game finishes.
	static void clearMap();
	
	
}; // end of MapReader class


#endif
