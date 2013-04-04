/*	File: buildingInstance.cpp
 *	Authors: idk your names
 *
 *	Description: this file contains the class declaration of the
 *	building instance object. The building object provides a specification
 *	of the abstract GameObject class and contains functions and variables
 *	specific to destructable buildings placed within the environment.
 */

#include "buildingInstance.h"

#include <iostream> // TODO: debug (remove)
using namespace std;

using namespace irr;
using namespace scene;
using namespace core;
using namespace video;


BuildingInstance::BuildingInstance(
	ISceneManager *smgr,
	float width, float height, float depth,
	float posX, float posY, float posZ,
	ITexture *texture)
	: GameObject(smgr) // call super GameObject constructor first
{
    // calculate y-position based on height (with posY being the base
    //  of the building. Irrlicht centers objects at 1/2 height.
    float actualPosY = posY + (height * 10) / 2;
    
    // set x,z positions based on width and depth respectively (center it)
    float actualPosX = posX + (width * 10) / 2;
    float actualPosZ = posZ + (depth * 10) / 2;
    
	this->sceneNode = smgr->addCubeSceneNode();
	this->sceneNode->setScale(vector3df(width, height, depth));
	this->sceneNode->setPosition(vector3df(actualPosX, actualPosY , actualPosZ));
	this->sceneNode->setMaterialTexture(0, texture);
	this->sceneNode->setMaterialFlag(EMF_LIGHTING, true);
	this->sceneNode->addShadowVolumeSceneNode(0,-1,true,25.0f);
}


void BuildingInstance::doDamage(int damage){
	this->health -= damage;
}

void BuildingInstance::applyCollision(
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
