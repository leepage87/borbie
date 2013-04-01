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
 *  Special thanks to http://www.online-convert.com for converting the
 *      provided .chm documentation file to an actually usable pdf file.
 *
 *  TESTED AUDIO FILE FORMATS (most likely supports more):
 *      .ogg
 *      .wav
 *      .mp3
 *
 *  FMOD LICENCE: FMod is free for non-commercial use. Commercial use for
 *      low-budget (i.e. < $100k) is $500 per title. For any type of product
 *      distribution (even non-commercial), a credit line is required:
 *      "Audio engine : FMOD Sound System by Firelight Technologies"
 *      (or something similar). See http://www.fmod.org/fmod-sales.html
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


// SoundClip: typdef for FMOD::Sound
typedef FMOD::Sound SoundClip;


// AudioSystem class
class AudioSystem {

  private:
    // FMOD system variables
    FMOD::System *system;
    
    // dedicated FMOD audio channels
    FMOD::Channel *musicChannel;
    FMOD::Channel *ambianceChannel;
    
    // private helper functions: music playback
    SoundClip* playMusic(const char *file, bool looped);
    void playMusic(FMOD::Sound *musicSound, bool looped);
    
    // private helper function: target follow 3D sound
    void playSound3dFollowTarget(FMOD::Sound *sound,
        irr::scene::ISceneNode *target,
        float volume, bool looped);

    
  public:
    // Constructor - initializes FMOD system and music/ambiance channels.
    AudioSystem();
    // Destructor - cleans up FMOD system. DOES NOT clean up individual sounds.
    //  Use  "SoundClip* -> release()"  to delete sounds.
    ~AudioSystem();
    
    // TODO: perhaps some kind of error-checking system?
    
    // Global sound functions
    SoundClip* createSound2d(const char *file);
    SoundClip* createSound3d(const char *file);
    
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
    void setMusicVolume(float volume);
    
    // TODO: same for ambiance as music
    
    // TODO: custom dedicated channels?
    
    // 3D Sound Functions - plays once, then channel is gone
    SoundClip* playSound3d(const char *file,
        irr::core::vector3df sourcePos,
        float volume = 1.0f);
    void playSound3d(SoundClip *sound,
        irr::core::vector3df sourcePos,
        float volume = 1.0f);
    
    // 3D Sound "Follow" - follows the object
    SoundClip *playSound3d(const char *file,
        irr::scene::ISceneNode *target,
        float volume = 1.0f);
    void playSound3d(SoundClip *sound,
        irr::scene::ISceneNode *target,
        float volume = 1.0f);
    // 3D Sound "Follow" with Loop
    SoundClip *playSound3dLoop(const char *file,
        irr::scene::ISceneNode *target,
        float volume = 1.0f);
    void playSound3dLoop(SoundClip *sound,
        irr::scene::ISceneNode *target,
        float volume = 1.0f);
    
    
    // 2D Sound Functions - plays once, then channel is gone
    
    // auto-tracking 3D objects "following" Irrlicht nodes
    
    
    // 3D sound update -- must be called every frame in the game loop
    void update(
        const irr::core::vector3df playerPos,
        const irr::core::vector3df playerRot
    );
    

}; // end of AudioSystem class


#endif
