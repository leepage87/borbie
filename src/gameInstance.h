#include <irrlicht.h>

class GameInstance {
  public:
    GameInstance(irr::ISceneManager *smgr);

    void draw();
 
  private:
    irr::ISceneManager *smgr;
    // draw functions
};
