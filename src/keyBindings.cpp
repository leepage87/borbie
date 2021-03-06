/*********************************************************************
 * File:     keyBindings.cpp
 * Authors:  Richard Teammco, Lee Page, Jonathan Miodownik

 * Function: Helper class use to clean up key bindings settings
 *********************************************************************/

#include "keyBindings.h"

using namespace irr;


/*********************************************************************
 * Constructor: Initializes the keyMap
 *********************************************************************/
KeyBindings::KeyBindings(SKeyMap *keyMap){
  this->keyMap = keyMap;
}

/*********************************************************************
 * Binds WASD, space, and arrow keys to relative movement
 *********************************************************************/
void KeyBindings::setKeys()
{
 // forward movement (UP arrow and W)
	keyMap[0].Action = EKA_MOVE_FORWARD;
	keyMap[0].KeyCode = KEY_UP;
	keyMap[1].Action = EKA_MOVE_FORWARD;
	keyMap[1].KeyCode = KEY_KEY_W;
	// backwards movement (DOWN arrow and S)
	keyMap[2].Action = EKA_MOVE_BACKWARD;
	keyMap[2].KeyCode = KEY_DOWN;
	keyMap[3].Action = EKA_MOVE_BACKWARD;
	keyMap[3].KeyCode = KEY_KEY_S;
	// left movement (LEFT arrow and A)
	keyMap[4].Action = EKA_STRAFE_LEFT;
	keyMap[4].KeyCode = KEY_LEFT;
	keyMap[5].Action = EKA_STRAFE_LEFT;
	keyMap[5].KeyCode = KEY_KEY_A;
	// left movement (RIGHT arrow and D)
	keyMap[6].Action = EKA_STRAFE_RIGHT;
	keyMap[6].KeyCode = KEY_RIGHT;
	keyMap[7].Action = EKA_STRAFE_RIGHT;
	keyMap[7].KeyCode = KEY_KEY_D;
	// jump action (SPACE)
	keyMap[8].Action = EKA_JUMP_UP;
	keyMap[8].KeyCode = KEY_SPACE;
	
 
}
