/* 
 * Borbie's Big Adventure: LET'S HIT THE TOWN! main file
 * Programmers: Lee Page
 *              Jonathan Miodownik
 *              Richard Teamco
 *              Ian Madigan
*/

#include "game.h"
#include <iostream>
#include <string>

#include "mapSearcher.h"

/* main: determines runtime commands and attempts to run the game as such.
 * RUNTIME FLAGS: to add a runtime parameter, do "-x" after the executable
 *	command, where "x" represents the flag value.
 * FLAGS:
 *	d	debug: runs the game in debug mode (allows free movevement)
 *	f	fullscreen: runs the game in fullscreen (not recommended if broken)
 */
int main(int argc, char ** argv) {
    AStarPriorityQueue<int> q;
    q.enqueue(5);
    q.enqueue(3);
    q.enqueue(7);
    q.enqueue(6);
    q.enqueue(1);
    q.enqueue(4);
    q.enqueue(9);
    q.enqueue(5);
    std::cout << q.dequeue() << std::endl;
    std::cout << q.dequeue() << std::endl;
    q.enqueue(1);
    std::cout << q.dequeue() << std::endl;
    std::cout << q.dequeue() << std::endl;
    std::cout << q.dequeue() << std::endl;
	// loop through all arguments to determine which flags to set when
	//	constructing the game.
	/*unsigned int mode = 0;
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

	return 0; // END OF PROGRAM*/
}
