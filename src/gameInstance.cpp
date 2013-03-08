#include "gameInstance.h"
#include "game.h"

using namespace irr;
using namespace scene;
using namespace video;
using namespace core;

GameInstance::GameInstance(
	ISceneManager *smgr,
	IVideoDriver *driver,
	IrrlichtDevice *device,
	unsigned int runMode)
{
	// keep pointers to Irrlicht rendering pointers
	this->smgr = smgr;
	this->driver = driver;
	this->device = device;
	
	// setup global collision meta selector
	this->metaTriSelector = smgr->createMetaTriangleSelector();
	
	
	/*** Environment Setup ***/
	
	// Add Terrain and collision
	this->terrain = new Terrain(driver, smgr);
	addCollision(this->terrain->getTriSelector());
	
	// add skybox
	this->skybox = new Sky(smgr, driver);
	
	// add buildings
	
	// add lighting
	

	/*** Camera Setup ***/
	
	// setup camera
	ICameraSceneNode *camera = smgr->addCameraSceneNodeFPS(
		0,		// parent (none)
		100.0f,	// rotate speed
		1.2f,	// move speed
		0,		// ID
		0,		// keymap
		0,		// keymap size
		true,	// disable vertical movement
		3.f		// jump speed
	);
	camera->setPosition(vector3df(2700*2,255*2,2600*2));
	camera->setFarValue(30000.0f); 
	//  hide cursor
	device->getCursorControl()->setVisible(false);
  
  	// set gravity (0 if running in debug mode)
	int gravity = 0;
	/*if(runMode == BORBIE_DEBUG_MODE)
		gravity = 0;
	else
		gravity = GLOBAL_GRAVITY;*/
	
	// add automatic collision response to camera
	ISceneNodeAnimator* anim =
		smgr->createCollisionResponseAnimator(metaTriSelector, camera,
			core::vector3df(30, 150, 30), // radius (10 = no clipping)
			core::vector3df(0, gravity, 0)); // gravity (negative y = go down)
			//core::vector3df(0,20,0)); // radius offset
	camera->addAnimator(anim);
	anim->drop();
}



/*** PRIVATE HELPER METHODS: used for adjusting and manipulating the world ***/

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
