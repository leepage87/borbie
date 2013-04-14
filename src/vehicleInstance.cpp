/*	File: buildingInstance.cpp
 *	Authors: idk your names
 *
 *	Description: this file contains the class declaration of the
 *	building instance object. The building object provides a specification
 *	of the abstract GameObject class and contains functions and variables
 *	specific to destructable buildings placed within the environment.
 */

#include "vehicleInstance.h"

#include <iostream> // TODO: debug (remove)
using namespace std;

using namespace irr;
using namespace scene;
using namespace core;
using namespace video;


VehicleInstance::VehicleInstance(
	ISceneManager *smgr,
	IVideoDriver *driver,
	IrrlichtDevice *device,
	GameInstance *gameInstance,
	float posX, float posY, float posZ, IAnimatedMesh *mesh, int modelIndex)
	// call super GameObject constructor first:
	: GameObject(smgr, driver, device, gameInstance)
{

    
	this->sceneNode = smgr->addMeshSceneNode(mesh);
	if (modelIndex == 0){//its a jeep
		this->sceneNode->setScale(vector3df(.2, .2, .2));
	}else{//its a riviera
		this->sceneNode->setScale(vector3df(40,40,40));
	}
	this->sceneNode->setPosition(vector3df(posX, posY+20 , posZ));
	this->sceneNode->setMaterialFlag(EMF_LIGHTING, true);
	//this->sceneNode->addShadowVolumeSceneNode(0,-1,true,25.0f);
}


void VehicleInstance::doDamage(int damage){
	this->health -= damage;
}

void VehicleInstance::applyCollision(
	irr::scene::IMetaTriangleSelector *metaTriSelector)
{
	// add its triangles to the global collision meta selector
	ITriangleSelector *selector =
		smgr->createTriangleSelectorFromBoundingBox(sceneNode);
	sceneNode->setTriangleSelector(selector);
	selector->drop();
	metaTriSelector->addTriangleSelector(sceneNode->getTriangleSelector());
	
	// get bounds
	/*core::aabbox3d<f32> modelBounds = this->sceneNode->getTransformedBoundingBox();
	// add a collision response animator to it
	core::vector3df radius = modelBounds.MaxEdge - modelBounds.getCenter();
	ISceneNodeAnimator* anim = this->smgr->createCollisionResponseAnimator(
		metaTriSelector, this->sceneNode,
		radius, // radius of collision
		vector3df(0, -5, 0), // gravity (negative y = down)
		vector3df(0, -radius.Y, 0)); // radius offset
	this->sceneNode->addAnimator(anim);
	anim->drop();*/
}
