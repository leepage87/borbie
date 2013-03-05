/*
* Lee Page
* Sky object (sky.h)
* CIS 395 
*/
#ifndef TERRAIN_H
#define TERRAIN_H

#include <string>
#include <irrlicht.h>

class sky {
private:

	irr::video::IVideoDriver * driver;
	irr::scene::ISceneManager * smgr;
	irr::scene::ICameraSceneNode* camera;
public:
	irr::scene::ISceneNode * sky;

	sky(irr::scene::ISceneManager * smgr);

	irr::scene::ISceneNode* getNode() { return sky; }
};
#endif
