/*********************************************************************
 * File: castRay.cpp
 * Authors: Richard Teammco, Lee Page, Jonathan Miodownik
 *
 * Description: Creates a ray caster for use in selecting targets and
 *              checking line of sight.
 *********************************************************************/

#include "castRay.h"

#include <iostream>

using namespace std;

using namespace irr;
using namespace scene;
using namespace core;

const f32 CLICK_RAY_LENGTH = 600.0f;
const f32 CLICK_RAY_LENGTH_SHORT = 300.0f;
const f32 THROW_RAY_LENGTH = 10000.0f;

/*********************************************************************
 * Constructor: sets sceneManager and camera
 *********************************************************************/
CastRay::CastRay(ISceneManager *_smgr, ICameraSceneNode *_camera){

	this->smgr = _smgr;
	this->camera = _camera;
}

/*********************************************************************
 * (private)
 * Returns the first ISceneNode in the current scene that is directly
 * in front of the camera, up to given number game units away. If no
 * target is within range,
 * RETURNS: the selected scene node or null
 *********************************************************************/
irr::scene::ISceneNode * CastRay::getTarget(float distance) {
	line3d<f32> ray;
	ray.start = camera->getPosition();
	ray.end = camera->getPosition() +
		(camera->getTarget() - camera->getPosition()).normalize()
        * distance;

	ISceneCollisionManager* collMan = smgr->getSceneCollisionManager();
	vector3df intersection;
	triangle3df hitTriangle;

	ISceneNode * selected =
		collMan->getSceneNodeAndCollisionPointFromRay(
		ray, intersection, hitTriangle, IDFlag_IsPickable, 0);

	return selected;
}

/*********************************************************************
 * Returns the first ISceneNode in the current scene directly up to
 * 600 units away. Returns NULL if nothing is there.
 *********************************************************************/
irr::scene::ISceneNode* CastRay::getClickTarget(){
    return this->getTarget(CLICK_RAY_LENGTH);
}

/*********************************************************************
 * Returns the first ISceneNode in the current scene directly up to 400 units
 * away. Returns NULL if nothing is there.
 *********************************************************************/
irr::scene::ISceneNode* CastRay::getClickTargetShort(){
    return this->getTarget(CLICK_RAY_LENGTH_SHORT);
}

/*********************************************************************
 * Same as getClickTarget: DEPRECATED
 *********************************************************************/
irr::scene::ISceneNode* CastRay::getTarget(){
    return this->getTarget(CLICK_RAY_LENGTH);
}

/*********************************************************************
 * Returns the first ISceneNode in the current scene up to
 * THROW_RAY_LENGTH units away. Returns NULL if nothing is there.
 *********************************************************************/
irr::scene::ISceneNode* CastRay::getThrowTarget(){
    return this->getTarget(THROW_RAY_LENGTH);
}
