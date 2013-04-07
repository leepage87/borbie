#include "gameMenu.h"

using namespace irr;
using namespace gui;
using namespace video;
using namespace core;

GameMenu::GameMenu(IGUIEnvironment *guienv, IVideoDriver *driver)
{
  this->guienv=guienv;
  this->driver=driver;
  this->skin= guienv->getSkin();
  this->font=guienv->getFont("assets/fonts/bigfont.png");
  if(font)
    this->skin->setFont(font);
  
  //create some buttons!
  startButton = guienv->addButton(rect<s32>(10,240,110,240 + 32), 0, NEW_GAME, L"Let's Hit the Town!", L"starts a new game");
  quitButton = guienv->addButton(rect<s32>(10,240,110,240 + 32), 0, QUIT, L"Quit", L"Running Away!?");
  creditsButton = guienv->addButton(rect<s32>(10,240,110,240 + 32), 0, CREDITS, L"Credits", L"learn about the losers who made this game");
  scoresButton = guienv->addButton(rect<s32>(10,240,110,240 + 32), 0, HIGH_SCORES, L"High Scores", L"see who's better than you"); 


  update();
}

GameMenu::~GameMenu()
{
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
  // get screen dimensions
  float screenWidth = driver->getScreenSize().Width;
  float screenHeight = driver->getScreenSize().Height;

  // calculate hud width and height based on screen size
  float hudX = 0;
  float hudW = screenWidth;
  float hudY = screenHeight - (screenHeight / 8);
  float hudH = screenHeight / 8;

  //set the positions of the buttons
  startButton->setRelativePosition(rect<s32>(20, 20, 400, 70));
  startButton->setDrawBorder(0);
  quitButton->setRelativePosition(rect<s32>(20, 230, 100, 280));
  quitButton->setDrawBorder(0);
  scoresButton->setRelativePosition(rect<s32>(20, 90, 200, 140));
  scoresButton->setDrawBorder(0);
  creditsButton->setRelativePosition(rect<s32>(20, 160, 200, 210));
  creditsButton->setDrawBorder(0);
  
 
/*
    // the hud background
  driver->draw2DImage(
      this->menuTexture,
      rect<s32>(hudX, hudY, hudX+hudW, hudY+hudH),
      rect<s32>(0, 0,
        this->menuTextureSize.Width,
        this->menuTextureSize.Height));

  // draw text
  if(font){
    font->draw(
        "Borbie's Big Adventure",
        rect<s32>(hudX, hudY, hudX+hudW, hudY+hudH),
        SColor(255, 0, 0, 255),
        true, true); 
    //bool  	hcenter = false,
    //bool  	vcenter = false,
  }
  */
}
