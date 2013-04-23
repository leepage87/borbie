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
    int x;
    int y;
};

// Road object with connected nodes list.
struct RoadIntersection {
    int x;
    int y;
    int id;
    std::vector<RoadIntersection> connections;
};


// MapReader class:
class MapReader {


  public: // All static (globally accessible)
	static std::vector<Point> buildingCoords;
	static std::vector<Point> streetLampCoords;
	static std::vector<Point> treeCoords;
	static std::vector<Point> fireHydrantCoords;
	static std::vector<RoadIntersection> roadIntersectionCoords;
	
	static void readCoordFile(const char *fileName);
	
	
}; // end of MapReader class


#endif
