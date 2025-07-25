#pragma once
#include "fmod.hpp"
#include <map>
#include <string>

namespace swaws
{
	class AudioSystem
	{
	public:
		AudioSystem() = default;

		FMOD::System* GetAudio() { return audio; }

		void InitializeAudio() { FMOD::System_Create(&audio); }

		void LoadSounds();
		void playSound(std::string refName, FMOD::ChannelGroup* channelGroup, bool paused, FMOD::Channel** channel) 
		{
			audio->playSound(sounds[refName], channelGroup, paused, channel);
		}
		void AddSound(const char* name_or_data, std::string refName);

		void Update();
		void Shutdown();

	private:
		FMOD::System* audio = nullptr;
		std::map<std::string, FMOD::Sound*> sounds;
	};
}