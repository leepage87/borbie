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


// Customized priority queue implemented for the A* algorithm. Note:
//  this queue is dumpy and inefficient, might need optimization.
// TEMPLATE: arbitrary object T: requires operators "<" and "=="
//  for comparisons.
template <class T> class AStarPriorityQueue {

  private:
    // internal under-the-hood queue container (iterable vector)
    std::vector<T> container;
    
  public:
    // enqueue into the priority queue, sorting it as it goes
    void enqueue(T obj){
        typename std::vector<T>::iterator it = this->container.begin();
        for( ; it != this->container.end(); ++it){
            if(obj < (*it))
                break;
        }
        this->container.insert(it, obj);
    }
    
    // dequeue from the priority queue (returns and removes the front element)
    T dequeue(){
        T obj = this->container[0];
        this->container.erase(this->container.begin());
        return obj;
    }
    
    // Returns TRUE if the given object is in this queue.
    bool contains(T obj){ return false; }
    
    // Gets a matching object from the queue
    //T getObject(T obj);
    
    // Remove an element from the priority queue by type or index.
    //  Returns TRUE if something was removed, false if not found.
    bool remove(T obj) { return false; }
    //bool remove(int index);
};


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
