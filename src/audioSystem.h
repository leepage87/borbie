/*	File: audioSystem.h
 *	Authors: idk your names
 *
 *	Description: this file contains the class declaration for the
 *	AudioSystem class. This object is responsible for providing an interface
 *  wrapping the Audio library subsystem. It is responsible for abstracting
 *  the audio playback functionality within the game, allowing for 2D and 3D
 *  sounds in the virtual world, such as music or world sound effects.
 *
 *  Currently, this class uses the FMOD audio library.
 *  See doc/fmodex.pdf for full documentation on this library.
 *  Special thanks to http://www.online-convert.com for converting
 *      the provided .chm file to an actually usable format.
 */

#ifndef AUDIO_SYSTEM_H
#define AUDIO_SYSTEM_H

// System includes
#include "fmod.hpp"
#include "fmod_errors.h"


// AudioSystem Class
class AudioSystem {
  private:
    // FMOD system variables
    FMOD::System *system;
    
    // primary audio channels
    FMOD::Channel *musicChannel;
    FMOD::Channel *ambianceChannel;
    
    // game sound variables
    FMOD_VECTOR playerPosition;
    
    // internal helper functions
    void playMusic(const char *file, bool looped);

    
  public:
    AudioSystem();
    ~AudioSystem();
    
    void playMusic(const char *file);
    void playMusicLoop(const char *file);
    void stopMusic();
    
    /* TODO: add these functions (or most of them):
    
    void playMusic(const char *file);
    void playMusicLoop(const char *file);
    void setCrossFade(unsigned int miliseconds);
    
    void setPlayerPosition(irr::core::vector3df position);
    
    void playSound3d(char *file, irr::core::vector3df source);
    void playSound3d(char *file, irr::scene::IMeshSceneNode *source);
    
    void encache(char *file);
    void decache(char *file);
    void clearCache();
    
    */


}; // end of AudioSystem class


#endif
