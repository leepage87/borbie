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


// SearchNode object used to apply the A* algorithm to (instead of using the
//  RoadIntersection list).
class SearchNode {
  private:
    // associated road intersection object in MapReader
    RoadIntersection *intersection;
    
  public:
    SearchNode(RoadIntersection *intersection);
    
    // position and cost
    float X;
    float Y;
    float cost;
    
    // get a list of the neighbors of this node
    std::vector<SearchNode> getNeighbors();
    
    // overloaded operator for priority queue sorting
    bool operator()
        (const SearchNode& a, const SearchNode& b) const
    {
        return a.cost < b.cost;
    }
};


// MapSearcher class:
class MapSearcher {


  public: // All static (globally accessible)
  
    // Returns the closest RoadIntersection pointer from the given location.
    //  If none exist on the map, returns 0 (null).
    static RoadIntersection * getClosestRoadIntersection(
        irr::core::vector3df location);
    
    // Returns the distance (in game units) from between the two given X, Y
    //  coordinates.
    static float getDistance(float X1, float Y1, float X2, float Y2);
  
    // Find shortest path via roads from the first location to the second
    //  location.
    // RETURNS: a list of road intersection pointers that represent the path
    //  required to take, starting with the closest road intersection to the
    //  start location, and ending with the closest road intersection to the
    //  destination location.
    static std::vector<RoadIntersection> getShortestPath(
        irr::core::vector3df startPosition,
        irr::core::vector3df endPosition
    );
	
	
}; // end of MapSearcher class


#endif
