/*	File: building.cpp
 *	Authors: idk your names
 *
 *	Description: this file contains the class declaration of the
 *	building object. The building object provides a specification
 *	of the abstract GameObject class and contains functions and variables
 *	specific to destructable buildings placed within the environment.
 */

#include "building.h"

using namespace irr;
using namespace scene;
using namespace core;
using namespace video;


Building::Building(
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


void Building::doDamage(int damage){
	this->health -= damage;
}

void Building::applyCollision(
	irr::scene::IMetaTriangleSelector *metaTriSelector)
{
	ITriangleSelector *selector =
		smgr->createTriangleSelectorFromBoundingBox(sceneNode);
	sceneNode->setTriangleSelector(selector);
	selector->drop();
	metaTriSelector->addTriangleSelector(sceneNode->getTriangleSelector());
}
