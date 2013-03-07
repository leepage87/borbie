/* 
 * Borbie's Big Adventure: LET'S HIT THE TOWN! main file
 * Programmers: Lee Page
 *              Jonathan Miodownik
 *              Richard Teamco
 *              Ian Madigan
*/

#include "game.h"

int main(int argc, char ** argv) {
	bool BORBIE_DEBUG_MODE = false;
	if(argc > 1){
		bool BORBIE_DEBUG_MODE = true;
	}
	
	Game *game = new Game();
	game->run();

	return 0;
}

