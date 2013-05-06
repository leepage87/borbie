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
#include "gameObject.h"


// declare GameInstance to use its pointer
class GameInstance;


// objectList class (abstract):
class ObjectList {

    friend class GameObject;
    friend class GameInstance;

  protected:
    // Irrlicht objects
	irr::scene::ISceneManager *smgr;
	irr::video::IVideoDriver *driver;
	irr::IrrlichtDevice *device;
	irr::scene::IMetaTriangleSelector *metaTriSelector;
	
	// pointer to the active GameInstance
	GameInstance *gameInstance;
	
	//vector containing the objects (e.g. vehicles, buildings)
	std::vector<GameObject *> objList;

  public:
	// constructor: initializes a vector to hold each object's pointer
	ObjectList(
        irr::scene::IMetaTriangleSelector *metaTriSelector,
        GameInstance *gameInstance);
	// destructor: automatically removes the node from the scene.
	~ObjectList();
	
	//takes a scene node pointer, finds it in the list, and returns the object
	virtual GameObject* getObject(irr::scene::ISceneNode* pointer);
	
	// delete objects from the list (and from Irrlicht) using either the
	//  Irrlicht ISceneNode pointer or the GameObject pointer
	virtual void removeObject(irr::scene::ISceneNode* pointer);
	virtual void removeObject(GameObject *pointer);
	
	// add an object to the list of objects containted in this list
	virtual void addObject(GameObject* object);
	
	// generate the objects in the world map (pure virtual)
	virtual void generateObjects() = 0;
	
	
}; // end of ObjectList class


#endif
