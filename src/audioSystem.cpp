#include "audioSystem.h"

#include <iostream>
#include <math.h>


AudioSystem::AudioSystem(){
    this->musicChannel = 0;
    this->ambianceChannel = 0;
    
    FMOD_RESULT result;
    
    // create the FMOD sound system
    result = FMOD::System_Create(&system);
    if(result != FMOD_OK)
        std::cout << "FMOD ERROR: System_Create failed." << std::endl;
    
    // TODO: parameters?
    result = system->init(10, FMOD_INIT_NORMAL, 0);
    if(result != FMOD_OK)
        std::cout << "FMOD ERROR: system init failed." << std::endl;
    
    // set world size from centerpoint to edge (10k game units)
    system->setGeometrySettings(10000.0);
    
    // TODO: debug - remove
    int numchannels = 0;
    result = system->getHardwareChannels(&numchannels);
    if(result != FMOD_OK)
        std::cout << "FMOD ERROR: getChannels failed." << std::endl;
    else
        std::cout << "FMOD -- number channels = " << numchannels << std::endl;
    
    
    //system->set3DSettings(1.0f, 10000.0f, 1.0f);
    
    // TODO: remove
    /*FMOD_VECTOR listenerPosition2;
    listenerPosition2.x = 3000 / 100.0;
    listenerPosition2.y = 516 / 100.0;
    listenerPosition2.z = 4450 / 100.0;
    system->set3DListenerAttributes(0, &listenerPosition2, 0,0,0);
    system->update();*/
    
    playSound3d(
        "assets/sounds/yumyum.ogg",
        irr::core::vector3df(10000/100.0, 516/100.0, 4450/100.0),
        0.0,
        true);
}


AudioSystem::~AudioSystem(){

    /*FMOD_RESULT result;
    result = sound1->release();
    ERRCHECK(result);
    result = sound2->release();
    ERRCHECK(result);
    result = sound3->release();
    ERRCHECK(result);*/

    this->system->close();
    this->system->release();
}



/*** MUSIC CONTROL METHODS ***/

// (PRIVATE -- helper method)
// Attempts to load and play the sound file given by the string parameter.
//  If <looped> parameter is set to true, the sound will repeat continuously
//  until manually stopped (or until the AudioSystem object is deleted).
// Sounds played through the playMusic call will be played in the dedicated
//  music sound channel, and will play in standard 2D stereo mode.
// TODO: maybe add a global musicSound pointer, and just release it if a new
//  song is to be played. Then release it if it exists in the destructor.
void AudioSystem::playMusic(const char *file, bool looped){
    return; // TODO: stop returning
    FMOD_RESULT result;
    
    // create the sound from the given file path
    FMOD::Sound *musicSound;
    result = system->createSound(file, FMOD_SOFTWARE, 0, &musicSound);
    if(result != FMOD_OK)
        std::cout << "FMOD ERROR: createSound failed." << std::endl;
    
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
    
    //result = musicSound->release();
    // TODO: where to delete? memory leak atm? (maybe...)
}

// Attempts to load and start playing the sound file given by the parameter.
//  This method only plays the sound once: this DOES NOT LOOP the music.
// See playMusic(const char*, bool) above for playMusic specifications.
void AudioSystem::playMusic(const char *file){
    this->playMusic(file, false);
}

// Attempts to load and start playing the sound file given by the parameter.
//  This method causes the sound to continuously repeat: this LOOPS the music.
// See playMusic(const char*, bool) above for playMusic specifications.
void AudioSystem::playMusicLoop(const char *file){
    this->playMusic(file, true);
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
//  be between 0.0 and 1.0 (float). Does nothing if the music channel is
//  null/un-initialized.
void AudioSystem::setMusicVolume(const float vol){
    if(vol < 0.0 || vol > 1.0)
        std::cout << "Volume must be between 0.0 and 1.0." << std::endl;
    else if(this->musicChannel){
        this->musicChannel->setVolume(vol);
    }
}



/*** 3D SOUND CONTROL METHODS ***/

// (PRIVATE -- helper method)
// Attempts to play 3D sound TODO: memory management
// NOTE: the FMOD system uses the system's global listener position as
//  the sound's origin reference point. Thus, if your player's position
//  was never updated, the sounds position will be RELATIVE to 0,0,0
void AudioSystem::playSound3d(
    const char *file, irr::core::vector3df sourcePos,
    const float volume, bool looped)
{
    FMOD_RESULT result;
    FMOD::Sound *sound;
    FMOD::Channel *soundChannel;
    
    // create the sound from the given file path
    result = system->createSound(file, FMOD_SOFTWARE | FMOD_3D, 0, &sound);
    if(result != FMOD_OK)
        std::cout << "FMOD ERROR: 3dcreateSound failed." << std::endl;
    
    // set looped on or off, depending on parameter
    if(looped)
        result = sound->setMode(FMOD_LOOP_NORMAL);
    else
        result = sound->setMode(FMOD_LOOP_OFF);
    if(result != FMOD_OK)
        std::cout << "FMOD ERROR: 3dsetMode (sound) failed." << std::endl;
    
    // setup 3D sound flags
    result = sound->set3DMinMaxDistance(4.0f, AUDIO_MAX_DISTANCE);
    if(result != FMOD_OK)
        std::cout << "FMOD ERROR: 3dset3dMinMaxDistance failed." << std::endl;
    
    // attempt to play the sound file in the music channel.
    result = system->playSound(FMOD_CHANNEL_FREE, sound, 0,
        &soundChannel);
    if(result != FMOD_OK)
        std::cout << "FMOD ERROR: 3dplaySound failed." << std::endl;
    
    // set the sound position in 3D space
    FMOD_VECTOR pos;
    pos.x = sourcePos.X;
    pos.y = sourcePos.Y;
    pos.z = sourcePos.Z;
    result = soundChannel->set3DAttributes(&pos, 0);
    if(result != FMOD_OK)
        std::cout << "FMOD ERROR: 3dset3dAttributes failed: " << std::endl;
    
    // add the loaded sound into the sound list
    this->activeSounds.push_back(SoundClip());
    int lastIndex = this->activeSounds.size() - 1;
    this->activeSounds[lastIndex].sound = sound;
    this->activeSounds[lastIndex].file = file;
    
    // update FMOD system
    this->system->update();
}



/*** SYSTEM UPDATE METHOD ***/

// Updates the global 3D sound environment with the listener position
//  and orientation of the player (pass in vectors from the camera
//  or player node - wherever you want to "hear" your sound from).
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
    
    // update the audio system
    system->update();
}





























