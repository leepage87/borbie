/* 
 * Borbie's Big Adventure: LET'S HIT THE TOWN! main file
 * Programmers: Lee Page
 *              Jonathan Miodownik
 *              Richard Teamco
 *              Ian Madigan
*/

#include "game.h"

int main(int argc, char ** argv) {
	if(argc > 1){
		BORBIE_DEBUG_MODE = true;
	}
	else{
		BORBIE_DEBUG_MODE = false;
	}
	
	Game *game = new Game();
	game->run();

	return 0;
}

