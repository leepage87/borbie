#include "audioSystem.h"

#include <iostream>


AudioSystem::AudioSystem(){
    this->musicChannel = 0;
    this->ambianceChannel = 0;
    this->playerPosition = { 0.0f, 0.0f, 0.0f };
    
    /*int              key;
    bool             listenerflag = true;
    unsigned int     version;*/
    
    FMOD_RESULT result;
    
    result = FMOD::System_Create(&system);
    if(result != FMOD_OK)
        std::cout << "FMOD ERROR: System_Create failed." << std::endl;
    
    // TODO: parameters?
    result = system->init(10, FMOD_INIT_NORMAL, 0);
    if(result != FMOD_OK)
        std::cout << "FMOD ERROR: system init failed." << std::endl;
    
    // TODO: debug - remove
    int numchannels = 0;
    result = system->getHardwareChannels(&numchannels);
    if(result != FMOD_OK)
        std::cout << "FMOD ERROR: getChannels failed." << std::endl;
    else
        std::cout << "FMOD -- number channels = " << numchannels << std::endl;
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


// Attempts to load and play the sound file given by the string parameter.
//  If <looped> parameter is set to true, the sound will repeat continuously
//  until manually stopped (or until the AudioSystem object is deleted).
// Sounds played through the playMusic call will be played in the dedicated
//  music sound channel, and will play in standard 2D stereo mode.
// TODO: maybe add a global musicSound pointer, and just release it if a new
//  song is to be played. Then release it if it exists in the destructor.
void AudioSystem::playMusic(const char *file, bool looped){
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


void AudioSystem::pauseMusic(){
    if(this->musicChannel)
        this->musicChannel->setPaused(true);
}

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
































