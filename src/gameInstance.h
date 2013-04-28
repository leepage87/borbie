/* Comments... YOU add them
 *
 */

#ifndef GAMEINSTANCE_H
#define GAMEINSTANCE_H

// include c++ standard
#include <vector>

// include irrlicht
#include <irrlicht.h>

// include game object definitions
#include "terrain.h"
#include "sky.h"
#include "gameObject.h"
#include "worldLight.h"
#include "buildings.h"
#include "vehicles.h"
#include "hud.h"
#include "castRay.h"
#include "audioSystem.h"
#include "objectCarrier.h"
#include "borbiesEventReceiver.h"
#include "vehicleInstance.h"
#include "soldier.h"
#include "enemy.h"
#include "borbie.h"


// world constants
#define GLOBAL_GRAVITY -40.0f
#define PLAYER_ROTATE_SPEED 100.0f
#define PLAYER_MOVEMENT_SPEED 1.2f
#define PLAYER_MOVEMENT_SPEED_DEBUG 5.0f
#define PLAYER_JUMP_SPEED 12.0f
#define PLAYER_HEIGHT 200.0f


// world state enum
enum WorldState {
    FABULOUS,
    WHATEVER,
    GONETOSHIT
};


// GameInstance class:
class GameInstance {
  public:
  	// list of game sounds used by multiple game classes
  	SoundClip *burningSound;
  	
  	
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
	irr::IEventReceiver *receiver;
	irr::core::vector3df targetPos; //position object was thrown at
	VehicleInstance *carriedVehicle; //object being carried/thrown
	bool vehicleThrown; // true if a vehicle has been thrown
    
    // collision detection pointers
	irr::scene::IMetaTriangleSelector *metaTriSelector;
	
	// game objects (e.g. terrain, GUI, etc.)
	AudioSystem *audioSystem;
    SoundClip *bgSound;
	Terrain *terrain;
	Sky *skybox;
	WorldLight *light;
	Buildings *buildings;
	Vehicles *vehicles;
	Enemy * enemies;
	Hud *hud;
	
	// private update methods to update the various subsystems:
	//  all of these are called by the update() method.
	void drawGUI();
    void updateSelector();
    void updateSound(); 
    void updateThrownObject();
    std::vector<GameObject *> updateList;
    
    // world state changes: update the mood of the global environment by swapping
    //  music, ambiant sound, ambiant colors and applying various world effects.
    void setWorldState(WorldState state);
    void setWorldState_wrecked();
    
    // world effect values
    irr::scene::IParticleSystemSceneNode *rainParticleSystem;
    void createRainParticleSystem();
    void setRainEmitter(irr::scene::IParticleEmitter *emitter);
    

  public:
    Borbie *player;
    
    GameInstance(irr::scene::ISceneManager *smgr,
                irr::gui::IGUIEnvironment *guienv,
    			irr::video::IVideoDriver *driver,
    			irr::IrrlichtDevice *device,
    			AudioSystem *audioSystem,
    			unsigned int runMode,
					irr::IEventReceiver *receiver);

    ~GameInstance();
    
    // getters for all Irrlicht objects: used by objects in the game
    //  to get pointers to all necessary Irrlicht objects.
    irr::gui::IGUIEnvironment* getIGUIEnvironment() {return this->guienv;}
    irr::scene::ISceneManager* getSceneManager() { return this->smgr; }
    irr::video::IVideoDriver* getDriver() { return this->driver; }
    irr::IrrlichtDevice* getDevice() { return this->device; }
    irr::scene::IMetaTriangleSelector* getMetaSelector() {
            return this->metaTriSelector;
        }
    AudioSystem* getAudioSystem() { return this->audioSystem; }
	
	// sets a new object to the update list
	void addUpdateObject(GameObject *toUpdate);
	
    // updates all of the game subsystems (hud, selectors, sounds, etc.)
    void update();

    irr::scene::ICameraSceneNode* getCamera() { return camera; }

  //the coziest place
  void applyExplosionDamage(GameObject *gameObject);
	// collision detection functions (add and remove from meta tri selector)
	void addCollision(irr::scene::ITriangleSelector *selector);
	void removeCollision(irr::scene::ITriangleSelector *selector);
  

}; // end of GameInstance class


#endif // end of header definition
