/*	Names, comments, etc.
 *
 *	GameObject is an abstract class that provides an interface of
 *	functions and values for all interactive game objects.
 *	This includes buildings, vehicles, NPCs, etc.
 */

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H


// GameObject definitions
//	TODO: modify as needed
#define GAME_OBJ_MAXHEALTH 1000


// GameObject class:
class GameObject {
  protected:
	int health;

  public:
	// default constructor: initializes standard object values
  	GameObject();
	
	// standard getters
	virtual int getHealth() const;
	
	// pure virtual functions (override mandatory)
	virtual void doDamage(int damage) = 0;
	virtual void applyCollision(int metaOfNotIntType) = 0;
	
}; // end of GameObject class


#endif
