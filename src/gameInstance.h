#include <irrlicht.h>

class GameInstance {
  public:
    GameInstance(irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *driver);

//    void draw();
 
  private:
    irr::scene::ISceneManager *smgr;
    irr::video::IVideoDriver *driver; 
    // draw functions
};
