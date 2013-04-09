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

vector3df ObjectCarrier::throwObj(){
		selected->setParent(smgr->getRootSceneNode());//removes camera as parent
		vector3df targetPos = camera->getTarget();
		ISceneNodeAnimator *flyAnimator =
		    smgr->createFlyStraightAnimator(camera->getPosition(),
							targetPos, 1000, false);
		selected->addAnimator(flyAnimator);
		flyAnimator->drop();
		//explodeObj(targetPos);
		selected = 0;
		return targetPos;
}



