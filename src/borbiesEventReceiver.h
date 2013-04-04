#ifndef BORBIESEVENTRECEIVER_H
#define BORBIESEVENTRECEIVER_H
  
#include <irrlicht.h>
#include <iostream>
#include "objectCarrier.h"
#include "castRay.h"

class Game;
/*
	struct SMouseState{
		bool RightButtonDown;
		SMouseState() : RightButtonDown(false) { }
	}MouseState;
*/
// BorbiesEventReceiver class (extends IEventReceiver)
class BorbiesEventReceiver : public irr::IEventReceiver {
  private:
  	irr::IrrlichtDevice *device;
  	Game *game;
		ObjectCarrier *objCarry;
		CastRay *selector;
		bool rightButtonDown;
		bool leftButtonDown;
  public:
   // set the device pointer
   void setDevice(irr::IrrlichtDevice *device, Game *game){
   	this->device = device;
   	this->game = game;
   }

   // process input events
   bool OnEvent(const irr::SEvent& event);/*{
   	// quit the game if ESC is pressed (makes it easier to work with for now)
   	if (event.EventType == irr::EET_KEY_INPUT_EVENT){
   		if(event.KeyInput.Key == irr::KEY_ESCAPE){
   			if(device){
   				std::cout << "Escape Key Pressed: Goodbye!" << std::endl;
	   			device->closeDevice();
	   		}
   		}
	} else if(event.EventType == irr::EET_MOUSE_INPUT_EVENT){
		//game-> manageStates();
	}
   	return false;
   }*/
   
   
   // returns if key is pressed down or not
   bool IsKeyDown(irr::EKEY_CODE key) { return false; }

	bool isRightMouseDown() { return rightButtonDown; }
	bool isLeftMouseDown() { return leftButtonDown; }

	void setRightMouse(bool status) { rightButtonDown = status; }
		//const SMouseState & GetMouseState(void) const;
   
}; // end of BorbiesEventReceiver class.


#endif
