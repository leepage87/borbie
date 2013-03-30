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

// scale: divides the actual coordinates by this scale
#define AUDIO_WORLD_SCALE 100.0f
// max distance 3D audio can be heard (plays at minimum volume if further)
#define AUDIO_MAX_DISTANCE 500.0f


// SoundClip: typdef for FMOD::Sound!
typedef FMOD::Sound SoundClip;


// AudioSystem Class
class AudioSystem {
  private:
    // FMOD system variables
    FMOD::System *system;
    
    // dedicated FMOD audio channels
    FMOD::Channel *musicChannel;
    FMOD::Channel *ambianceChannel;
    
    // private helper functions: music playback
    SoundClip* playMusic(const char *file, bool looped);
    void playMusic(SoundClip *musicSound, bool looped);

    
  public:
    AudioSystem();
    ~AudioSystem();
    
    // TODO: perhaps some kind of error-checking system?
    
    // Global sound functions
    //SoundClip* createSound2d(const char *file);
    //SoundClip* createSound3d(const char *file);
    //void dropSound(SoundClip *sound);
    //void setGlobalVolume(const float vol);
    //void setAudioPath(const char *path);
    
    /* TODO: add these functions (or most of them):
    void setMusicCrossFade(unsigned int miliseconds);
    void playSound3d(char *file, irr::scene::IMeshSceneNode *source);
    void dropSoundWhenFinished(SoundClip *, Channel *);
    */
    
    // Music Playback Functions - plays on dedicated music channel
    SoundClip* playMusic(const char *file);
    SoundClip* playMusicLoop(const char *file);
    void playMusic(SoundClip *sound);
    void playMusicLoop(SoundClip *sound);
    void pauseMusic();
    void resumeMusic();
    void setMusicVolume(const float vol);
    
    // 3D Sound Functions
    SoundClip* playSound3d(const char *file,
        irr::core::vector3df sourcePos,
        const float volume = 1.0f);
    void playSound3d(SoundClip *sound,
        irr::core::vector3df sourcePos,
        const float volume = 1.0f);
    
    //auto-tracking 3D objects "following" Irrlicht nodes
    
    
    // 3D sound update -- must be called every frame in the game loop
    void update(
        const irr::core::vector3df playerPos,
        const irr::core::vector3df playerRot
    );
    

}; // end of AudioSystem class


#endif
