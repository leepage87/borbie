/*
* Lee Page
* ambientLight.h
* CIS 395 
*/
#ifndef WORLD_LIGHT_H
#define WORLD_LIGHT_H

#include <string>
#include <irrlicht.h>

class WorldLight {
private:

	irr::scene::ILightSceneNode *sun;
	
public:
	// constructor
	WorldLight(irr::scene::ISceneManager * _smgr);

	irr::scene::ILightSceneNode* getNode() { return sun; }

};

#endif
