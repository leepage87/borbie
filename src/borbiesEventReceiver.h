#ifndef BORBIESEVENTRECEIVER_H
#define BORBIESEVENTRECEIVER_H
  
#include <irrlicht.h>

class BorbiesEventReceiver : public irr::IEventReceiver {
  public:
   bool OnEvent(const irr::SEvent& event){return false;}
   bool IsKeyDown(irr::EKEY_CODE key) { return false;}
};
#endif
