#include "hud.h"

#include <iostream> // TODO: debug

using namespace irr;
using namespace gui;
using namespace video;
using namespace core;


Hud::Hud(IGUIEnvironment *guienv, IVideoDriver *driver){
    this->guienv = guienv;
    this->driver = driver;
    
    /*guienv->addImage(
        driver->getTexture("assets/textures/hudTexture.jpg"),
        position2d<s32>(0, 0));*/
    
    /*
    float screenWidth = driver->getScreenSize().Width;
    float screenHeight = driver->getScreenSize().Height;
    
    float hudX = screenWidth / 2;
    float hudW = screenWidth / 4;
    float hudY = screenHeight - (screenHeight / 6);
    float hudH = screenHeight / 6;
    
    std::cout << "SCREEN W: " << screenWidth <<
        " | SCREEN H: " << screenHeight << std::endl;
    std::cout << "HUDX: " << hudX
        << " HUDY: " << hudY
        << " HUDW: " << hudW
        << " HUDH: " << hudH << std::endl;
    
    ITexture* tex;
    tex = driver->getTexture("assets/textures/hudTexture.jpg");

    IGUIImage* img;

    // Give to addImage() the XY coords of 2 points :
    img = guienv->addImage(
        core::rect<s32>(0, 0, 200, 200));
    img->setImage(tex);
    img->setScaleImage(true);
    driver->removeTexture(tex);
    */
    /*//ITexture* tex;
   // tex = driver->getTexture("assets/textures/hudTexture.jpg");

    driver->draw2DImage(tex,
        rect<s32>(0, 0, 200, 200),
        rect<s32>(0, 0, 200, 200));*/
    this->hudTexture = driver->getTexture("assets/textures/hudTexture.jpg");
}

Hud::~Hud(){

}


void Hud::drawHud(){
    float screenWidth = driver->getScreenSize().Width;
    float screenHeight = driver->getScreenSize().Height;
    
    float hudX = screenWidth / 4;
    float hudW = screenWidth / 2;
    float hudY = screenHeight - (screenHeight / 6);
    float hudH = screenHeight / 6;
    
    driver->draw2DImage(
        this->hudTexture,
        rect<s32>(hudX, hudY, hudX+hudW, hudY+hudH),
        rect<s32>(0, 0, 200, 200));
}

    
void Hud::changeHealthState(const int healthState){

}

void Hud::changeMoodText(const char *text){

}
