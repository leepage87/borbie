/* Comments... YOU add them
 *
 */

#ifndef GAMEINSTANCE_H
#define GAMEINSTANCE_H

#include <irrlicht.h>


// GameInstance class:
class GameInstance {
  private:
 	// irrlicht renderer pointers
    irr::scene::ISceneManager *smgr;
    irr::video::IVideoDriver *driver; 
    
    // collision detection pointers
	irr::scene::IMetaTriangleSelector *metaTriSelector;
	
	// collision detection functions (add and remove from meta tri selector)
	void addCollision(irr::scene::ITriangleSelector *selector);
	void removeCollision(irr::scene::ITriangleSelector *selector);
	
    
  public:
    GameInstance(irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *driver);

//    void draw();


}; // end of GameInstance class


#endif // end of header definition
