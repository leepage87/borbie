/*********************************************************************
 * File:     gameMenu.cpp
 * Authors:  Richard Teammco, Lee Page, Jonathan Miodownik

 * Function: This creates the game's menu object.
 *********************************************************************/

#include "gameMenu.h"

using namespace irr;
using namespace gui;
using namespace video;
using namespace core;


/*********************************************************************
 * Constructor: Initializes all necessary engine pointers, adds sound,
 * and creates menu buttons.
 *********************************************************************/
GameMenu::GameMenu(IGUIEnvironment *guienv, IVideoDriver *driver, AudioSystem *audioSystem)
{
  this->guienv=guienv;
  this->driver=driver;
  this->skin= guienv->getSkin();
  this->audioSystem = audioSystem;
  this->sound = audioSystem->createSound2d("assets/sounds/wind.wav");

  audioSystem->playMusicLoop(sound);
  audioSystem->setMusicVolume(1);

  this->screenHeight = driver->getScreenSize().Height;


  //create some buttons!
  startButton = guienv->addButton(rect<s32>(10,240,110,240 + 32), 0, NEW_GAME, L"", L"starts a new game");
  quitButton = guienv->addButton(rect<s32>(10,240,110,240 + 32), 0, QUIT, L"", L"Running Away!?");
  creditsButton = guienv->addButton(rect<s32>(10,240,110,240 + 32), 0, CREDITS, L"", L"learn about the losers who made this game");
  scoresButton = guienv->addButton(rect<s32>(10,240,110,240 + 32), 0, HIGH_SCORES, L"", L"see who's better than you"); 

  titleButton = guienv->addButton(rect<s32>(10,240,100,900), 0, TITLE, L"", L"");  
  titleButton->setIsPushButton(false);

  update();
}


/*********************************************************************
 * Destructor: Clears the GUI env and releases all related sounds
 *********************************************************************/
GameMenu::~GameMenu()
{
  sound->release();
  guienv->clear();
}

/*********************************************************************
 * Updates the menu rendering on a frame by frame basis
 *********************************************************************/
void GameMenu::update()
{
  drawMenu();
}

/*********************************************************************
 * Getter for game buttons
 * Returns: gameButton that got got
 *********************************************************************/
GameButton GameMenu::getGameButton(void)
{
  return gameButton;
}

/*********************************************************************
 * Draws each frame of the menu, is called by the Update() method
 *********************************************************************/
void GameMenu::drawMenu()
{
  this->screenHeight = driver->getScreenSize().Height;

  //set the positions of the buttons
  startButton->setRelativePosition(rect<s32>(20, 20, 660, 70));
  startButton->setImage(driver->getTexture("assets/textures/buttons/NEW_GAME.png"));
  startButton->setUseAlphaChannel(true);
  startButton->setDrawBorder(0);

  quitButton->setRelativePosition(rect<s32>(20, 230, 660, 280));
  quitButton->setDrawBorder(0);
  quitButton->setImage(driver->getTexture("assets/textures/buttons/QUIT.png"));
  quitButton->setUseAlphaChannel(true);

  scoresButton->setRelativePosition(rect<s32>(20, 90, 660, 140));
  scoresButton->setDrawBorder(0);
  scoresButton->setImage(driver->getTexture("assets/textures/buttons/HIGH_SCORES.png"));
  scoresButton->setUseAlphaChannel(true);
  creditsButton->setRelativePosition(rect<s32>(20, 160, 660, 210)); creditsButton->setDrawBorder(0);
  creditsButton->setImage(driver->getTexture("assets/textures/buttons/CREDITS.png"));
  creditsButton->setUseAlphaChannel(true);  


  titleButton->setRelativePosition(rect<s32>(20, screenHeight-120, 920, screenHeight-20));
  titleButton->setImage(driver->getTexture("assets/textures/buttons/Title.png"));
  titleButton->setUseAlphaChannel(true);
  titleButton->setDrawBorder(0);

}

