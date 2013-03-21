/*	File: audioSystem.h
 *	Authors: teamKillYourself
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
 *
 *  TESTED AUDIO FILE FORMATS (might support more):
 *      .ogg
 *      .wav
 *      .mp3
 */

#ifndef AUDIO_SYSTEM_H
#define AUDIO_SYSTEM_H

// System includes
#include <irrlicht.h>
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
    
    // primary sound objects
    
    // game sound variables
    FMOD_VECTOR playerPosition;
    
    // internal helper functions
    void playMusic(const char *file, bool looped);
    void playSound3d(
        const char *file,
        irr::core::vector3df source,
        const float volume,
        bool looped);

    
  public:
    AudioSystem();
    ~AudioSystem();
    
    // TODO: perhaps these functions can return int error codes
    
    // Global sound functions
    //void setGlobalVolume(const float vol);
    
    // Music Playback Functions
    void playMusic(const char *file);
    void playMusicLoop(const char *file);
    void pauseMusic();
    void resumeMusic();
    void setMusicVolume(const float vol);
    
    // 3D sound management functions
    void update(
        const irr::core::vector3df playerPos
        //const irr::core::vector3df playerForwardOrientation = 0,
        //const irr::core::vector3df playerUpOrientation = 0
    );
    
    // 3D Sound Functions
    
    
    /* TODO: add these functions (or most of them):
    
    void setMusicCrossFade(unsigned int miliseconds);
    
    void setPlayerPosition(irr::core::vector3df position);
    
    void playSound3d(char *file, irr::core::vector3df source);
    void playSound3d(char *file, irr::scene::IMeshSceneNode *source);
    
    void encache(char *file);
    void decache(char *file);
    void clearCache();
    
    */


}; // end of AudioSystem class


#endif
