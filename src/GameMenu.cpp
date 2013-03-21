#include "gameMenu.h"

using namespace irr;
using namespace gui;
using namespace video;
using namespace core;

GameMenu::GameMenu(IGUIEnvironment *guienv, IVideoDriver *driver)
{
  this->guienv=guienv;
  this->driver=driver;
  this->font=guienv->getFont("assets/fonts/bigfont.png");

    this->menuTexture = driver->getTexture("assets/textures/hudTexture.jpg");
    this->menuTextureSize = this->menuTexture->getSize();

  drawMenu();
}


GameMenu::~GameMenu()
{
  guienv->clear();
}

void GameMenu::drawMenu(){
  // get screen dimensions
  float screenWidth = driver->getScreenSize().Width;
  float screenHeight = driver->getScreenSize().Height;

  // calculate hud width and height based on screen size
  float hudX = 0;
  float hudW = screenWidth;
  float hudY = screenHeight - (screenHeight / 8);
  float hudH = screenHeight / 8;

  // draw the hud background
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
}
