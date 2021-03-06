/*********************************************************************
 * File:     hud.h
 * Authors:  Richard Teammco, Lee Page, Jonathan Miodownik

 * Function: This is the class delaration for the HUD object, which
 * displays health and score information as well as a borbie face and 
 * crosshair when applicable.
 *********************************************************************/

#ifndef HUD_H
#define HUD_H


#include <irrlicht.h>
class GameInstance;

// Hud class
class Hud {
  private:
    irr::gui::IGUIEnvironment *guienv;
    irr::video::IVideoDriver *driver;
    
    // main hud texture (background)
    irr::video::ITexture *hudTexture;
    //the borbie faces
    irr::video::ITexture *borbieFine;
    irr::video::ITexture *borbieMeh;
    irr::video::ITexture *borbieBad;
    irr::video::ITexture *borbieVeryBad;
    irr::video::ITexture *borbieDead;
    irr::video::ITexture *borbieFace; 
    
    irr::core::dimension2d<irr::u32> hudTextureSize;
    irr::core::dimension2d<irr::u32> borbieTextureSize;

    // target icon texture
    bool targetMarkerEnabled;
    irr::video::ITexture *targetImage;
    irr::core::dimension2d<irr::u32> targetImageSize;
    
    // font
    irr::gui::IGUIFont *font;
    GameInstance *gameInstance;

  public:
    Hud(GameInstance *gameInstance);
    ~Hud();
    
    void changeHealthState(const int healthState);
    void changeMoodText(const char *text);
       
    // start or stop displaying of the target icon in the middle of the screen
    void setTargetMarkerEnabled(bool val);
    
    void drawHud();
    void updateFace(int health);    
    void drawFace();
}; // end of Hud class

#endif
