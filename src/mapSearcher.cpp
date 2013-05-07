/*	File: mapSearcher.cpp
 *	Authors: teamKillYourself
 *
 *	Description: inplements an A* search algorithm that traverses the current
 *  map and determines the shortest path to a particular road intersection.
 */

#include "mapSearcher.h"
#include <cmath>
#include <queue>

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



/*** --- MapSearcher Definitions --- ***/

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
            MapReader::roadIntersectionCoords.begin();
        it != MapReader::roadIntersectionCoords.end(); ++it)
    {
        int curDistance =
            MapSearcher::getDistance(location.X, location.Z, (*it).X, (*it).Y);
        if(curDistance < bestDistance || closest == 0){
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
    RoadIntersection *start =
        MapSearcher::getClosestRoadIntersection(startPosition);
    RoadIntersection *end =
        MapSearcher::getClosestRoadIntersection(endPosition);
    
    // create initial list with just the first node in it
    vector<RoadIntersection> path;
    //path.push_back(*start);
    
    // if already at destination, just return start intersection
    if(start == end)
        return path;
    
    // copy the RoadIntersections into a SearchNode list
    /*vector<SearchNode> intersections;
    for(vector<RoadIntersection>::iterator it =
            MapReader::roadIntersectionCoords.begin();
        it != MapReader::roadIntersectionCoords.end(); ++it)
    {
        SearchNode node;
        node.X = (*it).X;
        node.Y = (*it).Y;
        node.cost = 0;
        
        for(vector<RoadIntersection *>::iterator conn =
                (*it).conn.begin();
            conn != (*it).conn.end(); ++conn)
        {
            SearchNode neighbor;
            neighbor.X = conn->X;
            conn->X
        }
        
        intersections.push_back(node);
    }
    
    vector<RoadIntersection> intersections(
        MapReader::roadIntersectionCoords.begin(),
        MapReader::roadIntersectionCoords.end());
    
    
    priority_queue<RoadIntersection> frontier;
    vector<RoadIntersection> visited;

    start->cost = 0;    
    frontier.push(start);
    
    while(frontier.size() > 0){
        RoadIntersection cur = frontier.top();
        visited.push_back(cur);
        
        //cur->connections
        // traverse all neighbors
        for(std::vector<RoadIntersection>::iterator it =
            cur->connections.begin();
            it != cur->connections.end(); ++it)
        {
            int distToNeighbor = 0;//TODO
            int estimatedCost = cu.>cost + distToNeighbor;
        }
    }*/
    
    return path;
}




























