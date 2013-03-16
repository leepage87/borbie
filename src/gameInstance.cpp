#include "gameInstance.h"
#include "game.h"
#include "kBindings.h"

using namespace irr;
using namespace scene;
using namespace video;
using namespace core;


// CONSTRUCTOR:
//  builds the GameInstance object and initializes all internal game objects,
//  such as buildings, vehicles, etc.
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
	
	// add lighting
	this->light = new WorldLight(smgr);

	/*** Runtime Flags Setup ***/
	
	float gravity = GLOBAL_GRAVITY;
	bool noVerticalMovement = true; // disabled
	
	// if debug mode, turn off gravity and enable vertical movement
	if(runMode & BORBIE_DEBUG_MODE){
		gravity = 0.f; // no gravity
		noVerticalMovement = false; // vertical movement enabled
	}
	
	/*** Camera Setup ***/
	
	// TODO: there was a memory leak. Delete after finished!
	SKeyMap keyMap[9];
    KBindings *keys = new KBindings(&keyMap[0]);
    keys->setKeys();
    // added: (remove if setKeys() becomes static)
    delete keys;
    
    // setup camera
	ICameraSceneNode *camera = smgr->addCameraSceneNodeFPS(
		0,						// parent (none)
		PLAYER_ROTATE_SPEED,	// rotate speed
		PLAYER_MOVEMENT_SPEED,	// move speed
		0,						// ID
		keyMap,					// keymap
		9,						// keymap size
		noVerticalMovement,		// no vertical movement (true = up/down disabled)
		PLAYER_JUMP_SPEED		// jump speed
	);
	
	// TODO: read camera position from map file
	camera->setPosition(vector3df(4400, 1000, 5200));
	// set view distance
	camera->setFarValue(30000.0f); 
	// hide cursor
	device->getCursorControl()->setVisible(false);
	
	// add automatic collision response to camera
	ISceneNodeAnimator* anim =
		smgr->createCollisionResponseAnimator(metaTriSelector, camera,
			core::vector3df(30, 150, 30), // radius (10 = no clipping)
			core::vector3df(0, gravity, 0), // gravity (negative y = go down)
			core::vector3df(0, PLAYER_HEIGHT, 0), //radius offset
      0.1f); // sliding value TODO tweak as needed
	camera->addAnimator(anim);
	anim->drop();
    
    // add the buildings and generate city based on coordinate file
	this->buildings = new Buildings(smgr, driver, metaTriSelector);
    this->buildings->generateBuildings("assets/map/coords.bor");
    
	const int ROAD_HEIGHT = 70;
	const int farX = 20000.0f;
	const int farY = 20000.0f;
	//add vehicle(s)
	this->vehicles = new Vehicles(smgr, driver, metaTriSelector);
	this->vehicles->addRandomVehicle(farX*.1953, ROAD_HEIGHT, farY*.2207);
    this->vehicles->addRandomVehicle(farX*.2453, ROAD_HEIGHT, farY*.2207);
    this->vehicles->addRandomVehicle(farX*.2953, ROAD_HEIGHT, farY*.2207);  
	
}


// destructor: removes all objects from memory and ensures that the scene
//  manager is completely wiped clean of all Irrlicht objects.
GameInstance::~GameInstance(){
    delete this->terrain;
	delete this->skybox;
	delete this->light;
	delete this->buildings;
	delete this->vehicles;
    this->smgr->clear();
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
