/*
* Lee Page
* Terrain object w/ collision (Terrain.cpp)
* CIS 395 
*/

#include "terrain.h"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;


#define s2( name ) #name
#define stringify( name ) s2( name )

Terrain::Terrain(IVideoDriver * _driver, ISceneManager * _smgr) {
	driver = _driver;
	smgr = _smgr;
	terrainNode = _smgr->addTerrainSceneNode(
		"assets/map/valleyHeightMap.bmp",
		0,					// parent node
		-1,					// node idsssssssss
		core::vector3df(0.f, 0.f, 0.f),		// position
		core::vector3df(0.f, 0.f, 0.f),		// rotation
		core::vector3df(
            BORBIE_TERRAIN_SCALE,
            4.4f,
            BORBIE_TERRAIN_SCALE),	// scale
		video::SColor ( 255, 255, 255, 255 ),	// vertexColor
		5,					// maxLOD
		scene::ETPS_17,				// patchSize
		4					// smoothFactor
		);

	
	terrainNode->setMaterialFlag(video::EMF_LIGHTING, true);

	terrainNode->setMaterialTexture(0,
		_driver->getTexture("assets/map/groundTexture.jpg"));
	terrainNode->setMaterialType(video::EMT_DETAIL_MAP);
	terrainNode->scaleTexture(1.0f, 20.0f);
	
	// setup collision
	ITriangleSelector* selector =
		smgr->createTerrainTriangleSelector(terrainNode, 0);
	terrainNode->setTriangleSelector(selector);
	this->triSelector = selector;
}
































