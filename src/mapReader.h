/*	File: mapReader.h
 *	Authors: idk your names
 *
 *	Description: this file contains the class declaration of the
 *	buildings list object. The building list object contains a
 *	function for constructing all buildings and placing them into the
 *	scene automatically.
 */

#ifndef MAP_READER_H
#define MAP_READER_H


// include cpp standard library objects
#include <vector>


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
	//  adds all values to the static lists.
	static void readCoordFile(const char *fileName);
	
	
}; // end of MapReader class


#endif
