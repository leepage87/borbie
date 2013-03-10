/*	File: game.cpp
 *	Authors: idk your names
 *
 *	Description: this file contains the class declaration for the
 *	Game class. This object is responsible for starting the
 *	game, initializaing the Irrlicht engine, and then switching between
 *	the primary high-level phases of the game (i.e. main menu and
 *	game instance). It "glues" main game pieces together under the
 *	game engine's roof.
 */

#include "game.h"

// using Irrlicht engine namespaces:
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
//using namespace io;
//using namespace gui;

//Constructor
Game::Game(unsigned int runMode)
{
  // remember the run mode flag
  this->runMode = runMode;
  
  receiver = new BorbiesEventReceiver();
  // if fullscreen is flagged, run as full screen
  bool fullScreen = false;
  if(runMode & BORBIE_FULLSCREEN)
  	fullScreen = true;
  device =
    createDevice(video::EDT_OPENGL,          // Video driver to use
        dimension2d<u32>(640, 480), // Dimensions of window
        32,                         // Bit-depth
        fullScreen,                 // Full screen
        false,                      // Stencil buffer
        false,                      // Vsync
        receiver);                 // Pointer to IEventReceiver

  ((BorbiesEventReceiver *)receiver)->setDevice(device);

  device->setWindowCaption(L"Borbie's Big Adventure: LET'S HIT THE TOWN!");

  /* Cache pointers to the VideoDriver, SceneManager, and
     GUIEnvironment in local variables. */
  driver = device->getVideoDriver();
  smgr = device->getSceneManager();

}

//De(con)structor
Game::~Game()
{
  device->drop();
}

//TODO eventually refactor to call a run either playable game or gui-menu
int Game::run()
{
  this->gameInstance =
  	new GameInstance(this->smgr, this->driver, this->device, this->runMode);
  while(device->run()) 
  {
    //this->gameInstance.draw();
    driver->beginScene(true, true, SColor(255,100,101,140));
    
    smgr->drawAll();
    driver->endScene();
  }
}

