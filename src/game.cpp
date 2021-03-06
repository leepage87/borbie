 /********************************************************************* 
 *	File: game.cpp
 *	Authors:  Richard Teammco, Lee Page, Jonathan Miodownik
 *
 *	Description: This object is responsible for starting the
 *	game, initializaing the Irrlicht engine, and then switching between
 *	the primary high-level phases of the game (i.e. main menu and
 *	game instance). It "glues" main game pieces together under the
 *	game engine's roof.
 *********************************************************************/

#include "game.h"
#include "random.h"
#include <iostream>

// using Irrlicht engine namespaces:
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
//using namespace io;
using namespace gui;


/*********************************************************************
 * Constructor: Initializes the irrlicht device driver, audio system,
 *              event receiver, scene manager, GUI enviornment, and
 *              loads the main menu.
 * Param: runMode determines whether or not to run the game in fullscreen
 *                See header file for full description.
 *********************************************************************/
Game::Game(unsigned int runMode)
{
    // remember the run mode flag
    this->runMode = runMode;
    
    // seed the random number generator
    Random::init();

    gameMenu = 0;
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
    // Create the audio system
    this->audioSystem = new AudioSystem();

    // set the event receiver's device pointer to the current device.
    ((BorbiesEventReceiver *)receiver)->initialize(this->gameInstance, device, this, audioSystem);

    device->setWindowCaption(L"Borbie's Big Adventure: LET'S HIT THE TOWN!");

    /* Cache pointers to the VideoDriver, SceneManager, and
       GUIEnvironment in local variables. */
    driver = device->getVideoDriver();
    device->setResizable(true);
    smgr = device->getSceneManager();
    guienv = smgr->getGUIEnvironment();
    
    g_device = device;
    
    //this->audioSystem->playMusicLoop("assets/sounds/yumyum.ogg");

    // start the main menu (initial phase)
    gameState = BORBIE_MAIN_MENU_STATE;
    loadMainMenuState(); 
}

/*********************************************************************
 * De(con)structor: clean up Irrlicht
 *********************************************************************/
Game::~Game()
{
    if(this->gameInstance)
        delete this->gameInstance;
    if(this->gameMenu)
        delete this->gameMenu;
    delete this->receiver;
    delete this->audioSystem;
    this->device->drop();
}

/*********************************************************************
 * loads the main menu
 *********************************************************************/
void Game::loadMainMenuState(){
    this->gameMenu = new GameMenu(guienv, driver, audioSystem);
}


/*********************************************************************
 * loads the main game 
 *********************************************************************/
void Game::loadGameState(){
    this->gameInstance = new GameInstance(
        this->smgr, this->guienv, this->driver, this->device,
		this->audioSystem, this->runMode, this->receiver, this);
//    this->audioSystem->setMusicVolume(0.5);
}

/*********************************************************************
 * Returns: the current game state
 *********************************************************************/
GameState Game::getGameState(void)
{
  return gameState;
}
/*********************************************************************
 * switches to the next available game state
 *********************************************************************/
void Game::manageStates()
{
	// if currently in menu state, switch to game state
	if(gameState == BORBIE_MAIN_MENU_STATE){
		gameState = BORBIE_GAME_STATE;
		if(gameMenu){
			delete gameMenu;
			gameMenu = 0;
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


/*********************************************************************
 * Returns: the game menu
 *********************************************************************/
GameMenu* Game::getGameMenu()
{
    return gameMenu; 
}

/*********************************************************************
 * Runs the game and calls per-frame update methods
 *********************************************************************/
int Game::run()
{  
    while(device->run())
    {
        driver->beginScene(true, true, SColor(255,100,101,140));
        
        // draw world and GUI
        smgr->drawAll();

        //draw the background for the main menu before the
        //buttons get generated
        if(gameState == BORBIE_MAIN_MENU_STATE){
          // get screen dimensions
          float screenWidth = driver->getScreenSize().Width;
          float screenHeight = driver->getScreenSize().Height;

          // calculate hud width and height based on screen size
          float hudX = 0;
          float hudW = screenWidth;
          float hudY = screenHeight - (screenHeight / 8);
          float hudH = screenHeight / 8;
          
          driver->draw2DRectangle(SColor(255,0,0,0), rect<s32>(0, 0, screenWidth, screenHeight));

          //load the borbie cover
          driver->enableMaterial2D();
          driver->draw2DImage(driver->getTexture("assets/misc/borbie_menu.jpg"), core::rect<s32>(screenWidth-800,0,screenWidth,screenHeight),
              core::rect<s32>(0,0,800,1200));
          driver->enableMaterial2D(false);
          
          driver->draw2DRectangle(SColor(100,0,0,0), rect<s32>(0, 0, 500, 300));

        }

          guienv->drawAll();
        
        // if gameInstance is active, update its subsystems
        if(gameInstance)
          gameInstance->update();
												
        
        if(gameMenu)
          gameMenu->update();
        	
        driver->endScene();
    }
}
