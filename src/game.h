#ifndef GAME_H
#define GAME_H

//System includes
#include <irrlicht.h>

//Game Includes
#include "borbiesEventReceiver.h"
#include "gameInstance.h"

class Game {
  private:
    irr::IrrlichtDevice *device;
    irr::IEventReceiver *receiver;
    irr::video::IVideoDriver* driver;
    irr::scene::ISceneManager *smgr;
    

  public:
    int run(); 
    GameInstance *GI;

  Game();
  ~Game();
};

#endif
