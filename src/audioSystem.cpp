/*	File: audioSystem.cpp
 *	Authors: teamKillYourself
 *
 *	Description: this file contains the class definitions for the
 *	AudioSystem class. This object is responsible for providing an interface
 *  wrapping the Audio library subsystem. It is responsible for abstracting
 *  the audio playback functionality within the game, allowing for 2D and 3D
 *  sounds in the virtual world, such as music or world sound effects.
 */

#include "audioSystem.h"

#include <iostream>
#include <math.h>


/* TODO list:
 *  - test 3D follow target sound
 *  - test volume setting
 *  - get rid of print statements
 */


// Constructor:
//  Attempts to create and initialize the FMOD::System object, which is later
//  used for all audio playback.
AudioSystem::AudioSystem(){
    this->musicChannel = 0;
    this->ambianceChannel = 0;
    
    FMOD_RESULT result;
    
    // create the FMOD sound system
    result = FMOD::System_Create(&system);
    if(result != FMOD_OK)
        std::cout << "FMOD ERROR: System_Create failed." << std::endl;
    
    // initialize the audio system
    result = system->init(
        10, // maximum number of audio channels that can play simultaneously
        FMOD_INIT_NORMAL, // system flags (normal)
        0); // extra driver data (ignored)
    if(result != FMOD_OK)
        std::cout << "FMOD ERROR: system init failed." << std::endl;
    
    // set world size from centerpoint to edge (10k game units)
    // TODO: huh?
    system->setGeometrySettings(10000.0);
    //system->set3DSettings(1.0f, 10000.0f, 1.0f);
    
    // TODO: remove
    //playSound3d(
    ////    "assets/sounds/yumyum.ogg",
    ////    irr::core::vector3df(10000/100.0, 516/100.0, 4450/100.0));
}


// Destructor:
//  Cleans up the AudioSystem from memory. All SoundClip objects collected
//  throughout your usage of the AudioSystem class should be released
//  separately by using SoundClip->release();
AudioSystem::~AudioSystem(){
    this->system->release();
}



/*** GLOBAL SOUND MANAGEMENT FUNCTIONS ***/

// Attempts to create a new 2D sound from the given file name.
// Use this to create sound objects during level loading, etc. On-the-fly
//  sound playback functions will also use this method.
// NOTE: If sound is intended for 3D use, use createSound3d method. Using a
//  2D sound will cause the system to disregard all 3D positioning.
// RETURNS the FMOD::Sound (SoundClip) object pointer, and if the sound could
//  not be created, RETURNS NULL POINTER.
SoundClip* AudioSystem::createSound2d(const char *file){
    FMOD_RESULT result;
    
    FMOD::Sound *sound;
    result = system->createSound(file, FMOD_SOFTWARE, 0, &sound);
    if(result != FMOD_OK){
        std::cout << "FMOD ERROR: createSound failed." << std::endl;
        return 0;
    }
    
    return sound;
}

// Attempts to create a new 3D sound from the given file name.
// Use this to create sound objects during level loading, etc. On-the-fly
//  sound playback functions will also use this method.
// NOTE: If sound is intended for 2D use, use createSound2d method. Using a
//  3D sound will result in it being played in default position (0, 0, 0)
// RETURNS the FMOD::Sound (SoundClip) object pointer, and if the sound could
//  not be created, RETURNS NULL POINTER.
SoundClip* AudioSystem::createSound3d(const char *file){
    FMOD_RESULT result;
    
    FMOD::Sound *sound;
    result = system->createSound(file, FMOD_SOFTWARE | FMOD_3D, 0, &sound);
    if(result != FMOD_OK){
        std::cout << "FMOD ERROR: 3dcreateSound failed." << std::endl;
        return 0;
    }
    
    return sound;
}



/*** MUSIC CONTROL METHODS ***/

// (PRIVATE -- helper method)
// Attempts to play the given SoundClip (FMOD::Sound) object on the dedicated
//  music channel. Can be called directly or via helper method.
// If <looped> parameter is set to true, the sound will repeat continuously
//  until manually stopped (or until the AudioSystem object is deleted).
// Sounds played through the playMusic call will be played in the dedicated
//  music sound channel, and will play in standard 2D stereo mode.
void AudioSystem::playMusic(FMOD::Sound *musicSound, bool looped){
    FMOD_RESULT result;
    
    // set looped on or off, depending on parameter
    if(looped)
        result = musicSound->setMode(FMOD_LOOP_NORMAL);
    else
        result = musicSound->setMode(FMOD_LOOP_OFF);
    if(result != FMOD_OK)
        std::cout << "FMOD ERROR: setMode (sound) failed." << std::endl;
    
    // attempt to play the sound file in the music channel.
    result = system->playSound(FMOD_CHANNEL_FREE, musicSound, 0,
        &(this->musicChannel));
    if(result != FMOD_OK)
        std::cout << "FMOD ERROR: playSound failed." << std::endl;
    
    // update FMOD system
    this->system->update();
}

// (PRIVATE -- helper method)
// Attempts to load and play the sound file given by the string parameter.
// If <looped> parameter is set to true, the sound will repeat continuously
//  until manually stopped (or until the AudioSystem object is deleted).
// Sounds played through the playMusic call will be played in the dedicated
//  music sound channel, and will play in standard 2D stereo mode.
// RETURNS: SoundClip / FMOD::Sound object pointer if successful;
//  returns 0 (NULL pointer) if something went wrong).
SoundClip* AudioSystem::playMusic(const char *file, bool looped){
    //return 0; // TODO: stop returning
    FMOD_RESULT result;
    
    // create the sound from the given file path
    FMOD::Sound *musicSound = this->createSound2d(file);
    
    // play the sound on the music channel
    this->playMusic(musicSound, looped);
    
    return musicSound;
}

// Attempts to load and start playing the sound file given by the parameter.
//  This method only plays the sound once: this DOES NOT LOOP the music.
// See playMusic(const char*, bool) above for playMusic specifications.
// RETURNS: Pointer to the played sound object (NULL if something goes wrong)
SoundClip* AudioSystem::playMusic(const char *file){
    return this->playMusic(file, false);
}

// Attempts to load and start playing the sound file given by the parameter.
//  This method causes the sound to continuously repeat: this LOOPS the music.
// See playMusic(const char*, bool) above for playMusic specifications.
// RETURNS: Pointer to the played sound object (NULL if something goes wrong)
SoundClip* AudioSystem::playMusicLoop(const char *file){
    return this->playMusic(file, true);
}

// Attempts to play the SoundClip (FMOD::Sound typedef) as a music clip.
//  This method only plays the sound once: this DOES NOT LOOP the music.
// See playMusic(SoundClip*, bool) above for playMusic specifications.
void AudioSystem::playMusic(SoundClip *sound){
    this->playMusic(sound, false);
}

// Attempts to play the SoundClip (FMOD::Sound typedef) as a music clip.
//  This method causes the sound to continuously repeat: this LOOPS the music.
// See playMusic(SoundClip*, bool) above for playMusic specifications.
void AudioSystem::playMusicLoop(SoundClip *sound){
    this->playMusic(sound, true);
}

// Attempts to pause the music channel if it's active. Does
//  nothing if already paused.
void AudioSystem::pauseMusic(){
    if(this->musicChannel)
        this->musicChannel->setPaused(true);
}

// Attempts to unpause the music channel if it's active. Does
//  nothing if already playing.
void AudioSystem::resumeMusic(){
    if(this->musicChannel)
        this->musicChannel->setPaused(false);
}

// Attempts to set the volume of the music channel. Volume is expected to
//  be between 0.0 (mute) and 1.0 (max) (float). Does nothing if the music
//  channel is null/un-initialized.
//  Volume less than 0 will be set to 0; vol > 1 will be set to 1.
void AudioSystem::setMusicVolume(float volume){
    // make sure volume is in the correct range
    if(volume < 0.0)
        volume = 0.0;
    else if(volume > 1.0)
        volume = 1.0;
    
    // if music channel isn't null, make the volume adjustment
    if(this->musicChannel){
        this->musicChannel->setVolume(volume);
    }
}



/*** 2D SOUND CONTROL METHODS ***/
void AudioSystem::playSound2d(SoundClip *sound, float volume){
    FMOD_RESULT result;
    
    // set looped to off (no loop!)
    result = sound->setMode(FMOD_LOOP_OFF);
    if(result != FMOD_OK)
        std::cout << "FMOD ERROR: 2dsetMode (sound) failed." << std::endl;
    
    // attempt to play the sound file in a new sound channel.
    FMOD::Channel *soundChannel;
    result = system->playSound(FMOD_CHANNEL_FREE, sound, 0,
        &soundChannel);
    if(result != FMOD_OK)
        std::cout << "FMOD ERROR: 2dplaySound failed." << std::endl;
    
    // make sure volume is in the correct range
    if(volume < 0.0)
        volume = 0.0;
    else if(volume > 1.0)
        volume = 1.0;
    // set the volume on the sound's channel
    result = soundChannel->setVolume(volume);
    if(result != FMOD_OK)
        std::cout << "FMOD ERROR: 2dsetVolume failed." << std::endl;
    
    // update FMOD system
    this->system->update();
}

SoundClip* AudioSystem::playSound2d(const char *file, float volume){
    FMOD::Sound *sound = this->createSound2d(file);
    this->playSound2d(sound, volume);
    
    return sound;
}



/*** 3D SOUND CONTROL METHODS ***/

// Attempts to play the given sound file in 3D space given by the Irrlicht
//  vector3df at the provided volume. Volume is expected to be between
//  0.0 (mute) and 1.0 (max) (float).
// Volume less than 0 will be set to 0; vol > 1 will be set to 1.
void AudioSystem::playSound3d(
    SoundClip *sound, irr::core::vector3df sourcePos, float volume)
{
    FMOD_RESULT result;
    
    // set looped to off (no loop!)
    result = sound->setMode(FMOD_LOOP_OFF);
    if(result != FMOD_OK)
        std::cout << "FMOD ERROR: 3dsetMode (sound) failed." << std::endl;
    
    // setup 3D sound flags
    result = sound->set3DMinMaxDistance(4.0f, AUDIO_MAX_DISTANCE);
    if(result != FMOD_OK)
        std::cout << "FMOD ERROR: 3dset3dMinMaxDistance failed." << std::endl;
    
    // attempt to play the sound file in a new sound channel.
    FMOD::Channel *soundChannel;
    result = system->playSound(FMOD_CHANNEL_FREE, sound, 0,
        &soundChannel);
    if(result != FMOD_OK)
        std::cout << "FMOD ERROR: 3dplaySound failed." << std::endl;
    
    // make sure volume is in the correct range
    if(volume < 0.0)
        volume = 0.0;
    else if(volume > 1.0)
        volume = 1.0;
    // set the volume on the sound's channel
    result = soundChannel->setVolume(volume);
    if(result != FMOD_OK)
        std::cout << "FMOD ERROR: 3dsetVolume failed." << std::endl;
    
    // set the sound position in 3D space
    FMOD_VECTOR pos;
    pos.x = sourcePos.X;
    pos.y = sourcePos.Y;
    pos.z = sourcePos.Z;
    result = soundChannel->set3DAttributes(&pos, 0);
    if(result != FMOD_OK)
        std::cout << "FMOD ERROR: 3dset3dAttributes failed: " << std::endl;
    
    // update FMOD system
    this->system->update();
}

// Attempts to play the given sound file in 3D space given by the Irrlicht
//  vector3df at the provided volume. Volume is expected to be between
//  0.0 (mute) and 1.0 (max) (float).
// Volume less than 0 will be set to 0; vol > 1 will be set to 1.
// RETURNS: SoundClip / FMOD::Sound object pointer if successful;
//  returns 0 (NULL pointer) if something went wrong).
SoundClip* AudioSystem::playSound3d(
    const char *file, irr::core::vector3df sourcePos, float volume)
{
    FMOD::Sound *sound = this->createSound3d(file);
    this->playSound3d(sound, sourcePos, volume);
    
    return sound;
}



/*** 3D TARGET FOLLOW SOUND CONTROL METHODS ***/

// (PRIVATE -- helper method)
// Attempts to play the given 3D sound attached to the provided Irrlicht
//  scene node as a target to follow. The sound is established in the initial
//  position of the given target node, and then is added to the list of
//  updated FollowSounds to be checked each frame for re-positioning.
// If <looped> parameter is set to TRUE, then the sound will keep looping
//  until the target node is destroyed (i.e. the pointer beomces null).
// Sound plays at the provided volume. Volume is expected to be between
//  0.0 (mute) and 1.0 (max) (float).
// Volume less than 0 will be set to 0; vol > 1 will be set to 1.
void AudioSystem::playSound3dFollowTarget(FMOD::Sound *sound,
    irr::scene::ISceneNode *target,
    float volume, bool looped)
{
    FMOD_RESULT result;
    
    // set looped on or off, depending on parameter
    if(looped)
        result = sound->setMode(FMOD_LOOP_NORMAL);
    else
        result = sound->setMode(FMOD_LOOP_OFF);
    if(result != FMOD_OK)
        std::cout << "FMOD ERROR: setMode (sound) failed." << std::endl;
    
    // setup 3D sound flags
    result = sound->set3DMinMaxDistance(4.0f, AUDIO_MAX_DISTANCE);
    if(result != FMOD_OK)
        std::cout << "FMOD ERROR: 3dset3dMinMaxDistance failed." << std::endl;
    
    // attempt to play the sound file in a new sound channel.
    FMOD::Channel *soundChannel;
    result = system->playSound(FMOD_CHANNEL_FREE, sound, 0,
        &soundChannel);
    if(result != FMOD_OK)
        std::cout << "FMOD ERROR: 3dplaySound failed." << std::endl;
    
    // make sure volume is in the correct range
    if(volume < 0.0)
        volume = 0.0;
    else if(volume > 1.0)
        volume = 1.0;
    // set the volume on the sound's channel
    result = soundChannel->setVolume(volume);
    if(result != FMOD_OK)
        std::cout << "FMOD ERROR: 3dsetVolume failed." << std::endl;
    
    // set the sound's initial position in 3D space
    irr::core::vector3df targetPos = target->getPosition();
    FMOD_VECTOR pos;
    pos.x = targetPos.X;
    pos.y = targetPos.Y;
    pos.z = targetPos.Z;
    result = soundChannel->set3DAttributes(&pos, 0);
    if(result != FMOD_OK)
        std::cout << "FMOD ERROR: 3dset3dAttributes failed: " << std::endl;
    
    // set up the follow target struct
    FollowSound newFollowSound;
    newFollowSound.channel = soundChannel;
    newFollowSound.target = target;
    this->followSounds.push_back(newFollowSound);
    
    // update FMOD system
    this->system->update();
}

// Attempts to load and start playing the sound file given by the parameter,
//  following the given Irrlicht scene node as a target at the provided volume.
// This method only plays the sound once: this DOES NOT LOOP the sound.
// See playSound3dFollowTarget above for follower sound specifications.
// RETURNS: Pointer to the played sound object (NULL if something goes wrong)
SoundClip* AudioSystem::playSound3d(const char *file,
    irr::scene::ISceneNode *target, float volume)
{
    FMOD::Sound *sound = this->createSound3d(file);
    this->playSound3dFollowTarget(sound, target, volume, false);
    
    return sound;
}

// Attempts to play the given SoundClip (FMOD::Sound typedef) as a 3D sound
//  following the given Irrlicht scene node as a target at the provided volume.
// This method only plays the sound once: this DOES NOT LOOP the sound.
// See playSound3dFollowTarget above for follower sound specifications.
void AudioSystem::playSound3d(SoundClip *sound,
    irr::scene::ISceneNode *target, float volume)
{
    this->playSound3dFollowTarget(sound, target, volume, false);
}

// Attempts to load and start playing the sound file given by the parameter,
//  following the given Irrlicht scene node as a target at the provided volume.
// This method causes the sound to continuously repeat: this LOOPS the sound
//  until the target node is destroyed (deleted).
// See playSound3dFollowTarget above for follower sound specifications.
// RETURNS: Pointer to the played sound object (NULL if something goes wrong)
SoundClip* AudioSystem::playSound3dLoop(const char *file,
    irr::scene::ISceneNode *target, float volume)
{
    FMOD::Sound *sound = this->createSound3d(file);
    this->playSound3dFollowTarget(sound, target, volume, true);
    
    return sound;
}

// Attempts to play the given SoundClip (FMOD::Sound typedef) as a 3D sound
//  following the given Irrlicht scene node as a target at the provided volume.
// This method causes the sound to continuously repeat: this LOOPS the sound
//  until the target node is destroyed (deleted).
// See playSound3dFollowTarget above for follower sound specifications.
void AudioSystem::playSound3dLoop(SoundClip *sound,
    irr::scene::ISceneNode *target, float volume)
{
    this->playSound3dFollowTarget(sound, target, volume, true);
}



/*** SYSTEM UPDATE METHOD ***/

// Updates the global 3D sound environment with the listener position
//  and orientation of the player (pass in vectors from the camera
//  or player node - wherever you want to "hear" your sound from).
// Also updates each of the FollowSound channel positions to the position
//  of its target Irrlicht scene node. If the following channel is done
//  playing, or if the followed target is deleted, the FollowSound is also
//  removed and no longer updated.
// Once update is finished, calls the FMOD audio system to update itself.
// This function should be called every frame
//  (possibly except when in the main menu or not playing 3D sounds).
void AudioSystem::update(
    const irr::core::vector3df playerPos,
    const irr::core::vector3df playerRot
){
// TODO: can use FPS counter to update velocity data. What is vel for?

    // get scaled 3D sound position of listener
    FMOD_VECTOR listenerPosition;
    listenerPosition.x = playerPos.X / AUDIO_WORLD_SCALE;
    listenerPosition.y = playerPos.Y / AUDIO_WORLD_SCALE;
    listenerPosition.z = playerPos.Z / AUDIO_WORLD_SCALE;
    
    // get 3D rotation (forward orientation) of listener:
    //  calculate radians from degrees
    float degree = playerRot.Y;
    float radians = (degree) * (M_PI/180);
    //  figure out rotation angles using sin, cos
    float fx = cos(radians);
    float fz = sin(radians);
    // set rotation vector based on calculated angles
    FMOD_VECTOR listenerRotation;
    listenerRotation.x = fz;
    listenerRotation.y = 0;
    listenerRotation.z = fx;
    
    // apply the attributes to the system
    system->set3DListenerAttributes(
        0,                  // listener id (0: only one listener)
        &listenerPosition,  // current listener position
        0,                  // how far moved since last update
        &listenerRotation,  // forward orientation of player
        0);                 // up orientation of player
    
    
    // update each of the FollowSounds
    int numFollowSounds = this->followSounds.size();
    for(int i=0; i<numFollowSounds; ++i){
        FollowSound fs = this->followSounds[i];
        // if target is lost or if channel is done playing, remove the sound
        bool isChannelPlaying;
        fs.channel->isPlaying(&isChannelPlaying);
        if(!fs.target || !isChannelPlaying) {
            followSounds.erase(followSounds.begin() + i);
            numFollowSounds--;
            i--;
        }
        // otherwise, update the channel's position to that of the target's
        else {
            irr::core::vector3df targetPos = fs.target->getPosition();
            FMOD_VECTOR pos;
            pos.x = targetPos.X;
            pos.y = targetPos.Y;
            pos.z = targetPos.Z;
            fs.channel->set3DAttributes(&pos, 0);
        }
    }
    
    
    // update the audio system
    system->update();
}
