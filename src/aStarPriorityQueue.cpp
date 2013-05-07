/*	File: aStarPriotyQueue.cpp
 *	Authors: teamKillYourself
 *
 *	Description: inplementation for the AStarPriorityQueue object as defined by
 *  mapSearcher.h.
 */

#include "mapSearcher.h"

#include <iostream> // TODO - remove

using namespace std;


// enqueue into the priority queue, sorted by its value
/*template <class T> void AStarPriorityQueue<T>::enqueue(T obj){
    // loop through the container, and insert into the position as needed
    //  typename used for unknown type of iterator until instantiation
    typename vector<T>::iterator it = this->container.begin();
    for( ; it != this->container.end(); ++it){
        if(obj < (*it))
            break;
    }
    this->container.insert(it, obj);
}

// dequeue top priority item (front) from the priority queue, removing it from
//  the queue.
template <class T> T AStarPriorityQueue<T>::dequeue(){
    T obj = this->container[0];
    this->container->erase(this->container->begin());
    return obj;
}
    
// Returns TRUE if the given object is in this queue.
template <class T> bool AStarPriorityQueue<T>::contains(T obj){

}
    
// Remove an element from the priority queue by type or index.
//  Returns TRUE if something was removed, false if not found.
template <class T> bool AStarPriorityQueue<T>::remove(T obj){

}*/

/*template <class T> bool AStarPriorityQueue<T>::remove(int index){

}*/
