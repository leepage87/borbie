/*
 *Casts a ray and returns any scene nodes the ray intersects
 *
 *Returns: The intersected scene node
 */
#include "castRay.h"

#include <iostream>

using namespace std;

using namespace irr;
using namespace scene;
using namespace core;

const f32 CLICK_RAY_LENGTH = 500.0f;
const f32 THROW_RAY_LENGTH = 10000.0f;

//constructor:
//sets sceneManager and camera
CastRay::CastRay(ISceneManager *_smgr, ICameraSceneNode *_camera){

	this->smgr = _smgr;
	this->camera = _camera;
}

// (private)
// Returns the first ISceneNode in the current scene that is directly in front
//  of the camera, up to given number game units away. If no target is within range,
//  returns NULL.
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

// Returns the first ISceneNode in the current scene directly up to 400 units
//  away. Returns NULL if nothing is there.
irr::scene::ISceneNode* CastRay::getClickTarget(){
    return this->getTarget(CLICK_RAY_LENGTH);
}

// Same as getClickTarget: DEPRECATED
irr::scene::ISceneNode* CastRay::getTarget(){
    return this->getTarget(CLICK_RAY_LENGTH);
}

// Returns the first ISceneNode in the current scene up to ??? units
//  away. Returns NULL if nothing is there.
irr::scene::ISceneNode* CastRay::getThrowTarget(){
    return this->getTarget(THROW_RAY_LENGTH);
}
