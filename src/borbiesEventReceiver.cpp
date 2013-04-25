#include "borbiesEventReceiver.h"
#include "game.h"
#include "gameMenu.h"
#include "gameInstance.h"

#include <iostream>


bool BorbiesEventReceiver::OnEvent(const irr::SEvent& event){

  //MENU EVENTS
  if(game)
  {
    SoundClip *mm = audioSystem->createSound2d("assets/sounds/menuMouseOver.wav");
    SoundClip *newGame = audioSystem->createSound2d("assets/sounds/hugebitch.wav");

    if(game->getGameState() == BORBIE_MAIN_MENU_STATE)
    {

      if(event.EventType == irr::EET_GUI_EVENT)
      {
        irr::s32 id = event.GUIEvent.Caller->getID();
        switch(event.GUIEvent.EventType)
        {
          case irr::gui::EGET_BUTTON_CLICKED:
            switch(id)
            {
              case NEW_GAME:
                if(newGame)
                 audioSystem->playSound2d(newGame); 
                game->manageStates();
                std::cout<<"Hello from New Game"<<std::endl;
                break; 

              case QUIT:
                if(device)
                {
                  std::cout << "Escape Button Pressed: Goodbye!" << std::endl;
                  device->closeDevice();
                  break;
                }
              default:
                std::cout<<"Unimplemented Button Pressed"<<std::endl; 
                break;
            }
          case irr::gui::EGBS_BUTTON_MOUSE_OVER:
            switch(id)
            {
              default:
                if(mm && id!=TITLE)
                  audioSystem->playSound2d(mm);

            }
        }
      }    
    }
  }

  //BORBIE GAME ON EVENTS

  // switch the game state if ESC is pressed (makes it easier to work with for now)
  if(game)
    if(game->getGameState() == BORBIE_GAME_STATE)
    {
      if (event.EventType == irr::EET_KEY_INPUT_EVENT){
        //FIXME  TODO this is testing shit to see if borbi updates her health
        if(event.KeyInput.Key == irr::KEY_MINUS && !event.KeyInput.PressedDown){
          if(gameInstance && gameInstance->player)
            gameInstance->player->applyDamage(10);        
        } 

        if(event.KeyInput.Key == irr::KEY_ESCAPE && !event.KeyInput.PressedDown){
          if(device){
            std::cout << "Escape Key Pressed: Switching States" << std::endl;
            game->manageStates();
          }
        }
      } else if(event.EventType == irr::EET_MOUSE_INPUT_EVENT){
        switch(event.MouseInput.Event){
          case irr::EMIE_RMOUSE_PRESSED_DOWN:
            rightButtonDown = true;
            std::cout << "R MOUSE DOWN" << std::endl;
            break;

          case irr::EMIE_RMOUSE_LEFT_UP:
            rightButtonDown = false;
            std::cout << "R MOUSE UP" << std::endl;
            break;

          case irr::EMIE_LMOUSE_PRESSED_DOWN:
            leftButtonDown = true;
            std::cout << "L MOUSE DOWN" << std::endl;
            break;

          case irr::EMIE_LMOUSE_LEFT_UP:
            //MouseState.RightButtonDown = false;
            leftButtonDown = false;
            std::cout << "L MOUSE UP" << std::endl;
            break;

          default:
            break;
        }


      }
      return false;
    }
}
