#pragma once
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

        AddSound("bass.wav", "bass");
        AddSound("snare.wav", "snare");
        AddSound("open-hat.wav", "open-hat");
        AddSound("close-hat.wav", "close-hat");
        AddSound("clap.wav", "clap");
        AddSound("cowbell.wav", "cowbell");
    }

    void AudioSystem::AddSound(const char* name_or_data, std::string refName)
    {
        FMOD::Sound* sound = nullptr;
        audio->createSound(name_or_data, FMOD_DEFAULT, 0, &sound);
        sounds[refName] = sound;
    }

    /// <summary>
    /// Updates the state of the audio system.
    /// </summary>
    void AudioSystem::Update()
    {
        //
    }

    /// <summary>
    /// Shuts down the audio system and releases associated resources.
    /// </summary>
    void AudioSystem::Shutdown()
    {
        //
    }
}
