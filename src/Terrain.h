/*
* Lee Page
* Terrain object w/ collision (Terrain.h)
* CIS 395 
*/
#ifndef TERRAIN_H
#define TERRAIN_H

#include <string>
#include <irrlicht.h>

class Terrain {
private:

	irr::video::IVideoDriver * driver;
	irr::scene::ISceneManager * smgr;
	irr::scene::ICameraSceneNode* camera;
public:
	irr::scene::ITerrainSceneNode * terrain;

	Terrain(irr::video::IVideoDriver * driver, irr::scene::ISceneManager * smgr, irr::scene::ICameraSceneNode* camera);

	irr::scene::ITerrainSceneNode* getNode() { return terrain; }
};
#endif
