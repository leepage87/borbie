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
	//the parent node that the sun will be attached to
	scene::ISceneNode *pNode = _smgr->addEmptySceneNode();
	pNode->setPosition(core::vector3df(2600, 2000, 2600));
	
	sun = _smgr->addLightSceneNode(
		pNode,								// parent
		core::vector3df(0,0,1),				// position relative to parent
		video::SColor(255, 255, 255, 255),	// color
		4000.0f,							// radius of light
		-1									// id
	);
	sun-> setLightType(video::ELT_DIRECTIONAL);
	// change angle:
	// now rotate pNode to set light angle (degrees):
	//	x: up/down rotation (90 = directly above)
	//	y: rotates around sides (90 = to the left)
	//	z:
	pNode->setRotation(core::vector3df(85, 0, 0));

	// add ambient light
	_smgr->setAmbientLight(video::SColor(255, 255, 192, 203));
}
































