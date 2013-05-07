/*	File: mapSearcher.h
 *	Authors: teamKillYourself
 *
 *	Description: inplements an A* search algorithm that traverses the current
 *  map and determines the shortest path to a particular road intersection.
 */

#ifndef MAP_SEARCHER_H
#define MAP_SEARCHER_H

// include irrlicht and map reader for position information
#include <irrlicht.h>
#include "mapReader.h"

// include cpp vector to return a list of RoadIntersections.
#include <vector>
#include <algorithm>


// SearchNode object used to apply the A* algorithm to (instead of using the
//  RoadIntersection list).
class SearchNode {
  private:
    
  public:
    SearchNode(RoadIntersection *intersection);
    
    // position and cost
    float X;
    float Y;
    float cost;
    
    // associated road intersection object in MapReader, and the previous
    RoadIntersection *intersection;
    RoadIntersection *previous;
    
    // get a list of the neighbors of this node
    std::vector<SearchNode> getNeighbors();
    
    // get an irrlicht version of the position vector
    irr::core::vector3df getPosition();
    
    // overloaded compare < operator for priority queue sorting
    bool operator < (const SearchNode& other) const {
        return this->cost < other.cost;
    }
    
    // overloaded compare == operator for list removal/getter
    bool operator == (const SearchNode& other) const {
        return this->intersection == other.intersection;
    }
};


// MapSearcher class:
class MapSearcher {

  private:
    MapReader *mapReader;

  public:
    // constructor: keeps track of a MapReader object pointer
    MapSearcher(MapReader *mapReader);
    
    // Returns the closest RoadIntersection pointer from the given location.
    //  If none exist on the map, returns 0 (null).
    RoadIntersection * getClosestRoadIntersection(
        irr::core::vector3df location);
    
    // Returns the distance (in game units) from between the two given X, Y
    //  coordinates.
    float getDistance(float X1, float Y1, float X2, float Y2);
  
    // Find shortest path via roads from the first location to the second
    //  location.
    // RETURNS: a list of road intersection pointers that represent the path
    //  required to take, starting with the closest road intersection to the
    //  start location, and ending with the closest road intersection to the
    //  destination location.
    std::vector<RoadIntersection> getShortestPath(
        irr::core::vector3df startPosition,
        irr::core::vector3df endPosition
    );
	
	
}; // end of MapSearcher class


#endif
