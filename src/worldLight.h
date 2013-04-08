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
	irr::scene::ISceneManager *smgr;
	
public:
	// constructor
	WorldLight(irr::scene::ISceneManager * _smgr);

	irr::scene::ILightSceneNode* getNode() { return sun; }
	
	// sets the world's ambiant light (RGB from 0 to 255)
	void setAmbientLight(unsigned int r, unsigned int g, unsigned int b);

};

#endif
