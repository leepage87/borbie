#include "gameInstance.h"

using namespace irr;
using namespace scene;
using namespace video;
using namespace core;

GameInstance::GameInstance(ISceneManager *smgr, IVideoDriver *driver, IrrlichtDevice *device){
	// keep pointers to Irrlicht rendering pointers
	this->smgr = smgr;
	this->driver = driver;
	this->device = device;
	
	// setup global collision meta selector
	this->metaTriSelector = smgr->createMetaTriangleSelector();
		
	//create a temp camera for testing
	//TODO remove temp camera

	// setup camera
	ICameraSceneNode *camera = smgr->addCameraSceneNodeFPS(0, 100.0f, 1.2f);
	camera->setPosition(vector3df(2700*2,255*2,2600*2));
	camera->setFarValue(30000.0f); 
	//  hide cursor
	device->getCursorControl()->setVisible(false);
	
	// add terrain and collision
	this->terrain = new Terrain(driver, smgr, camera);
	addCollision(this->terrain->getTriSelector());
	
	// add skybox
	this->skybox = new Sky(smgr, driver);
  
	// add automatic collision response to camera
	ISceneNodeAnimator* anim =
		smgr->createCollisionResponseAnimator(metaTriSelector, camera,
			core::vector3df(10, 10, 10), // radius (10 = no clipping)
			core::vector3df(0, -10, 0)); // gravity (negative y = go down)
			//core::vector3df(0,20,0)); // radius offset
	camera->addAnimator(anim);
	anim->drop();
}


// Add a node's Traingle Selector to the global meta selector. Use
//	irr::scene::ISceneNode->getTriangleSelector() to get one.
//	Make sure to set it up first with:
//	smgr->createTriangleSelectorFromBoundingBox(node); (or something)
void GameInstance::addCollision(irr::scene::ITriangleSelector *selector){
	this->metaTriSelector->addTriangleSelector(selector);
}

// Remove a node's Triangle Selector from the global meta selector.
void GameInstance::removeCollision(irr::scene::ITriangleSelector *selector){
	this->metaTriSelector->removeTriangleSelector(selector);
}























// empty space just cuz it's cool
