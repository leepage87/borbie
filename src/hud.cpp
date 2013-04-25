#include "hud.h"
#include "gameInstance.h"

#include <iostream> // TODO: debug

using namespace irr;
using namespace gui;
using namespace video;
using namespace core;

Hud::Hud(GameInstance *gameInstance){
    this->gameInstance=gameInstance;
    this->guienv = gameInstance->getIGUIEnvironment();
    this->driver = gameInstance->getDriver();

    // get hud font
    this->font = guienv->getFont("assets/fonts/bigfont.png");
    if(!this->font)
        std::cout << "ERROR: Font can't load." << std::endl;

    // get the main hud texture
    this->hudTexture = driver->getTexture("assets/textures/hudTexture1.jpg");
    this->hudTextureSize = this->hudTexture->getSize();
    
    //load in the borbie textures
    this->borbieFine = driver->getTexture("assets/textures/borbieFine.jpg");
    this->borbieMeh = driver->getTexture("assets/textures/borbieMeh.jpg");
    this->borbieBad = driver->getTexture("assets/textures/borbieBad.jpg");
    this->borbieDead = driver->getTexture("assets/textures/borbieDead.jpg");
    
    this->borbieTextureSize = borbieFine->getSize();

    this->targetMarkerEnabled = false;
    this->targetImage = driver->getTexture("assets/textures/target.png");
    this->targetImageSize = this->targetImage->getSize();
}

Hud::~Hud(){
    this->hudTexture->drop();
    this->targetImage->drop();
}


void Hud::drawHud(){
    // get screen dimensions
    float screenWidth = driver->getScreenSize().Width;
    float screenHeight = driver->getScreenSize().Height;
    
    // if target marker is enabled, draw that
    if(this->targetMarkerEnabled){
        float targetSize = screenHeight/20;
        float targetX = screenWidth/2 - targetSize/2;
        float targetY = screenHeight/2 - targetSize/2;
        driver->draw2DImage(
            this->targetImage,
            rect<s32>(targetX, targetY,
                targetX + targetSize, targetY + targetSize),
            rect<s32>(0, 0,
                this->targetImageSize.Width,
                this->targetImageSize.Height),
            0, 0, true);
    }
    
    // calculate hud width and height based on screen size
    float hudX = 0;
    float hudW = screenWidth;
    float hudY = screenHeight - (screenHeight / 8);
    float hudH = screenHeight / 8;
    
    int health = gameInstance->player->getHealth();

    if(health >= 750)
    {
      this->borbieFace = borbieFine;
    }else if(health < 750 && health > 500)
    {
      this->borbieFace = borbieMeh;
    }else if(health <=500 && health > 0)
    {
      this->borbieFace = borbieBad;
    }else
    {
      this->borbieFace = borbieDead;
    }

      
    driver->draw2DImage(
        this->hudTexture,
        rect<s32>(hudX, hudY, hudX+hudW, hudY+hudH),
       rect<s32>(0, 0,
            this->hudTextureSize.Width,
            this->hudTextureSize.Height));

    // draw the hud background
    driver->draw2DImage(
        this->borbieFace,
        rect<s32>((hudW/2)-70, hudY+5, (hudW/2)+70, hudY+hudH-5),
        rect<s32>(0, 0,
            this->borbieTextureSize.Width,
            this->borbieTextureSize.Height));
    
    // draw text
    if(font){
        stringw s;
        s += gameInstance->player->getHealth(); 
        font->draw(
            s, rect<s32>(hudW-250, hudY, hudX+hudW, hudY+hudH),
            SColor(255, 239,9,107),
            true, true);

    }
}


// start or stop displaying of the target icon in the middle of the screen
void Hud::setTargetMarkerEnabled(bool val){
    this->targetMarkerEnabled = val;
}


void Hud::changeHealthState(const int healthState){

}

void Hud::changeMoodText(const char *text){

}
