#pragma once
#include "fmod.hpp"
#include <vector>

namespace swaws
{
	class AudioSystem
	{
	public:
		AudioSystem() = default;

		FMOD::System* GetAudio() { return audio; }

		void InitializeAudio() { FMOD::System_Create(&audio); }

		void LoadSounds();
		void playSound(uint8_t index, FMOD::ChannelGroup* channelGroup, bool paused, FMOD::Channel** channel) 
		{
			audio->playSound(sounds[index], channelGroup, paused, channel);
		}

		void Update();

	private:
		FMOD::System* audio = nullptr;
		std::vector<FMOD::Sound*> sounds;
	};
}