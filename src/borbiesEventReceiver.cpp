#include "borbiesEventReceiver.h"
#include "game.h"
#include "gameMenu.h"

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
