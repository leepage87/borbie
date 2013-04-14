/*	File: soldier.cpp
 *	Authors: idk your names
 *	
 *	This class creates soldiers so you can throw cars at them and shit
 */

#include "soldier.h"

#include <iostream> // TODO: debug (remove)
using namespace std;

using namespace irr;
using namespace scene;
using namespace core;
using namespace video;


Soldier::Soldier(
	ISceneManager *smgr,
	IVideoDriver *driver,
	IrrlichtDevice *device,
	float posX, float posY, float posZ)
	: Enemy(smgr, driver, device) // call super GameObject constructor first
{
    sceneNode =
    	smgr->addAnimatedMeshSceneNode(smgr->getMesh("assets/models/enemies/soldier/soldier_1.obj"));
	sceneNode->setPosition(vector3df(posX, posY, posZ));
	sceneNode->setScale(vector3df(40,40,40));
	sceneNode->setVisible(true);
	sceneNode->setMaterialFlag(EMF_LIGHTING, false);
}
