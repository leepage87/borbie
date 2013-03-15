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
	float posX, float posY, float posZ)
	: GameObject(smgr) // call super GameObject constructor first
{






    
	this->sceneNode = smgr->addMeshSceneNode(smgr->getMesh("assets/models/jeep/jeep.obj"));
	this->sceneNode->setScale(vector3df(.2, .2, .2));
	this->sceneNode->setPosition(vector3df(posX, posY , posZ));
	this->sceneNode->setMaterialFlag(EMF_LIGHTING, false);
	this->sceneNode->addShadowVolumeSceneNode(0,-1,true,50.0f);
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
