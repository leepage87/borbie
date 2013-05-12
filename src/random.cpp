/*********************************************************************
 * File:     random.cpp
 * Authors:  Richard Teammco, Lee Page, Jonathan Miodownik
 * Function: this file contains the class definition of the static-based
 *           global random number generator, used by multiple objects,
 *           namely for creating randomly textures cars, buildings,
 *           spawning and movement, etc.
 *********************************************************************/

#include "random.h"

// c++ includes for random number generator
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */


// Seeds the c/c++ random number generator.
void Random::init() {
    srand(time(NULL));
}

// Returns a random integer between 0 and max-1.
int Random::randomInt(int max) {
    return rand() % max;
}

// Returns a random integer between min and max-1.
int Random::randomInt(int min, int max) {
    return min + Random::randomInt(max - min);
}

// Returns a random float between 0 and 1 (excluding 1).
float Random::randomFloat() {
    return (float)rand() / (float)RAND_MAX;
}

// Returns a random float between 0 and max (excluding max).
float Random::randomFloat(float max) {
    return Random::randomFloat() * max;
}

// Returns a random float between min and max (excluding max).
float Random::randomFloat(float min, float max) {
    return min + Random::randomFloat(max - min);
}
