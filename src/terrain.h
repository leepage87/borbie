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

	irr::video::IVideoDriver *driver;
	irr::scene::ISceneManager *smgr;
	irr::scene::ITerrainSceneNode *terrainNode;
	irr::scene::ITriangleSelector *triSelector;
	
public:
	// constructor
	Terrain(irr::video::IVideoDriver * driver,
			irr::scene::ISceneManager * smgr);

	// returns the terrain node
	irr::scene::ITerrainSceneNode* getNode() { return terrainNode; }
	
	// const means it doesn't change anything
	irr::scene::ITriangleSelector* getTriSelector() { return triSelector; }
};


#endif
