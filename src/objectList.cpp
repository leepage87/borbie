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
#include <stdlib.h>
#include "objectList.h"
#include "game_object.h"



using namespace irr;
using namespace scene;
using namespace video;




ObjectList::ObjectList(	ISceneManager *smgr,
	IVideoDriver *driver,
	IrrlichtDevice *device,
	IMetaTriangleSelector *metaTriSelector){
	this->smgr = smgr;
	this->driver = driver;
	this->device = device;
	this->metaTriSelector = metaTriSelector;
}

// delete all of the objects
ObjectList::~ObjectList(){
	for(std::vector<GameObject *>::iterator it = objList.begin();
		it != objList.end(); ++it)
	{
		delete (*it);
	}
}
//Adds an object to the list for tracking purposes
void ObjectList::addObject(GameObject* object){
	this->objList.push_back(object);
}

//Takes a pointer and returns the associated object if its found
GameObject* ObjectList::getObject(irr::scene::ISceneNode* pointer){
	for(std::vector<GameObject *>::iterator it = objList.begin();
		it != objList.end(); ++it){
		if ((*it)->getNode() == pointer) {//pointer match, return this object
		    std::cout << "about to return" << std::endl;
			return *it;
	    }
	}//no match found
	return 0;
}

void ObjectList::deleteObject(irr::scene::ISceneNode* pointer){
for(std::vector<GameObject *>::iterator it = objList.begin();
		it != objList.end(); ++it){
		if ((*it)->getNode() == pointer) {//pointer match, delete this object
		    std::cout << "Deleting object" << std::endl;
        this->objList.erase(it);
        delete (*it);			
	    }
	}
}



