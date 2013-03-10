/*	File: buildingInstance.h
 *	Authors: idk your names
 *
 *	Description: this file contains the class declaration of the
 *	buildings list object. The building object provides a specification
 *	of the abstract GameObject class and contains functions and variables
 *	specific to destructable buildings placed within the environment.
 */

#ifndef BUILDINGS_H
#define BUILDINGS_H


// include irrlicht
#include <irrlicht.h>

// include building header
#include "buildingInstance.h"


// Buildings class:
class Buildings {

  public:
	void makeBuilding(unsigned int type,
		float xPos, float yPos, float zPos);
	
	
}; // end of Buildings class


#endif
