#include "borbiesEventReceiver.h"
#include "game.h"
#include "gameMenu.h"
#include "gameInstance.h"

#include <iostream>


bool BorbiesEventReceiver::OnEvent(const irr::SEvent& event){

  //MENU EVENTS
  if(game)
  {
    
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
                break; 
              case QUIT:
                if(device)
                {
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
            gameInstance->player->applyDamage(1000);        
        }

        if(event.KeyInput.Key == irr::KEY_ESCAPE && !event.KeyInput.PressedDown){
          if(device){
            std::cout << "Escape Key Pressed: Switching States" << std::endl;
            game->manageStates();
          }
        }
      } else if(event.EventType == irr::EET_MOUSE_INPUT_EVENT){
        switch(event.MouseInput.Event){
          case irr::EMIE_RMOUSE_PRESSED_DOWN: // right mouse down
            rightButtonDown = true;
            gameInstance->clickEvent(BORBIE_RIGHT_CLICK);
            break;

          case irr::EMIE_RMOUSE_LEFT_UP: // right mouse up
            rightButtonDown = false;
            break;

          case irr::EMIE_LMOUSE_PRESSED_DOWN: // left mouse down
            leftButtonDown = true;
            gameInstance->clickEvent(BORBIE_LEFT_CLICK);
            break;

          case irr::EMIE_LMOUSE_LEFT_UP: // left mouse up
            leftButtonDown = false;
            break;

          default:
            break;
        }


      }
      return false;
    }
}
