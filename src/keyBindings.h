/*********************************************************************
 * File:     keyBindings.h
 * Authors:  Richard Teammco, Lee Page, Jonathan Miodownik

 * Function: Class declarations for key bindings settings
 *********************************************************************/
#ifndef KBINDINGS_H
#define KBINDINGS_H
#include <irrlicht.h>

class KeyBindings {
  public:
    irr::SKeyMap * keyMap;
    KeyBindings(irr::SKeyMap *keyMap);
    void setKeys();
};
#endif
