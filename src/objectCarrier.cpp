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
}

void ObjectCarrier::pickUp(irr::scene::ISceneNode *selected) {
	//get the position of the object being picked up
	float carryPosition[3];
	vector3d<f32> oldPosition = selected->getPosition();
	camera->getPosition().getAs3Values(carryPosition);
	//drop the object by 20 units
	carryPosition[1] += -100.0;
	carryPosition[0] += 40.0;
	//TODO: FIX VEHICLE ROTATION, SINGLE CLICK CARRYING, DONT CARRY BUILDINGS
	selected->addAnimator(smgr->createFlyStraightAnimator(oldPosition,
							vector3df(carryPosition[0], carryPosition[1], carryPosition[2]), 200, false));
}
