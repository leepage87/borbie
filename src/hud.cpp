#include "hud.h"

using namespace irr;
using namespace gui;
using namespace video;
using namespace core;


Hud::Hud(IGUIEnvironment *guienv, IVideoDriver *driver){
    this->guienv = guienv;
    this->driver = driver;
    
    guienv->addImage(
        driver->getTexture("assets/textures/hudTexture.jpg"),
        position2d<s32>(0, 0));
}

Hud::~Hud(){

}
    
void Hud::changeHealthState(const int healthState){

}

void Hud::changeMoodText(const char *text){

}
