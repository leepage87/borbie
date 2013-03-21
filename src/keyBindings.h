/**
 * helper class used to clean up key binding setting
 */
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
