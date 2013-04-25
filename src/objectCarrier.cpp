/*
 *Allows borbie to carry an object
 *
 */
#include "objectCarrier.h"
#include <iostream> // TODO - debug (remove)

using namespace std;

using namespace irr;
using namespace scene;
using namespace core;

const f32 RAY_LENGTH_IN_UNITS = 350.0f;

// constant: how long a thrown object will fly until it explodes
//  (it will explode sooner if it collides with something first)
const f32 TIME_TO_FLY = 1000.0f;
const f32 SPEED_UNITS_PER_MS = 10000.0f / 1000.0f; // 10000 units per second

//TODO: initialize this in gameInstance and pass it to the event receiver, pass in smgr and camera
//constructor:
//sets sceneManager and camera
ObjectCarrier::ObjectCarrier(
    irr::scene::ISceneManager *_smgr,
    irr::IrrlichtDevice *_device,
    irr::scene::ICameraSceneNode *_camera)
{
	this->smgr = _smgr;
	this->camera = _camera;
	this->selected = 0;
	
	this->timer = _device->getTimer();
	this->timerStopTime = 0;
}


// pick up an object: keep track of its node pointer.
void ObjectCarrier::pickUp(irr::scene::ISceneNode *selected) {
	this->selected = selected;
	
	selected->setParent(camera);
	selected->setPosition(vector3df(65,-40,150));
	vector3df rotation = (selected->getPosition()-camera->getPosition()).getHorizontalAngle();
	rotation.Y -=210;
	selected->setRotation(rotation);

//get bounding box and then get edges and find center
//irrtests src main line 106
}


// throw the object that is currently selected (picked up), if any
void ObjectCarrier::throwObj(ISceneNode *target){
    if(!selected) // if nothing is selected, return (do nothing)
        return;

    vector3df targetPos;
    float actualTimeToFly = TIME_TO_FLY;
    
    // if there is a target, cut time to fly by max distance
    // 15k game units per second fly speed
    if(target){
        targetPos = target->getPosition();
        f32 flyDist = camera->getPosition().getDistanceFrom(targetPos);
        //actualTimeToFly = 
        actualTimeToFly = flyDist / SPEED_UNITS_PER_MS;
        std::cout << "FLY TIME: " << actualTimeToFly << std::endl;
    }
    else{
        targetPos = camera->getTarget();
    }
    // send the selected object flying straight out towards the camera's target
    selected->setParent(smgr->getRootSceneNode()); //removes camera as parent
    //vector3df targetPos = camera->getTarget();
    ISceneNodeAnimator *flyAnimator =
        smgr->createFlyStraightAnimator(camera->getPosition(),
            targetPos, actualTimeToFly, false);
    selected->addAnimator(flyAnimator);
    flyAnimator->drop();
    selected = 0;
    
    // update timer stop time to current time plus actualTimeToFly
    this->timerStopTime = this->timer->getTime() + actualTimeToFly;
    
    // return the target position of the object's destination
    //return targetPos;
}


// returns TRUE if the thrown object (if any) is done flying. Does not
//  return valid information if no object has yet been thrown.
bool ObjectCarrier::objectDoneFlying(){
    return (this->timer->getTime() >= this->timerStopTime);
}
