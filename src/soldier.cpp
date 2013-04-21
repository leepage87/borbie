/*	File: soldier.cpp
 *	Authors: idk your names
 *	
 *	This class creates soldiers so you can throw cars at them and shit
 */

#include "soldier.h"
#include "gameInstance.h"

#include <iostream> // TODO: debug (remove)
using namespace std;

using namespace irr;
using namespace scene;
using namespace core;
using namespace video;


Soldier::Soldier(
	GameInstance *gameInstance,
	float posX, float posY, float posZ)
	// call super GameObject constructor first:
	: GameObject(gameInstance)
{
    sceneNode =
    	smgr->addAnimatedMeshSceneNode(smgr->getMesh("assets/models/enemies/green_army_man.3DS"));
	sceneNode->setPosition(vector3df(posX, posY, posZ));
	sceneNode->setScale(vector3df(0.7,0.7,0.7));
	sceneNode->setVisible(true);
	sceneNode->setMaterialFlag(EMF_LIGHTING, false);

	//create the billboard for the "bullet"
	bill = smgr->addBillboardSceneNode();
    bill->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR );
    bill->setMaterialTexture(0, driver->getTexture("assets/textures/particle.bmp"));
    bill->setMaterialFlag(video::EMF_LIGHTING, false);
    bill->setMaterialFlag(video::EMF_ZBUFFER, false);
    bill->setSize(core::dimension2d<f32>(20.0f, 20.0f));
    bill->setID(0);//not pickable by ray caster
}

void Soldier::applyCollision(
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

void Soldier::fire(){
	//get the length of the distance we're shooting
	//hard coded target for testing
	vector3df end = gameInstance->getCamera()->getPosition();

	//get enemy position, adjust bullet height to barrel
	vector3df start = sceneNode->getPosition();
	float gunPosition[3];
	start.getAs3Values(gunPosition);
	start = vector3df(gunPosition[0], gunPosition[1]+15, gunPosition[2]);

	f32 length = (f32)(end - start).getLength();
	const f32 speed = 7.0f;
	//figure out how long it should take to get there, so the animator speed is constant
	u32 time = (u32)(length / speed);
	ISceneNodeAnimator* anim = gameInstance->getSceneManager()->createFlyStraightAnimator(start, end, time);
	bill->addAnimator(anim);
	anim->drop();
	anim = gameInstance->getSceneManager()->createDeleteAnimator(time);
	//bill->addAnimator(anim);
	anim->drop();
	
}
