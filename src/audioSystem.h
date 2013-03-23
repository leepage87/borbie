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

// c++ standard library includes
#include <vector>

// System includes
#include <irrlicht.h>
#include "fmod.hpp"
#include "fmod_errors.h"

// scale: divides the actual coordinates by this scale
#define AUDIO_WORLD_SCALE 100.0f
// max distance 3D audio can be heard (plays at minimum volume if further)
#define AUDIO_MAX_DISTANCE 500.0f


// SoundClip: contains data
struct SoundClip {
    FMOD::Sound *sound;
    const char *file;
};


// AudioSystem Class
class AudioSystem {
  private:
    // FMOD system variables
    FMOD::System *system;
    
    // primary audio channels
    FMOD::Channel *musicChannel;
    FMOD::Channel *ambianceChannel;
    
    // list of all active sound objects
    std::vector<SoundClip> activeSounds;
    
    // internal helper functions
    void playMusic(const char *file, bool looped);
    void playSound3d(
        const char *file,
        irr::core::vector3df sourcePos,
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
        const irr::core::vector3df playerPos,
        const irr::core::vector3df playerRot
    );
    
    // 3D Sound Functions
    
    
    /* TODO: add these functions (or most of them):
    
    void setMusicCrossFade(unsigned int miliseconds);
    
    void setPlayerPosition(irr::core::vector3df position);
    
    void playSound3d(char *file, irr::core::vector3df source, float vol = 1.0);
    void playSound3d(char *file, irr::scene::IMeshSceneNode *source);
    
    void encache(char *file);
    void decache(char *file);
    void clearCache();
    
    */


}; // end of AudioSystem class


#endif
