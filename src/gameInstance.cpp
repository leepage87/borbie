#include "gameInstance.h"
#include "game.h"
#include "keyBindings.h"

using namespace irr;
using namespace scene;
using namespace video;
using namespace core;
using namespace gui;


// CONSTRUCTOR:
//  builds the GameInstance object and initializes all internal game objects,
//  such as buildings, vehicles, etc.
GameInstance::GameInstance(
	ISceneManager *smgr,
	IGUIEnvironment *guienv,
	IVideoDriver *driver,
	IrrlichtDevice *device,
	AudioSystem *audioSystem,
	unsigned int runMode)
{
    /*** Setup Pointers and Irrlicht Objects ***/    
    
	// keep pointers to Irrlicht rendering pointers
	this->smgr = smgr;
	this->guienv = guienv;
	this->driver = driver;
	this->device = device;
	this->audioSystem = audioSystem;
	
	// setup global collision meta selector
	this->metaTriSelector = smgr->createMetaTriangleSelector();



	/*** Setup Runtime Flags ***/
	
	float gravity = GLOBAL_GRAVITY;
	bool noVerticalMovement = true; // disabled
	
	// if debug mode, turn off gravity and enable vertical movement
	if(runMode & BORBIE_DEBUG_MODE){
		gravity = 0.f; // no gravity
		noVerticalMovement = false; // vertical movement enabled
	}
	
	
	
	/*** Setup Environment ***/
	
	// Add Terrain and collision
	this->terrain = new Terrain(driver, smgr, metaTriSelector);
	addCollision(this->terrain->getTriSelector());
	
	// add skybox
	this->skybox = new Sky(smgr, driver);
	
	// add lighting
	this->light = new WorldLight(smgr);
	
  //set shadow color: dark purplish
	smgr->setShadowColor(video::SColor(120,35,20,47));
	

	/*** Setup Game Objects (BUILDINGS, VEHICLES) ***/
    
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
	
	
	
	/*** Setup User Interface (HUD) ***/
	
	// add the hud object
	this->hud = new Hud(this->guienv, this->driver);
	
	
	
	/*** Setup Camera ***/
	
	// TODO: there was a memory leak. Delete after finished!
	SKeyMap keyMap[9];
    KeyBindings *keys = new KeyBindings(&keyMap[0]);
    keys->setKeys();
    // added: (remove if setKeys() becomes static)
    delete keys;
    
    // setup camera
		camera = smgr->addCameraSceneNodeFPS(
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
	camera->setPosition(vector3df(2500, 1000, 4450));
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


	//create beatDown ray selector
	selector = new CastRay(smgr, camera);
	highlightedSceneNode = 0;

}


// destructor: removes all objects from memory and ensures that the scene
//  manager is completely wiped clean of all Irrlicht objects.
GameInstance::~GameInstance(){
    delete this->terrain;
	delete this->skybox;
	delete this->light;
	delete this->buildings;
	delete this->vehicles;
	delete this->selector;
    this->smgr->clear();
}



/*** PER-FRAME UPDATE METHODS ***/

// called each frame by Game object to upda all of the GameInstance
//  subsystems, including GUI, target selector, and sound.
void GameInstance::update(){
    this->drawGUI();
    this->updateSelector();
    this->updateSound();
}

// (private)
// calls update on the hud (called each frame)
void GameInstance::drawGUI(){
    this->hud->drawHud();
}

// (private)
// gets a highlighted scene node if there is one
void GameInstance::updateSelector(){
if (highlightedSceneNode) {
		//highlighted->setMaterialFlag(EMF_LIGHTING, true);
		highlightedSceneNode->setVisible(true);
		highlightedSceneNode = 0;
	}
ISceneNode * selected = selector->getTarget();
	if (selected){
		highlightedSceneNode = selected;
		//highlightedSceneNode->setMaterialFlag(EMF_LIGHTING, false);
		highlightedSceneNode->setVisible(false);
	}
}

// (private)
// update the sound system for current player position and orientation
void GameInstance::updateSound(){
    this->audioSystem->update(
        this->camera->getPosition(),
        this->camera->getRotation()
    );
}



/*** PRIVATE COLLISION METHODS ***/

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
