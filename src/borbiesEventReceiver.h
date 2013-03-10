#ifndef BORBIESEVENTRECEIVER_H
#define BORBIESEVENTRECEIVER_H
  
#include <irrlicht.h>
#include <iostream>


// BorbiesEventReceiver class (extends IEventReceiver)
class BorbiesEventReceiver : public irr::IEventReceiver {
  private:
  	irr::IrrlichtDevice *device;
  
  public:
   // set the device pointer
   void setDevice(irr::IrrlichtDevice *device){
   	this->device = device;
   }
  
   // process input events
   bool OnEvent(const irr::SEvent& event){
   	// quit the game if ESC is pressed (makes it easier to work with for now)
   	if (event.EventType == irr::EET_KEY_INPUT_EVENT){
   		if(event.KeyInput.Key == irr::KEY_ESCAPE){
   			if(device){
   				std::cout << "Escape Key Pressed: Goodbye!" << std::endl;
	   			device->closeDevice();
	   		}
   		}
	}
   	return false;
   }
   
   // returns if key is pressed down or not
   bool IsKeyDown(irr::EKEY_CODE key) { return false; }
   
}; // end of BorbiesEventReceiver class.


#endif
