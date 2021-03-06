/*********************************************************************
 * File:     terrain.h
 * Authors:  Richard Teammco, Lee Page, Jonathan Miodownik
 * Function: This is the header file for terrain.cpp
 *********************************************************************/
#ifndef TERRAIN_H
#define TERRAIN_H

#include <string>
#include <irrlicht.h>

// terrain scale (1 scale unit = 500 game units)
#define BORBIE_TERRAIN_SCALE 40.0f


// Terrain class:
class Terrain {
private:

	irr::video::IVideoDriver *driver;
	irr::scene::ISceneManager *smgr;
	irr::scene::ITerrainSceneNode *terrainNode;
	irr::scene::ITriangleSelector *triSelector;
  irr::scene::IMetaTriangleSelector *metaTriSelector;	
  irr::scene::ITriangleSelector *wallSelector;

  void applyCollision(irr::scene::IMeshSceneNode *wall);

public:
	// constructor
	Terrain(irr::video::IVideoDriver * driver,
			irr::scene::ISceneManager * smgr, irr::scene::IMetaTriangleSelector *metaTriSelector);

	// returns the terrain node
	irr::scene::ITerrainSceneNode* getNode() { return terrainNode; }
	
	// const means it doesn't change anything
	irr::scene::ITriangleSelector* getTriSelector() { return triSelector; }
}; // end of Terrain class.


#endif
