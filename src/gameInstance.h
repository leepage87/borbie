/********************************************************************* 
 *	File:     gameInstance.h
 *	Authors:  Richard Teammco, Lee Page, Jonathan Miodownik
 *	Description: This is the header file for gameInstance.cpp
 *********************************************************************/

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
#include "enemies.h"
#include "borbie.h"
#include "hands.h"


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

enum menu
{
  NG,
  EXIT
};

// GameInstance class:
class GameInstance {
  public:
    // list of game sounds used by multiple game classes
    SoundClip *burningSound;
    SoundClip *explosionSound1;
    SoundClip *death1;
    SoundClip *gunShot1;
    SoundClip *gunShot2;

    // current game time
    unsigned int currentGameTime;


  private:
    // irrlicht renderer pointers
    irr::scene::ISceneManager *smgr;
    irr::scene::ICameraSceneNode *camera;
    irr::gui::IGUIEnvironment *guienv;
    irr::video::IVideoDriver *driver;
    irr::IrrlichtDevice *device;
    irr::ITimer *timer;
    
    //menu of the death screen
    irr::video::ITexture *menu;
    irr::gui::IGUIButton *newGameButton;
    irr::gui::IGUIButton *quitButton;

    CastRay *selector;
    ObjectCarrier *objCarry;
    irr::scene::ISceneNode *highlightedSceneNode;
    irr::IEventReceiver *receiver;
    irr::core::vector3df targetPos; //position object was thrown at
    VehicleInstance *carriedVehicle; //object being carried/thrown
    bool vehicleThrown; // true if a vehicle has been thrown
    int nextScoreEvent;

    // collision detection pointers
    irr::scene::IMetaTriangleSelector *metaTriSelector;

    // game objects (e.g. terrain, GUI, etc.)
    AudioSystem *audioSystem;
    SoundClip *bgSound;
    SoundClip *borbieDead;
    SoundClip *bgSoundDead;
    Terrain *terrain;
    Sky *skybox;
    WorldLight *light;
    Buildings *buildings;
    Vehicles *vehicles;
    Enemies * enemies;
    Hud *hud;
    Game *game;
    Hands *hands;
    MapReader *mapReader;
    MapSearcher *mapSearcher;


    // private update methods to update the various subsystems:
    //  all of these are called by the update() method.
    void drawGUI();
    void updateSelector();
    void updateThrownObject();
    std::vector<GameObject *> updateList;

    // world state changes: update the mood of the global environment by swapping
    //  music, ambiant sound, ambiant colors and applying various world effects.
    void setWorldState(WorldState state);
    void setWorldState_wrecked();
    void setWorldState_fabulous();

    // world effect values
    irr::scene::IParticleSystemSceneNode *rainParticleSystem;
    void createRainParticleSystem(const char *texture);
    void setRainEmitter(irr::scene::IParticleEmitter *emitter);

    // gameplay events
    void punch(); // try to punch something
    unsigned int nextPunchTime; // lock to prevent punch by click spamming


  public:
    Borbie *player; // TODO - public variable just like that? Really?

    GameInstance(irr::scene::ISceneManager *smgr,
        irr::gui::IGUIEnvironment *guienv,
        irr::video::IVideoDriver *driver,
        irr::IrrlichtDevice *device,
        AudioSystem *audioSystem,
        unsigned int runMode,
        irr::IEventReceiver *receiver, Game *game);

    ~GameInstance();

    // getters for all Irrlicht objects: used by objects in the game
    //  to get pointers to all necessary Irrlicht objects.
    irr::gui::IGUIEnvironment* getIGUIEnvironment() {return this->guienv;}
    irr::scene::ISceneManager* getSceneManager() { return this->smgr; }
    irr::video::IVideoDriver* getDriver() { return this->driver; }
    irr::IrrlichtDevice* getDevice() { return this->device; }
    AudioSystem* getAudioSystem() { return this->audioSystem; }
    irr::scene::ICameraSceneNode* getCamera() { return camera; }
    irr::scene::IMetaTriangleSelector* getMetaSelector() {
      return this->metaTriSelector;
    }
    MapReader* getMapReader() { return this->mapReader; }
    MapSearcher* getMapSearcher() { return this->mapSearcher; }

    // update the player's score
    void updatePlayerScore(int amount);
    
    // register a click event (using BorbieInput enum)
    void clickEvent(BorbieInputEvent click);

    // sets a new object to the update list
    void addUpdateObject(GameObject *toUpdate);

    // updates all of the game subsystems (hud, selectors, sounds, etc.)
    void update();


    //the coziest place
    void applyExplosionDamage(GameObject *gameObject);

    // collision detection functions (add and remove from meta tri selector)
    void addCollision(irr::scene::ITriangleSelector *selector);
    void removeCollision(irr::scene::ITriangleSelector *selector);


}; // end of GameInstance class


#endif // end of header definition
