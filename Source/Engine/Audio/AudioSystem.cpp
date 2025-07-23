#include "AudioSystem.h"

namespace swaws
{
    /// <summary>
    /// Loads a set of predefined sound files into the audio system.
    /// </summary>
    void AudioSystem::LoadSounds()
    {
        void* extradriverdata = nullptr;
        audio->init(32, FMOD_INIT_NORMAL, extradriverdata);

        FMOD::Sound* sound = nullptr;

        audio->createSound("bass.wav", FMOD_DEFAULT, 0, &sound);
        sounds.push_back(sound);

        audio->createSound("snare.wav", FMOD_DEFAULT, 0, &sound);
        sounds.push_back(sound);

        audio->createSound("open-hat.wav", FMOD_DEFAULT, 0, &sound);
        sounds.push_back(sound);

        audio->createSound("close-hat.wav", FMOD_DEFAULT, 0, &sound);
        sounds.push_back(sound);

        audio->createSound("clap.wav", FMOD_DEFAULT, 0, &sound);
        sounds.push_back(sound);

        audio->createSound("cowbell.wav", FMOD_DEFAULT, 0, &sound);
        sounds.push_back(sound);
    }

    /// <summary>
    /// Updates the state of the audio system.
    /// </summary>
    void AudioSystem::Update()
    {
        //
    }
}
