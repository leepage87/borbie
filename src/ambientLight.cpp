/*
* Lee Page
* ambientLight.cpp
* CIS 395 
*/

#include "ambientLight.h"

using namespace irr;

using namespace core;
using namespace video;
using namespace io;


#define s2( name ) #name
#define stringify( name ) s2( name )

ambientLight::ambientLight(scene::ISceneManager * _smgr) {
	sun = _smgr->addLightSceneNode(
		0,								// parent = 0 (null)
		core::vector3df(12.5, 40, -10)	// position
	);
	sun-> setLightType(video::ELT_DIRECTIONAL);
	// change angle:
	scene::ISceneNode *pNode = _smgr->addEmptySceneNode();
	sun->setPosition(core::vector3df(0,0,1)); //default is (1,1,0)
	sun->setParent(pNode);
	// now rotate pNode to set light angle (degrees):
	//	x: up/down rotation (90 = directly above)
	//	y: rotates around sides (90 = to the left)
	//	z:
	pNode->setRotation(core::vector3df(75, -20, -20));
}
































