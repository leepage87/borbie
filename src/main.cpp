/* 
 * Borbie's Big Adventure: LET'S HIT THE TOWN! main file
 * Programmers: Lee Page
 *              Jonathan Miodownik
 *              Richard Teamco
 *              Ian Madigan
*/

#include "game.h"

int main(int argc, char ** argv) {
	int mode = BORBIE_GAME_MODE;
	if(argc > 1){
		mode = BORBIE_DEBUG_MODE;
	}
	
	Game *game = new Game();
	game->run(mode);

	return 0;
}
