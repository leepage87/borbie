#include "borbiesEventReceiver.h"
#include "game.h"



bool BorbiesEventReceiver::OnEvent(const irr::SEvent& event){
   	// quit the game if ESC is pressed (makes it easier to work with for now)
   	if (event.EventType == irr::EET_KEY_INPUT_EVENT){
   		if(event.KeyInput.Key == irr::KEY_ESCAPE){
   			if(device){
   				std::cout << "Escape Key Pressed: Goodbye!" << std::endl;
	   			device->closeDevice();
	   		}
   		}
	} else if(event.EventType == irr::EET_MOUSE_INPUT_EVENT){
		switch(event.MouseInput.Event){
			case irr::EMIE_LMOUSE_PRESSED_DOWN:
				game-> manageStates();	
				break;
			default:
				break;
		}
				
		
	}
   	return false;
}
