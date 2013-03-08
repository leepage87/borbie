#ifndef GAME_H
#define GAME_H

//System includes
#include <irrlicht.h>

//Game Includes
#include "borbiesEventReceiver.h"
#include "gameInstance.h"


// run mode definitions
#define BORBIE_DEBUG_MODE 0
#define BORBIE_GAME_MODE 1


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
    int run(int runMode);

}; // end of Game class

#endif
