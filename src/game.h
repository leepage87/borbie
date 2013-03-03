#ifndef GAME_H
#define GAME_H

#include <irrlicht.h>
#include "borbiesEventReceiver.h"

class Game {
  private:
    irr::IrrlichtDevice *device;
    irr::IEventReceiver *receiver;
    irr::video::IVideoDriver* driver;
    irr::scene::ISceneManager *smgr;

  public:
    int run(); 

  Game();
  ~Game();
};

#endif
