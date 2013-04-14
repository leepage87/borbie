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
#include "game_object.h"
#include "gameInstance.h"



using namespace irr;
using namespace scene;
using namespace video;




ObjectList::ObjectList(	ISceneManager *smgr,
	IVideoDriver *driver,
	IrrlichtDevice *device,
	IMetaTriangleSelector *metaTriSelector,
	GameInstance *gameInstance){
	this->smgr = smgr;
	this->driver = driver;
	this->device = device;
	this->metaTriSelector = metaTriSelector;
	this->gameInstance = gameInstance;
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

// delete object using the Irrlicht node pointer
void ObjectList::deleteObject(irr::scene::ISceneNode* pointer){
    for(std::vector<GameObject *>::iterator it = objList.begin();
		it != objList.end(); ++it){
		if ((*it)->getNode() == pointer) {//pointer match, delete this object
            this->objList.erase(it);
            delete (*it);			
	    }
	}
}


// delete object using the object pointer
void ObjectList::deleteObject(GameObject *pointer) {
    std::vector<GameObject *>::iterator it;
    it = std::find(this->objList.begin(), this->objList.end(), pointer);
    if(it != this->objList.end()){
        delete (*it);
        this->objList.erase(it);
    }
}
