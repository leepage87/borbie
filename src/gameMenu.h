#ifndef GAME_MENU_H
#define GAME_MENU_H

#include <irrlicht.h>
#include "audioSystem.h"

enum GameButton
{
  NEW_GAME,
  QUIT,
  CREDITS,
  HIGH_SCORES,
  KILL_YOURSELF
};

class GameMenu
{
  private:
    //pointers to Menu Related Objects
    GameButton gameButton;
    
    AudioSystem *audioSystem;
    SoundClip *sound;
    
    irr::gui::IGUIButton *startButton;
    irr::gui::IGUIButton *quitButton;
    irr::gui::IGUIButton *creditsButton;
    irr::gui::IGUIButton *scoresButton;

    irr::gui::IGUIEnvironment *guienv;
    irr::video::IVideoDriver *driver;

    irr::video::ITexture *menuTexture;
    irr::core::dimension2d<irr::u32> menuTextureSize;

    irr::gui::IGUISkin *skin;
    irr::gui::IGUIFont *font;
    
    void drawMenu(); 
  public:
    GameMenu(irr::gui::IGUIEnvironment *guienv,
        irr::video::IVideoDriver *driver,AudioSystem *audioSystem);
    ~GameMenu();
   
    GameButton getGameButton(void); 
    void update();

};
#endif

