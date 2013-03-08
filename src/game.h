/*	File: game.h
 *	Authors: idk your names
 *
 *	Description: this file contains the class declaration for the
 *	Game class. This object is responsible for starting the
 *	game, initializaing the Irrlicht engine, and then switching between
 *	the primary high-level phases of the game (i.e. main menu and
 *	game instance). It "glues" main game pieces together under the
 *	game engine's roof.
 */

#ifndef GAME_H
#define GAME_H

//System includes
#include <irrlicht.h>

//Game Includes
#include "borbiesEventReceiver.h"
#include "gameInstance.h"


/* RuntimeOptions: enum (constant definitions):
 *	16-bit flags allow for bitwise or operations
 *	to have a single option be represented as multiple
 *	values.
 * EXAMPLE (this is 8-bit):
 * 		00000001	= debug				= hex 0x01, or dec 1
 * and	00000010	= fullscreen		= hex 0x02, or dec 2
 * and	00000100	= something			= hex 0x04, or dec 4
 * and	00001000	= something_else	= hex 0x08, or dec 8
 *	So, (using | as the bitwise or operator), set (unsigned)
 *	unit options = debug | fullscreen | something =
 *		00000111
 * Then to check the values that are flagged, use
 *	options & debug = (bitwise)
 *		00000111 & 00000001 =
 *		00000001 = true,
 *	and options & something_else = (bitwise)
 *		00000111 & 00001000 =
 *		00000000 = false.
 *	For 16-bit, use 0x0001... for 32-bit, use 0x00000001, etc.
 */
enum RuntimeOptions {
	BORBIE_DEBUG_MODE	= 0x0001,
	BORBIE_FULLSCREEN	= 0x0002
};


// Game Class
class Game {
  private:
	// pointers to all internal Irrlicht engine objects used in the game:
    irr::IrrlichtDevice *device;
    irr::IEventReceiver *receiver;
    irr::video::IVideoDriver* driver;
    irr::scene::ISceneManager *smgr;
    
    // pointers to all internal Borbie-related objects:
    GameInstance *gameInstance;


  public:
  	// constructor/destructor
	Game();
	~Game();
	
	// start the game
    int run(unsigned int runMode);


}; // end of Game class


#endif
