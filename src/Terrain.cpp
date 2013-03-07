/*
* Lee Page
* Terrain object w/ collision (Terrain.cpp)
* CIS 395 
*/

#include "Terrain.h"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;


#define s2( name ) #name
#define stringify( name ) s2( name )

Terrain::Terrain(IVideoDriver * _driver, ISceneManager * _smgr, ICameraSceneNode* _camera) {
	driver = _driver;
	smgr = _smgr;
	camera = _camera;
	terrain = _smgr->addTerrainSceneNode(
		"assets/textures/valleyHeightMap.bmp",
		0,					// parent node
		-1,					// node id
		core::vector3df(0.f, 0.f, 0.f),		// position
		core::vector3df(0.f, 0.f, 0.f),		// rotation
		core::vector3df(40.f, 4.4f, 40.f),	// scale
		video::SColor ( 255, 255, 255, 255 ),	// vertexColor
		5,					// maxLOD
		scene::ETPS_17,				// patchSize
		4					// smoothFactor
		);

	
	//set lighting to true after lights have been added
	terrain->setMaterialFlag(video::EMF_LIGHTING, false);

	terrain->setMaterialTexture(0,
		_driver->getTexture("assets/textures/groundTexture.jpg"));
	terrain->setMaterialType(video::EMT_DETAIL_MAP);
	terrain->scaleTexture(1.0f, 20.0f);
	
	// setup collision
	ITriangleSelector* selector =
		smgr->createTerrainTriangleSelector(this->terrainNode, 0);
	terrain->setTriangleSelector(selector);
	this->triSelector = selector;
}
































