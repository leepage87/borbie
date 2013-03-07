/*
* Lee Page
* ambientLight.h
* CIS 395 
*/
#ifndef AMBIENTLIGHT_H
#define AMBIENTLIGHT_H

#include <string>
#include <irrlicht.h>

class ambientLight {
private:

	irr::scene::ILightSceneNode *sun;
	
public:
	// constructor
	ambientLight(irr::scene::ISceneManager * _smgr);

	irr::scene::ILightSceneNode* getNode() { return sun; }

};
#endif
