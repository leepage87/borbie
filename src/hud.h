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
    irr::core::dimension2d<irr::u32> hudTextureSize;
    
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
    
}; // end of Hud class

#endif
