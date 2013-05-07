/*	File: mapSearcher.cpp
 *	Authors: teamKillYourself
 *
 *	Description: inplements an A* search algorithm that traverses the current
 *  map and determines the shortest path to a particular road intersection.
 */

#include "mapSearcher.h"
#include "aStarPriorityQueue.h"
#include <cmath>
#include <algorithm>

#include <iostream> // TODO - remove

using namespace std;



/*** --- SearchNode Definitions --- ***/

// Constructor:
//  Copies all of the important values of the intersection and creates
//  them as a SearchNode, initializing cost to 0 and the linked intersection
//  to the one provided.
SearchNode::SearchNode(RoadIntersection *intersection){
    this->X = intersection->X;
    this->Y = intersection->Y;
    this->cost = 0;
    this->intersection = intersection;
    this->previous = 0;
}


//  Returns a list of all neighbors connected to this node
vector<SearchNode> SearchNode::getNeighbors(){
    vector<SearchNode> neighbors;
    // traverse all connections of the associated intersection
    for(vector<RoadIntersection *>::iterator it =
            this->intersection->connections.begin();
        it != this->intersection->connections.end(); ++it)
    {
        // setup the neighbor node and add it to the list
        SearchNode node(*it);
        neighbors.push_back(node);
    }
    return neighbors;
}


// Return an Irrlicht version of a 3D vector resembling this node's position
irr::core::vector3df SearchNode::getPosition(){
    irr::core::vector3df pos;
    pos.X = this->X;
    pos.Y = 0;
    pos.Z = this->Y;
    return pos;
}



/*** --- MapSearcher Definitions --- ***/


// Constructor: keeps track of the MapReader pointer that built this searcher.
MapSearcher::MapSearcher(MapReader *mapReader){
    this->mapReader = mapReader;
}


// Returns the closest RoadIntersection pointer from the given location.
//  If none exist on the map, returns an uninitialized RoadIntersection.
RoadIntersection * MapSearcher::getClosestRoadIntersection(
    irr::core::vector3df location)
{
    // start with no good distance or path
    int bestDistance = -1;
    RoadIntersection *closest = 0;
    
    // loop through each intersection; if one is closer, set closest to that
    //  intersection.
    for(vector<RoadIntersection>::iterator it =
            this->mapReader->roadIntersectionCoords.begin();
        it != this->mapReader->roadIntersectionCoords.end(); ++it)
    {
        int curDistance =
            MapSearcher::getDistance(location.X, location.Z, (*it).X, (*it).Y);
        
        // if distance is not 0 (i.e. not the same node), if it's closer (or
        //  the first other node seen), use it as the closest distance.
        if(curDistance != 0 && (curDistance < bestDistance || closest == 0)){
            closest = &(*it);
            bestDistance = curDistance;
        }
    }
    
    return closest;
}


// Returns the distance (in game units) from between the two given X, Y
//  coordinates.
float MapSearcher::getDistance(float X1, float Y1, float X2, float Y2){
    return sqrt((X2-X1)*(X2-X1) + (Y2-Y1)*(Y2-Y1));
}


// Find shortest path via roads from the first location to the second
//  location.
// RETURNS: a list of road intersection pointers that represent the path
//  required to take, starting with the closest road intersection to the
//  start location, and ending with the closest road intersection to the
//  destination location.
std::vector<RoadIntersection> MapSearcher::getShortestPath(
    irr::core::vector3df startPosition,
    irr::core::vector3df endPosition)
{
    // get the closest road intersection from the start/end location:
    RoadIntersection *startIntersection =
        MapSearcher::getClosestRoadIntersection(startPosition);
    RoadIntersection *endIntersection =
        MapSearcher::getClosestRoadIntersection(endPosition);
    
    // create initial list with just the first node in it
    vector<RoadIntersection> path;
    //path.push_back(*start);
    
    // if already at destination, just return start intersection
    if(startIntersection == endIntersection)
        return path;
    
    // get first and last (final) start nodes
    SearchNode start(startIntersection);
    SearchNode end(endIntersection);
    
    // set up the frontier priority queue with the first node
    AStarPriorityQueue<SearchNode> frontier;
    frontier.enqueue(start);
    
    // keep track of visited nodes and in parallel a list of the queue's nodes
    //  for easy traversal with iterators when needed
    vector<SearchNode> visited;
    
    // run A* search until a path is found, or until the queue runs out,
    //  in which case this search failed.
    while(frontier.size() > 0){
        // pop cur from top of frontier
        SearchNode cur = frontier.dequeue();
        
        // remove cur from the unsorted frontier list
        
        
        // add cur to list of visited nodes
        visited.push_back(cur);
        
        // traverse all neighbors of this node
        vector<SearchNode> neighbors = cur.getNeighbors();
        for(vector<SearchNode>::iterator it = neighbors.begin();
            it != neighbors.end(); ++it)
        {
            // set neighbors previous to current's intersection
            (*it).previous = cur.intersection;
            
            // find distance to neighbor from current node
            int distToNeighbor = this->getDistance(cur.X, cur.Y, (*it).X, (*it).Y);
            
            // get best distance to end node (heuristic)
            int heuristic = this->getDistance(end.X, end.Y, (*it).X, (*it).Y);
            
            // estimate best case cost to path
            int estimatedCost = cur.cost + distToNeighbor + heuristic;
            
            // try to find the current neighbor in visited list
            vector<SearchNode>::iterator inVisitedIterator =
                find(visited.begin(), visited.end(), (*it));
            
            // try to find the current neighbor in the frontier (-1 if not found)
            int frontierIndex = frontier.getElementIndex((*it));
            
            // if neighbor NOT in frontier and NOT yet visited ...
            if(inVisitedIterator == visited.end() && frontierIndex == -1) {
                // ... if we found the end node, we're done!
                if((*it) == end){
                    cout << "Found" << endl; // done TODO
                }
                // ... otherwise, push the neighbor into the frontier.
                else {
                    frontier.enqueue(*it);
                }
            }
            
            // otherwise if neighbor IS in frontier ...
            else if(frontierIndex >= 0){
                // ... if cost is lower than the one already in frontier,
                //  replace it with the node of lower cost.
                SearchNode inFrontier = frontier.get(frontierIndex);
                if((*it).cost < inFrontier.cost){
                    if(frontier.remove(frontierIndex))
                        frontier.enqueue(*it);
                }
            }
        }
    }
    
    return path;
}




























