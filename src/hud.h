#ifndef HUD_H
#define HUD_H


#include <irrlicht.h>

// Hud class
class Hud {
  private:
    irr::gui::IGUIEnvironment *guienv;
    irr::video::IVideoDriver *driver;

  public:
    Hud(irr::gui::IGUIEnvironment *guienv, irr::video::IVideoDriver *driver);
    ~Hud();
    
    void changeHealthState(const int healthState);
    void changeMoodText(const char *text);
    
}; // end of Hud class

#endif
