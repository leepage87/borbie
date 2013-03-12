/* Comments... YOU add them
 *
 */

#ifndef GAMEINSTANCE_H
#define GAMEINSTANCE_H

// include irrlicht
#include <irrlicht.h>

// include c++ standard library objects
#include <vector>

// include game object definitions
#include "terrain.h"
#include "sky.h"
#include "game_object.h"
#include "ambientLight.h"
#include "buildings.h"


// world constants
#define GLOBAL_GRAVITY -40.0f
#define PLAYER_ROTATE_SPEED 100.0f
#define PLAYER_MOVEMENT_SPEED 1.2f
#define PLAYER_JUMP_SPEED 12.0f
#define PLAYER_HEIGHT 200.0f


// GameInstance class:
class GameInstance {
  private:
 	// irrlicht renderer pointers
    irr::scene::ISceneManager *smgr;
    irr::video::IVideoDriver *driver;
    irr::IrrlichtDevice *device;
    
    // collision detection pointers
	irr::scene::IMetaTriangleSelector *metaTriSelector;
	
	// list of all scene objects
	std::vector<GameObject *> sceneObjects;
	// TODO: maybe make separate lists for buildings, npc's, vehicles, etc.
	//	for better control over each object type.
	
	// collision detection functions (add and remove from meta tri selector)
	void addCollision(irr::scene::ITriangleSelector *selector);
	void removeCollision(irr::scene::ITriangleSelector *selector);
	
	// game objects (e.g. terrain, GUI, etc.)
	Terrain *terrain;
	Sky *skybox;
	ambientLight *light;
	Buildings *buildings;
	
    
  public:
    GameInstance(irr::scene::ISceneManager *smgr,
    			irr::video::IVideoDriver *driver,
    			irr::IrrlichtDevice *device,
    			unsigned int runMode);
    ~GameInstance();

//    void draw();


}; // end of GameInstance class


#endif // end of header definition
