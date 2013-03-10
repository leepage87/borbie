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
	

	/*** Runtime Flags Setup ***/
	
	float gravity = GLOBAL_GRAVITY;
	bool noVerticalMovement = true; // disabled
	
	// if debug mode, turn off gravity and enable vertical movement
	if(runMode & BORBIE_DEBUG_MODE){
		gravity = 0.f; // no gravity
		noVerticalMovement = false; // vertical movement enabled
	}
	
	/*** Camera Setup ***/
	
	// TODO: move these to a separate keybindings file
	// camera (player) control key bindings
	SKeyMap keyMap[8];
	// forward movement (UP arrow and W)
	keyMap[0].Action = EKA_MOVE_FORWARD;
	keyMap[0].KeyCode = KEY_UP;
	keyMap[1].Action = EKA_MOVE_FORWARD;
	keyMap[1].KeyCode = KEY_KEY_W;
	// backwards movement (DOWN arrow and S)
	keyMap[2].Action = EKA_MOVE_BACKWARD;
	keyMap[2].KeyCode = KEY_DOWN;
	keyMap[3].Action = EKA_MOVE_BACKWARD;
	keyMap[3].KeyCode = KEY_KEY_S;
	// left movement (LEFT arrow and A)
	keyMap[4].Action = EKA_STRAFE_LEFT;
	keyMap[4].KeyCode = KEY_LEFT;
	keyMap[5].Action = EKA_STRAFE_LEFT;
	keyMap[5].KeyCode = KEY_KEY_A;
	// left movement (RIGHT arrow and D)
	keyMap[6].Action = EKA_STRAFE_RIGHT;
	keyMap[6].KeyCode = KEY_RIGHT;
	keyMap[7].Action = EKA_STRAFE_RIGHT;
	keyMap[7].KeyCode = KEY_KEY_D;
	// jump action (SPACE)
	keyMap[8].Action = EKA_JUMP_UP;
	keyMap[8].KeyCode = KEY_SPACE;
	
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
	// set camera position to ???? TODO: wtf?
	//camera->setPosition(vector3df(2700*2,255*2,2600*2));
	//camera->setPosition(vector3df(5400, 510, 5200));
	camera->setPosition(vector3df(5400, 1000, 5200));
	// set view distance
	camera->setFarValue(30000.0f); 
	//  hide cursor
	device->getCursorControl()->setVisible(false);
	
	// add automatic collision response to camera
	ISceneNodeAnimator* anim =
		smgr->createCollisionResponseAnimator(metaTriSelector, camera,
			core::vector3df(30, 150, 30), // radius (10 = no clipping)
			core::vector3df(0, gravity, 0), // gravity (negative y = go down)
			core::vector3df(0, PLAYER_HEIGHT, 0)); // radius offset
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
