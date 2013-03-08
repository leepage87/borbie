/*
 * game is the primary controll structure for running the game
 * depending on the game state, it will alternate between running
 * the playable game and the menuing system
 */

#include "game.h"

/*
   Standard Irrlicht namespaces
   */
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
//using namespace io;
//using namespace gui;

//Constructor
Game::Game()
{

  receiver = new BorbiesEventReceiver(); 
  //do something?
  device =
    createDevice(video::EDT_OPENGL,          // Video driver to use
        dimension2d<u32>(640, 480), // Dimensions of window
        32,                         // Bit-depth
        false,                      // Full screen
        false,                      // Stencil buffer
        false,                      // Vsync
        receiver);                 // Pointer to IEventReceiver


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
int Game::run(int runMode)
{
  this->gameInstance = new GameInstance(this->smgr, this->driver, this->device, runMode);
  while(device->run()) 
  {
    //this->gameInstance.draw();
    driver->beginScene(true, true, SColor(255,100,101,140));
    
    smgr->drawAll();
    driver->endScene();
  }
}

