/* Borbies Big Adventure: Let's Hit the Town!
 * Authors: teamKillYourself
 *
 * UPDATABLE "interface"
 *	Supports the update method for whichever objects require it.
 */

#ifndef UPDATABLE_H
#define UPDATABLE_H


// Updatable class: pure virtual, "interface" object
class Updatable {
  public:
  	virtual void update() = 0;

}; // end of Updatable class


#endif
