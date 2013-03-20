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
#include <iostream>

// using Irrlicht engine namespaces:
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
//using namespace io;
using namespace gui;


//Constructor
Game::Game(unsigned int runMode)
{
    // remember the run mode flag
    this->runMode = runMode;

    gui = 0;
    gameInstance = 0;

    receiver = new BorbiesEventReceiver();
    // if fullscreen is flagged, run as full screen
    bool fullScreen = false;
    if(runMode & BORBIE_FULLSCREEN)
        fullScreen = true;
    device =
        createDevice(video::EDT_OPENGL, // Video driver to use
            dimension2d<u32>(800, 600), // Dimensions of window
            32,                         // Bit-depth
            fullScreen,                 // Full screen
            true,                       // Stencil buffer
            false,                      // Vsync
            receiver);                  // Pointer to IEventReceiver

    // set the event receiver's device pointer to the current device.
    ((BorbiesEventReceiver *)receiver)->setDevice(device, this);

    device->setWindowCaption(L"Borbie's Big Adventure: LET'S HIT THE TOWN!");

    /* Cache pointers to the VideoDriver, SceneManager, and
       GUIEnvironment in local variables. */
    driver = device->getVideoDriver();
    device->setResizable(true);
    smgr = device->getSceneManager();
    guienv = smgr->getGUIEnvironment();
    
    // Create the audio system
    this->audioSystem = new AudioSystem();
    this->audioSystem->playMusicLoop("assets/sounds/yumyum.ogg");

    // start the main menu (initial phase)
    gameState = BORBIE_MAIN_MENU_STATE;
    loadMainMenuState(); 
}


//De(con)structor: clean up Irrlicht
Game::~Game()
{
    delete this->audioSystem;
    this->device->drop();
}


// loads the main menu
void Game::loadMainMenuState(){
    this->gui = new Gui();
    this->audioSystem->setMusicVolume(1.0);
}


// loads the main game state
void Game::loadGameState(){
    this->gameInstance = new GameInstance(this->smgr, this->guienv,
			this->driver, this->device, this->runMode);
    this->audioSystem->setMusicVolume(0.25);
}


// switches to the next available game state
void Game::manageStates()
{
	// if currently in menu state, switch to game state
	if(gameState == BORBIE_MAIN_MENU_STATE){
		gameState = BORBIE_GAME_STATE;
		if(gui){
			delete gui;
			gui = 0;
	    }
		loadGameState();
	}
	
	// if currently in game state, switch to menu state
	else if(gameState == BORBIE_GAME_STATE){
		gameState = BORBIE_MAIN_MENU_STATE;
		if(gameInstance){
			delete gameInstance;
			gameInstance = 0;
		}
		loadMainMenuState();
	}
}


//TODO eventually refactor to call a run either playable game or gui-menu
int Game::run()
{  
  while(device->run()) 
  {
    //this->gameInstance.draw();
    driver->beginScene(true, true, SColor(255,100,101,140));
    
    // draw world and GUI
    smgr->drawAll();
    guienv->drawAll();
    
    // if gameInstance is active, draw the GUI
    if(gameInstance){
        gameInstance->drawGUI();
				gameInstance->updateSelector();
		}
    	
    driver->endScene();
  }
}

