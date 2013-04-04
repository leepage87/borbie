#ifndef GAME_MENU_H
#define GAME_MENU_H

#include <irrlicht.h>

enum GameButton
{
  NEW_GAME,
  QUIT,
  KILL_YOURSELF
};

class GameMenu
{
  private:
    //pointers to Menu Related Objects
    GameButton gameButton;

    irr::gui::IGUIButton *startButton;

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
   
    GameButton getGameButton(void); 
    void update();

};
#endif

