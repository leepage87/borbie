#include "gameInstance.h"
#include "game.h"
#include "kBindings.h"

#include <fstream> // TODO: move file stuff into a different place?
#include <string>
#include <iostream>
#include <istream>
#include <sstream>

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
	this->light = new ambientLight(smgr);

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
	SKeyMap keyMap[9];
  KBindings *keys = new KBindings(&keyMap[0]);
  keys->setKeys();
  
  
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
	camera->setPosition(vector3df(4400, 1000, 5200));
	// set view distance
	camera->setFarValue(30000.0f); 
	//  hide cursor
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
	
	/* Positions explained:
	 *  x: 0-19825  0 is RIGHT edge of texture
	 *  y: height (~500 is slightly over ground level)
	 *  z: 0-19825  0 is TOP edge of texture
	 *
	 *  9912.5 is half-way (9912.5, 9912.5) = center of texture
	 */
	IMeshSceneNode *sceneNode = smgr->addCubeSceneNode();
    sceneNode->setScale(vector3df(10, 10, 10));
    sceneNode->setPosition(vector3df(0, 1000 , 0));
	IMeshSceneNode *sceneNode2 = smgr->addCubeSceneNode();
    sceneNode2->setScale(vector3df(10, 10, 10));
    sceneNode2->setPosition(vector3df(19825, 1000 , 19825));
    sceneNode->setMaterialFlag(EMF_LIGHTING, true);
    sceneNode->addShadowVolumeSceneNode();
    
	
	this->buildings = new Buildings(smgr, driver, metaTriSelector);
	
	// read in the map building coordinate file
	std::ifstream mapfile("assets/map/coords.bor");
	for(std::string line; getline(mapfile, line); ) {
        if(line.size() == 0)
            continue;
        else if(line[0] == '#')
            continue;
        else {
             std::istringstream lineParser(line);
             float coordX, coordY;
             lineParser >> coordX;
             lineParser >> coordY;
             // use coordinates to add the building at specified location
             this->buildings->addRandomBuilding(
		        19825 * coordX,
		        0.0f,
		        19825 * (coordY)
	         );
             std::cout << "Generated building at " <<
                "x: " << coordX << ", y: " << coordY << std::endl;
        }
    }
    
	this->buildings->addRandomBuilding(
		19825 * coordX
		0.0f,
		4850.0f
	);
    
	/*this->buildings->addRandomBuilding(
		6500.0f,	// x		increase to make it go "right"
		0.0f,		// y
		4850.0f		// z        increase makes it go "back"
	);
	for(int i=0; i<10; ++i){
	    this->buildings->addRandomBuilding(
		    7350.0f + (450*i),	// x
		    0.0f,		// y
		    4850.0f		// z
	    );
	}
	for(int i=0; i<10; ++i){
	    this->buildings->addRandomBuilding(
		    7350.0f + (450*i),	// x
		    0.0f,		// y
		    5300.0f		// z
	    );
	}
	for(int i=0; i<10; ++i){
	    this->buildings->addRandomBuilding(
		    7350.0f + (450*i),	// x
		    0.0f,		// y
		    5750.0f		// z
	    );
	}
	for(int i=0; i<10; ++i){
	    this->buildings->addRandomBuilding(
		    7350.0f + (450*i),	// x
		    0.0f,		// y
		    6200.0f		// z
	    );
	}*/
}


// destructor: clears the scene
GameInstance::~GameInstance(){
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
