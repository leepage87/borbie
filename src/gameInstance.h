/* Comments... YOU add them
 *
 */

#ifndef GAMEINSTANCE_H
#define GAMEINSTANCE_H

// include irrlicht
#include <irrlicht.h>

// include game object definitions
#include "terrain.h"
#include "sky.h"
#include "game_object.h"
#include "worldLight.h"
#include "buildings.h"
#include "vehicles.h"
#include "hud.h"
#include "castRay.h"
#include "audioSystem.h"
#include "objectCarrier.h"


// world constants
#define GLOBAL_GRAVITY -40.0f
#define PLAYER_ROTATE_SPEED 100.0f
#define PLAYER_MOVEMENT_SPEED 1.2f
#define PLAYER_MOVEMENT_SPEED_DEBUG 5.0f
#define PLAYER_JUMP_SPEED 12.0f
#define PLAYER_HEIGHT 200.0f


// GameInstance class:
class GameInstance {
  private:
 	// irrlicht renderer pointers
    irr::scene::ISceneManager *smgr;
		irr::scene::ICameraSceneNode *camera;
    irr::gui::IGUIEnvironment *guienv;
    irr::video::IVideoDriver *driver;
    irr::IrrlichtDevice *device;
		CastRay *selector;
		ObjectCarrier *objCarry;
		irr::scene::ISceneNode *highlightedSceneNode;

    
    // collision detection pointers
	irr::scene::IMetaTriangleSelector *metaTriSelector;
	
	// collision detection functions (add and remove from meta tri selector)
	void addCollision(irr::scene::ITriangleSelector *selector);
	void removeCollision(irr::scene::ITriangleSelector *selector);
	
	// game objects (e.g. terrain, GUI, etc.)
	AudioSystem *audioSystem;
	Terrain *terrain;
	Sky *skybox;
	WorldLight *light;
	Buildings *buildings;
	Vehicles *vehicles;
	Hud *hud;
	
	// private update methods to update the various subsystems:
	//  all of these are called by the update() method.
	void drawGUI();
    void updateSelector();
    void updateSound();
    
    
  public:
    GameInstance(irr::scene::ISceneManager *smgr,
                irr::gui::IGUIEnvironment *guienv,
    			irr::video::IVideoDriver *driver,
    			irr::IrrlichtDevice *device,
    			AudioSystem *audioSystem,
    			unsigned int runMode);

    ~GameInstance();
	
    // updates all of the game subsystems (hud, selectors, sounds, etc.)
    void update();

    irr::scene::ICameraSceneNode* getCamera() { return camera; }


}; // end of GameInstance class


#endif // end of header definition
