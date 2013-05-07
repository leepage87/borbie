/*	File: aStarPriorityQueue.h
 *	Authors: teamKillYourself
 *
 *	Description: a very crappy implementation of an interable priority queue
 *  to use for the A* map search algorithm.
 */

#ifndef A_STAR_PRIORITY_QUEUE_H
#define A_STAR_PRIORITY_QUEUE_H

// include cpp vector and algorithm for dealing with iteration
#include <vector>
#include <algorithm>


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
    
    // Returns the element index if an element exists; if not, returns -1
    int getElementIndex(T obj){
        int numItems = this->container.size();
        for(int i=0; i<numItems; ++i){
            if(this->container[i] == obj)
                return i;
        }
        return -1;
    }
    
    // Remove an element from the priority queue by type or index.
    //  Returns TRUE if something was removed, false if not found.
    bool remove(unsigned int index) {
        if(index < 0 || index >= this->container.size())
            return false;
        
        this->container.erase(this->container.begin() + index);
        return true;
    }
    
}; // end of AStarPriorityQueue class


#endif
