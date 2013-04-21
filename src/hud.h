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
    
    // font
    irr::gui::IGUIFont *font;
    GameInstance *gameInstance;

  public:
    Hud(GameInstance *gameInstance);
    ~Hud();
    
    void changeHealthState(const int healthState);
    void changeMoodText(const char *text);
    
    void drawHud();
    
}; // end of Hud class

#endif
