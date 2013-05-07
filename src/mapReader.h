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
    
    // comparison operator (check for equality)
    bool operator == (const RoadIntersection& other) const {
        return ((this->X == other.X) && (this->Y == other.Y));
    }
};

// Basic x, y point, but attached with a reference to the road intersection
//  that the spawned object will first travel to in order to connect to the
//  road graph (network of interconnected road intersections).
struct RoadSpawnPoint {
    int X;
    int Y;
    RoadIntersection *connection;
};


// Declare MapSearcher for returning pointer
class MapSearcher;


// MapReader class:
class MapReader {

  public:
    // constructor: read the file and populate the lists of coordinates
    MapReader(const char *fileName);
    
    // returns a MapSearcher object to iterate this map
    MapSearcher* getMapSearcher();
    
    // Map texture directory path:
    std::string mapTextureDirectory;
  
    // Non-moving object coordinates:
	std::vector<Point> buildingCoords;
	std::vector<Point> streetLampCoords;
	std::vector<Point> treeCoords;
	std::vector<Point> fireHydrantCoords;
	std::vector<RoadIntersection> roadIntersectionCoords;
	
	// Spawn point coordinates:
	std::vector<Point> enemySpawnPoints;
	std::vector<RoadSpawnPoint> vehicleSpawnPoints;
	
	
}; // end of MapReader class


#endif
