/*********************************************************************
 * File:     main.cpp
 * Authors:  Richard Teammco, Lee Page, Jonathan Miodownik

 * Function: this is the main file
 *********************************************************************/


#include "game.h"
#include <iostream>
#include <string>

/* main: determines runtime commands and attempts to run the game as such.
 * RUNTIME FLAGS: to add a runtime parameter, do "-x" after the executable
 *	command, where "x" represents the flag value.
 * FLAGS:
 *	d	debug: runs the game in debug mode (allows free movevement)
 *	f	fullscreen: runs the game in fullscreen (not recommended if broken)
 */
int main(int argc, char ** argv) {
	// loop through all arguments to determine which flags to set when
	//	constructing the game.
	unsigned int mode = 0;
	for(int i=1; i<argc; ++i){
		std::string arg = argv[i];
		if(arg[0] == '-'){ // if arg is a runtime flag
			// apply appropriate flags
			if(arg.find('d') != std::string::npos)
				mode = mode | BORBIE_DEBUG_MODE;
			if(arg.find('f') != std::string::npos)
				mode = mode | BORBIE_FULLSCREEN;
		}
	}
	
	Game *game = new Game(mode);

	game->run();
	
	// destructs the game object, in turn closing Irrlicht device,
	//  and fixing the screen resolution issue when running in fullscreen.
	delete game;

	return 0; // END OF PROGRAM
}
