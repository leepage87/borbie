/*
* Lee Page
* Terrain object w/ collision (Terrain.cpp)
* CIS 395 
*/

#include "terrain.h"
#include "castRay.h"

#include <iostream>

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

//const core::vector3df SIZE = (10.0f,10.0f, 10.0f);
#define s2( name ) #name
#define stringify( name ) s2( name )

Terrain::Terrain(IVideoDriver * _driver, ISceneManager * _smgr, irr::scene::IMetaTriangleSelector *metaTriSelector) {
	driver = _driver;
	smgr = _smgr;
    this->metaTriSelector = metaTriSelector;

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

    // make this node NOT pickable :( What a loser LOL!
    terrainNode->setID(IDFlag_IsNotPickable);
	
	terrainNode->setMaterialFlag(video::EMF_LIGHTING, true);
 
	terrainNode->setMaterialTexture(0,
		_driver->getTexture("assets/map/groundTexture.jpg"));
	terrainNode->setMaterialType(video::EMT_DETAIL_MAP);
	terrainNode->scaleTexture(1.0f, 20.0f);
  
    vector3df edges[8];
    aabbox3df bounds = terrainNode->getBoundingBox();
    bounds.getEdges(edges);
    std::cout << "EDGES-----------------------------------EDGES" << std::endl;
    for(int i=0; i<8; ++i){
        float x = edges[i].X;
        float y = edges[i].Y;
        float z = edges[i].Z;
        std::cout << "Edge # " << i << " -- " << x << ", " << y << ", " << z
            << std::endl;
    }

  // setup collision
	ITriangleSelector* selector =
		smgr->createTerrainTriangleSelector(terrainNode, 0);
	terrainNode->setTriangleSelector(selector);
	this->triSelector = selector;
   
  //add invisible walls
  IMeshSceneNode * southWall = smgr->addCubeSceneNode(100000, 0 , -1, vector3df(2000, 500,2000), vector3df(0,90,0), vector3df(1, 1, 0.0001));
  IMeshSceneNode * eastWall = smgr->addCubeSceneNode(100000, 0 , -1, vector3df(2000, 500,2000), vector3df(0,0,0), vector3df(1, 1, 0.0001));
  IMeshSceneNode * westWall = smgr->addCubeSceneNode(100000, 0 , -1, vector3df(2000, 500,18500), vector3df(0,0,0), vector3df(1, 1, 0.0001));
  IMeshSceneNode * northWall = smgr->addCubeSceneNode(100000, 0 , -1, vector3df(18000, 500,2000), vector3df(0,90,0), vector3df(1, 1, 0.0001));
  southWall->setVisible(false);
  northWall->setVisible(false);
  eastWall->setVisible(false);
  westWall->setVisible(false);
	
  
  applyCollision(southWall);
  applyCollision(northWall);
  applyCollision(westWall);
  applyCollision(eastWall);
  
  
  // add its triangles to the global collision meta selector
//  southWall->setTriangleSelector(wallSelector);
//	wallSelector->drop();
//  metaTriSelector->addTriangleSelector(southWall->getTriangleSelector());
	
 }

//helper functions
void Terrain::applyCollision(IMeshSceneNode* wall)
{
	
  wallSelector =
		smgr->createTriangleSelectorFromBoundingBox(wall);
  
  wall->setTriangleSelector(wallSelector);
	wallSelector->drop();
  metaTriSelector->addTriangleSelector(wall->getTriangleSelector());
	

}

























