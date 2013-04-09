/*	File: objectList.h
 *	Authors: idk your names
 *
 *	Description: this file contains the class declaration for the 
 *	class objectList. ObjectList is responsible for keeping track of all
 *  the objects that appear in the world, such as buildings, vehicles or NPCs,
 *	allowing you to add, get, and delete them.
 */

#ifndef OBJECT_LIST_H
#define OBJECT_LIST_H

// include irrlicht
#include <irrlicht.h>
#include <vector>
#include "game_object.h"

// objectList class (abstract):
class ObjectList {

  protected:
	irr::scene::ISceneManager *smgr;
	irr::video::IVideoDriver *driver;
	irr::IrrlichtDevice *device;
	irr::scene::IMetaTriangleSelector *metaTriSelector;
	//vector containing the objects
	std::vector<GameObject *> objList;

  public:
	// constructor: initializes a vector to hold each object's pointer
	ObjectList(	irr::scene::ISceneManager *smgr,
	irr::video::IVideoDriver *driver,
	irr::IrrlichtDevice *device,
	irr::scene::IMetaTriangleSelector *metaTriSelector);
	// destructor: automatically removes the node from the scene.
	~ObjectList();
	
	//takes a scene node pointer, finds it in the list, and returns the object
	GameObject* getObject(irr::scene::ISceneNode* pointer);
	void deleteObject(irr::scene::ISceneNode* pointer);
	void addObject(GameObject* object);
	
}; // end of ObjectList class


#endif
