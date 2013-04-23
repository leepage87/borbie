/*	File: random.h
 *	Authors: teamKillYourself
 *
 *	Description: this file contains the class declaration of the static-based
 *  global random number generator, used by multiple objects, namely for
 *  creating randomly textures cars, buildings, spawning and movement, etc.
 */

#ifndef RANDOM_H
#define RANDOM_H

// c++ includes for random number generator
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */


// Random class:
class Random {


  public: // All static (globally accessible)
  
    // Initialize (seed) the random number generator. Do this ONLY ONCE,
    //  in the Game constructor, or the universe will explode and everything
    //  you ever knew and love will be gone. Forever.
	static void init();
	
	
	/*** RNG functions:
	    It is expected that all given values to calculate random numbers
	    are positive, and min < max in all cases.
	    If you pass in min = max, enjoy your (probably) error.
	 ***/
	
	// Returns a random integer between 0 and max-1.
	static int randomInt(int max);
	
	// Returns a random integer between min and max-1.
	static int randomInt(int min, int max);
	
	// Returns a random float between 0 and 1 (excluding 1).
	static float randomFloat();
	
	// Returns a random float between 0 and max (excluding max).
	static float randomFloat(float max);
	
	// Returns a random float between min and max (excluding max).
	static float randomFloat(float min, float max);
	
	
}; // end of Random class


#endif
