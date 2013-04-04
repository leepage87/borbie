/*
 *Allows borbie to carry an object
 *
 */
#include "objectCarrier.h"

using namespace std;

using namespace irr;
using namespace scene;
using namespace core;

const f32 RAY_LENGTH_IN_UNITS = 350.0f;
//TODO: initialize this in gameInstance and pass it to the event receiver, pass in smgr and camera
//constructor:
//sets sceneManager and camera
ObjectCarrier::ObjectCarrier(irr::scene::ISceneManager *_smgr, irr::scene::ICameraSceneNode *_camera){
	this->smgr = _smgr;
	this->camera = _camera;
	this->selected = 0;
}
void ObjectCarrier::pickUp(irr::scene::ISceneNode *selected) {
	this->selected = selected;
	
	selected->setParent(camera);
	selected->setPosition(vector3df(40,-40,150));

//get bounding box and then get edges and find center
//irrtests src main line 106
}

void ObjectCarrier::throwObj(){
		selected->setParent(smgr->getRootSceneNode());//removes camera as parent
		selected->addAnimator(smgr->createFlyStraightAnimator(camera->getPosition(),
							camera->getTarget(), 400, false));
		selected = 0;
}


