#ifndef GAME_MENU_H
#define GAME_MENU_H

#include <irrlicht.h>

class GameMenu
{
  private:
    irr::gui::IGUIEnvironment *guienv;
    irr::video::IVideoDriver *driver;

    irr::video::ITexture *menuTexture;
    irr::core::dimension2d<irr::u32> menuTextureSize;

    irr::gui::IGUIFont *font;
    
    void drawMenu(); 
  public:
    GameMenu(irr::gui::IGUIEnvironment *guienv,
        irr::video::IVideoDriver *driver);
    ~GameMenu();
    
    void update();

};
#endif

