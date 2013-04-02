#include "borbiesEventReceiver.h"
#include "game.h"

#include <iostream>



bool BorbiesEventReceiver::OnEvent(const irr::SEvent& event){


   	// quit the game if ESC is pressed (makes it easier to work with for now)
   	if (event.EventType == irr::EET_KEY_INPUT_EVENT){
   		if(event.KeyInput.Key == irr::KEY_ESCAPE){
   			if(device){
   				std::cout << "Escape Key Pressed: Goodbye!" << std::endl;
	   			device->closeDevice();
	   		}
   		}
   		
   		// if tab key pressed, switch game states
   		else if(event.KeyInput.Key == irr::KEY_TAB &&
   		        !event.KeyInput.PressedDown){
   		    game-> manageStates();
   		    std::cout << "TAB PRESSED: shifting game state." << std::endl;
   		}
	} else if(event.EventType == irr::EET_MOUSE_INPUT_EVENT){
		switch(event.MouseInput.Event){
			case irr::EMIE_RMOUSE_PRESSED_DOWN:
				//MouseState.RightButtonDown = true;
				rightButtonDown = true;
				std::cout << "R MOUSE DOWN" << std::endl;
				break;

			case irr::EMIE_RMOUSE_LEFT_UP:
				//MouseState.RightButtonDown = false;
				rightButtonDown = false;
				std::cout << "R MOUSE UP" << std::endl;
				break;
				
			default:
				break;
		}
				
		
	}
   	return false;
}

/*const SMouseState & BorbiesEventReceiver::GetMouseState(void) const{
	return MouseState;
}*/


