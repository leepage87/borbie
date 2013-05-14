/*********************************************************************
 *	File: mapSearcher.cpp
 *  Authors:  Richard Teammco, Lee Page, Jonathan Miodownik
 *
 *	Description: inplements an A* search algorithm that traverses the current
 *  map and determines the shortest path to a particular road intersection.
 *********************************************************************/


#include "mapSearcher.h"
#include "aStarPriorityQueue.h"
#include <cmath>
#include <algorithm>

#include <iostream> // TODO - remove

using namespace std;


/*********************************************************************
                     --- SearchNode Definitions ---
 *********************************************************************
 * Constructor:
 * Copies all of the important values of the intersection and creates
 * them as a SearchNode, initializing cost to 0 and the linked
 * intersection to the one provided.
 *********************************************************************/
SearchNode::SearchNode(RoadIntersection *intersection){
    this->X = intersection->X;
    this->Y = intersection->Y;
    this->cost = 0;
    this->intersection = intersection;
}


//  Returns a list of all neighbors connected to this node
vector<SearchNode *> SearchNode::getNeighbors(){
    vector<SearchNode *> neighbors;
    // traverse all connections of the associated intersection
    for(vector<RoadIntersection *>::iterator it =
            this->intersection->connections.begin();
        it != this->intersection->connections.end(); ++it)
    {
        // setup the neighbor node and add it to the list
        SearchNode *node = new SearchNode(*it);
        neighbors.push_back(node);
    }
    return neighbors;
}

/*********************************************************************
 * Return an Irrlicht version of a 3D vector resembling this node's position
 *********************************************************************/
irr::core::vector3df SearchNode::getPosition(){
    irr::core::vector3df pos;
    pos.X = this->X;
    pos.Y = 0;
    pos.Z = this->Y;
    return pos;
}


/*********************************************************************
                   --- MapSearcher Definitions --- 
 *********************************************************************
 * Constructor: Keeps track of the MapReader pointer that built
 *              this searcher.
 *********************************************************************/
MapSearcher::MapSearcher(MapReader *mapReader){
    this->mapReader = mapReader;
}

/*********************************************************************
 * Gets the closest RoadIntersection pointer from the given location.
 * If none exist on the map, returns an uninitialized RoadIntersection.
 * Param: location - the current location
 * Returns: The closest roadIntersection point
 *********************************************************************/
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

/*********************************************************************
 * Returns the distance (in game units) from between the two
 * given X, Y coordinates.
 * Param: X1 - X coord 1
 * Param: Y1 - Y coord 1
 * Param: X2 - X coord 2
 * Param: Y2 - Y coord 2
 * Returns: distance between (X1,Y1) and (X2,Y2)
 *********************************************************************/
float MapSearcher::getDistance(float X1, float Y1, float X2, float Y2){
    return sqrt((X2-X1)*(X2-X1) + (Y2-Y1)*(Y2-Y1));
}

/*********************************************************************
 * Find shortest path via roads from the first location to the second
 * location.
 * Returns: a list of road intersection pointers that represent the path
 *          required to take, starting with the closest road intersection
 *          to the start location, and ending with the closest road
 *          intersection to the destination location. If no path is available,
 *          or the end point is already close enough to the  starting point
 *          (where the start and end road intersections would be the
 *          same), returns an empty list.
 *********************************************************************/
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
    //path.push_back(*startIntersection);
    
    // if already at destination, just return start intersection
    if(startIntersection == endIntersection)
        return path;
    
    // get first and last (final) start nodes
    SearchNode *start = new SearchNode(startIntersection);
    SearchNode *end = new SearchNode(endIntersection);
    
    // set up the frontier priority queue with the first node
    AStarPriorityQueue<SearchNode *> frontier;
    frontier.enqueue(start);
    
    // keep track of visited nodes and in parallel a list of the queue's nodes
    //  for easy traversal with iterators when needed
    vector<SearchNode *> visited;
    
    // run A* search until a path is found, or until the queue runs out,
    //  in which case this search failed.
    bool found = false;
    while(frontier.size() > 0 && !found){
        // pop cur from top of frontier
        SearchNode *cur = frontier.dequeue();
        
        // add cur (dereferenced) to list of visited nodes
        visited.push_back(cur);
        
        // traverse all neighbors of this node
        vector<SearchNode *> neighbors = cur->getNeighbors();
        for(vector<SearchNode *>::iterator it = neighbors.begin();
            it != neighbors.end(); ++it)
        {
            // set neighbors previous to current's intersection
            (*it)->previous = cur;
            
            // find distance to neighbor from current node
            int distToNeighbor = this->getDistance(
                cur->X, cur->Y, (*it)->X, (*it)->Y);
            
            // get best distance to end node (heuristic)
            int heuristic = this->getDistance(
                end->X, end->Y, (*it)->X, (*it)->Y);
            
            // estimate best case cost to path
            int estimatedCost = cur->cost + distToNeighbor + heuristic;
            
            // try to find the current neighbor in visited list
            int numVisited = visited.size();
            int visitedIndex = 0;
            for( ; visitedIndex<numVisited; ++visitedIndex){
                if((*(visited[visitedIndex])) == (*(*it)))
                    break;
            }
            //vector<SearchNode>::iterator inVisitedIterator =
            //    find(visited.begin(), visited.end(), *(*it));
            
            // try to find the current neighbor in the frontier (-1 if not found)
            int frontierIndex = frontier.getElementIndex((*it));
            
            // if neighbor NOT in frontier and NOT yet visited ...
            if(visitedIndex >= numVisited && frontierIndex == -1) {
                // ... if we found the end node, we're done!
                if((*(*it)) == (*end)){
                    end = (*it);
                    found = true;
                    break;
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
                SearchNode *inFrontier = frontier.get(frontierIndex);
                if((*it)->cost < inFrontier->cost){
                    SearchNode *old = frontier.get(frontierIndex);
                    // if removed from frontier, add the better cost node
                    if(frontier.remove(frontierIndex)){
                        frontier.enqueue(*it);
                        // clean up memory (delete old node)
                        delete old;
                    }
                }
            }
        }
    }
    
    int frontierSize = frontier.size();
    int visitedSize = visited.size();
    
    // if frontier is empty, no path was found, so return the empty list
    if(frontierSize == 0)
        return path;
    
    // Backstep through the path as constructed and push all of the
    //  intersections in order from last to first into the path list.
    SearchNode *cur = end;
    while((*(cur->previous)) != (*start)){
        path.push_back(*(cur->intersection));
        cur = cur->previous;
    }
    path.push_back(*(cur->intersection)); // push the start node
    
    // reverse path to return it (since it is currently in backwards order)
    reverse(path.begin(), path.end());
    
    // clean up memory: delete all objects in frontier and visited list
    for(int i=0; i<frontierSize; i++)
        delete frontier.get(i);
    for(int i=0; i<visitedSize; i++)
        delete visited[i];
    
    return path;
}




























