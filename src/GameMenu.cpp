#include "gameMenu.h"

using namespace irr;
using namespace gui;
using namespace video;
using namespace core;

GameMenu::GameMenu(IGUIEnvironment *guienv, IVideoDriver *driver, AudioSystem *audioSystem)
{
  this->guienv=guienv;
  this->driver=driver;
  this->skin= guienv->getSkin();
  this->audioSystem = audioSystem;
    this->sound = audioSystem->createSound2d("assets/sounds/wind.wav");
  
  audioSystem->playMusicLoop(sound);
  audioSystem->setMusicVolume(1);
  
  //create some buttons!
  startButton = guienv->addButton(rect<s32>(10,240,110,240 + 32), 0, NEW_GAME, L"", L"starts a new game");
  quitButton = guienv->addButton(rect<s32>(10,240,110,240 + 32), 0, QUIT, L"", L"Running Away!?");
  creditsButton = guienv->addButton(rect<s32>(10,240,110,240 + 32), 0, CREDITS, L"", L"learn about the losers who made this game");
  scoresButton = guienv->addButton(rect<s32>(10,240,110,240 + 32), 0, HIGH_SCORES, L"", L"see who's better than you"); 

  update();
}

GameMenu::~GameMenu()
{
  sound->release();
  guienv->clear();
}

void GameMenu::update()
{
  drawMenu();
}

GameButton GameMenu::getGameButton(void)
{
  return gameButton;
}

void GameMenu::drawMenu()
{
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

  creditsButton->setRelativePosition(rect<s32>(20, 160, 660, 210));
  creditsButton->setDrawBorder(0);
  creditsButton->setImage(driver->getTexture("assets/textures/buttons/CREDITS.png"));
  creditsButton->setUseAlphaChannel(true);  
 }
