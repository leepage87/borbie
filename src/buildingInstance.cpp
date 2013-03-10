/*	File: buildingInstance.cpp
 *	Authors: idk your names
 *
 *	Description: this file contains the class declaration of the
 *	building instance object. The building object provides a specification
 *	of the abstract GameObject class and contains functions and variables
 *	specific to destructable buildings placed within the environment.
 */

#include "buildingInstance.h"

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
	this->sceneNode = smgr->addCubeSceneNode();
	this->sceneNode->setScale(vector3df(width, height, depth));
	this->sceneNode->setMaterialTexture(0, texture);
}


void BuildingInstance::doDamage(int damage){
	this->health -= damage;
}

void BuildingInstance::applyCollision(
	irr::scene::IMetaTriangleSelector *metaTriSelector)
{
	ITriangleSelector *selector =
		smgr->createTriangleSelectorFromBoundingBox(sceneNode);
	sceneNode->setTriangleSelector(selector);
	selector->drop();
	metaTriSelector->addTriangleSelector(sceneNode->getTriangleSelector());
}
