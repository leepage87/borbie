#ifndef GAME_H
#define GAME_H

//System includes
#include <irrlicht.h>

//Game Includes
#include "borbiesEventReceiver.h"
#include "gameInstance.h"


// determines whether or not the game is running in debug mode
extern bool BORBIE_DEBUG_MODE;


// Game Class
class Game {
  private:
    irr::IrrlichtDevice *device;
    irr::IEventReceiver *receiver;
    irr::video::IVideoDriver* driver;
    irr::scene::ISceneManager *smgr;
    GameInstance *gameInstance;

  public:
  	// constructor/destructor
	Game();
	~Game();
	
	// start the game
    int run();

}; // end of Game class

#endif
