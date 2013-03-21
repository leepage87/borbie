/*
 *Casts a ray and returns any scene nodes the ray intersects
 *
 *Returns: The intersected scene node
 */
#include "castRay.h"

using namespace std;

using namespace irr;
using namespace scene;
using namespace core;

const f32 RAY_LENGTH_IN_UNITS = 350.0f;

//constructor:
//sets sceneManager and camera
CastRay::CastRay(ISceneManager *_smgr, ICameraSceneNode *_camera){

	this->smgr = _smgr;
	this->camera = _camera;
}

enum PickingIDs {
	IDFlag_IsNotPickable = 0,               // 0
	IDFlag_IsPickable = 1 << 0,             // 1 
	IDFlag_IsHighlightable = 1 << 1         // 2 
};

irr::scene::ISceneNode * CastRay::getTarget() {
	line3d<f32> ray;
	ray.start = camera->getPosition();
	ray.end = camera->getPosition() +
		(camera->getTarget() - camera->getPosition()).normalize() * RAY_LENGTH_IN_UNITS;

	ISceneCollisionManager* collMan = smgr->getSceneCollisionManager();
	vector3df intersection;
	triangle3df hitTriangle;

	ISceneNode * selected =
		collMan->getSceneNodeAndCollisionPointFromRay(
		ray, intersection, hitTriangle, IDFlag_IsPickable, 0);

	return selected;
}
