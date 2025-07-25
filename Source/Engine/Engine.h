#pragma once
#include <memory>

namespace swaws
{
	class Renderer; // Forward declaration allowed if not used **here**
	class AudioSystem;
	class InputSystem;
	class Time;

	class Engine
	{
	public:
		Engine() = default;

		bool Initialize();
		void Update();

		void Shutdown();
		void Draw();

		Renderer& GetRenderer() { return *renderer; }
		AudioSystem& GetAudioSystem() { return *audio; }
		InputSystem& GetInputSystem() { return *input; }
		Time& GetTime() { return *time; }

	private:
		std::unique_ptr<Time> time;
		std::unique_ptr<Renderer> renderer;
		std::unique_ptr<AudioSystem> audio;
		std::unique_ptr<InputSystem> input;
	};

	Engine& GetEngine();
}