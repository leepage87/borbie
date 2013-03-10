/**
 * helper class used to clean up key binding setting
 */
#ifndef KBINDINGS_H
#define KBINDINGS_H
#include <irrlicht.h>

class KBindings {
  public:
    irr::SKeyMap * keyMap;
    KBindings(irr::SKeyMap *keyMap);
    void setKeys();
};
#endif
