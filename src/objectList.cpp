/*	File: objectList.cpp
 *	Authors: idk your names
 *
 *	Description: this file contains the class objectList.
 *  ObjectList is responsible for keeping track of all
 *  the objects that appear in the world, such as buildings, vehicles or NPCs,
 *	allowing you to add, get, and delete them.
 *  It also holds 
 */
#include <iostream>
//#include <stdlib.h> ???
#include <algorithm>
#include "objectList.h"
#include "gameInstance.h"



using namespace irr;
using namespace scene;
using namespace video;




ObjectList::ObjectList(
	IMetaTriangleSelector *metaTriSelector,
	GameInstance *gameInstance)
{
	this->smgr = gameInstance->getSceneManager();
	this->driver = gameInstance->getDriver();
	this->device = gameInstance->getDevice();
	this->metaTriSelector = metaTriSelector;
	this->gameInstance = gameInstance;
}

// delete all of the objects
ObjectList::~ObjectList(){
	for(std::vector<GameObject *>::iterator it = objList.begin();
		it != objList.end(); ++it)
	{
	    // null its container so that it doesn't try to remove itself from
	    //  the list and screw up the iteration, and then delete it.
	    (*it)->setContainer(0);
		delete (*it);
	}
}

//Adds an object to the list for tracking purposes, and assigns it a pointer
//  back to this list for self-removal.
void ObjectList::addObject(GameObject* object){
	this->objList.push_back(object);
	object->setContainer(this);
	object->setMetaTriSelector(this->metaTriSelector);
}

//Takes a pointer and returns the associated object if its found
GameObject* ObjectList::getObject(irr::scene::ISceneNode* pointer){
	for(std::vector<GameObject *>::iterator it = objList.begin();
		it != objList.end(); ++it){
		if ((*it)->getNode() == pointer) {//pointer match, return this object
			return *it;
	    }
	}//no match found
	return 0;
}

// Remove an object from this list using the Irrlicht node pointer. If no
//  matching object exists, does nothing.
void ObjectList::removeObject(irr::scene::ISceneNode* pointer){
    for(std::vector<GameObject *>::iterator it = objList.begin();
		it != objList.end(); ++it){
		if ((*it)->getNode() == pointer) {//pointer match, delete this object
            this->objList.erase(it);
            //delete (*it);
            break;
	    }
	}
}


// Remove an object from this list using the object pointer. If no matching
//  object exists, does nothing.
void ObjectList::removeObject(GameObject *pointer) {
    std::vector<GameObject *>::iterator it;
    it = std::find(this->objList.begin(), this->objList.end(), pointer);
    if(it != this->objList.end()){
        //delete (*it);
        this->objList.erase(it);
    }
}
