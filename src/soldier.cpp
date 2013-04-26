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
	setHealth(350);
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
	//create the billboard for the "bullet"
	IBillboardSceneNode * bill;
	bill = smgr->addBillboardSceneNode();
    bill->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR );
    bill->setMaterialTexture(0, driver->getTexture("assets/textures/particle.bmp"));
    bill->setMaterialFlag(video::EMF_LIGHTING, false);
    bill->setMaterialFlag(video::EMF_ZBUFFER, false);
    bill->setSize(core::dimension2d<f32>(20.0f, 20.0f));
    bill->setID(0);//not pickable by ray caster



	//hard coded target for testing
	float posAdjust[3];
	vector3df end = (gameInstance->getCamera()->getPosition());
	end.Y-=30;

	//get enemy position, adjust bullet height to barrel
	vector3df start = sceneNode->getPosition();
	start.Y+=45;

	//get the length of the distance we're shooting
	f32 length = (f32)start.getDistanceFrom(end);
	
	const float maxDistance = 4000;
	
	//vector3df bulletEnd = end;
	if (length < maxDistance){
		float scale = maxDistance/length;
		float diffX = end.X - start.X;
		float diffZ = end.Z - start.Z;
		end.X = start.X + diffX * scale;
		end.Z = start.Z + diffZ * scale;
		const f32 SPEED = 14.0f;
		//Borbie's Shit Adventure: Let's Fuck the Town!
		//figure out how long it should take to get there, so the animator SPEED is constant
		f32 length2 = (f32) start.getDistanceFrom(end);
		u32 time = (u32)(length2 / SPEED);
		//bulletEnd.X = bulletEnd.X * scale;
		//bulletEnd.Z = bulletEnd.Z * scale;
		//std::cout<<scale <<std::endl;
		/*
		IF BORBIE Z IS < SOLDIER Z MULTIPLY BY NEGATIVE, ETC
		//bulletEnd.X *= scale;
		//bulletEnd.Y *= scale;
		//bulletEnd.Z *= scale;
		*/
		ISceneNodeAnimator* anim = gameInstance->getSceneManager()->createFlyStraightAnimator(start, end, time);
		bill->addAnimator(anim);
		anim->drop();
		anim = gameInstance->getSceneManager()->createDeleteAnimator(time);
		bill->addAnimator(anim);
		anim->drop();
	}

	//turn the soldier to look at you
	end.Y -= 125;
	vector3df vect = start-end;
	sceneNode->setRotation(vect.getHorizontalAngle());
	
}
