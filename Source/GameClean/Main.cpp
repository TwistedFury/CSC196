#include <SDL3/SDL.h>
#include <fmod.hpp>

#include "Renderer/Renderer.h"
#include "Renderer/Model.h"
#include "Core/Random.h"
#include "Math/Math.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Core/Time.h"
#include "Input/InputSystem.h"
#include "Game/Actor.h"

#include <iostream>

static void LoadSounds(FMOD::System* audio, std::vector<FMOD::Sound*>& sounds)
{
    void* extradriverdata = nullptr;
    audio->init(32, FMOD_INIT_NORMAL, extradriverdata);

    // Play a test sound
    FMOD::Sound* sound = nullptr;
    audio->createSound("pacman_start.wav", FMOD_DEFAULT, 0, &sound);

    audio->playSound(sound, 0, false, nullptr);

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

int main(int argc, char* argv[]) {
    // Initialize Engine Systems

    swaws::Time time;

    swaws::Renderer renderer;

    renderer.Initialize();
    renderer.CreateWindow("Swaws Engine", 1280, 1024); 

    swaws::InputSystem input;
    input.Initialize();

    // Initialize Audio
    // create audio system
    FMOD::System* audio;
    FMOD::System_Create(&audio);


    // Loading Drum Sounds
    std::vector<FMOD::Sound*> sounds;
    LoadSounds(audio, sounds);

    swaws::vec2 v(30, 40);

    std::vector<swaws::vec2> model_points{
        { -5, -5 },
        { 5, -5 },
        { 5, 5 },
        { -5, 5 }
    };

    swaws::vec3 color{ 1, 1, 1 };
    swaws::Model model(model_points, color);
    swaws::Transform transform(swaws::vec2{540, 620}, 0, 2);

    for (int i = 0; i < 10; i++) 
    {
        swaws::Actor actor{ transform, model };
    }

    SDL_Event e;
    bool quit = false;

    std::vector<swaws::vec2> points;

    // MAIN LOOP
    while (!quit) {
        time.Tick();
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        // STEP ONE (CLICK)
        if (input.GetMouseButtonPressed(swaws::InputSystem::MouseButton::Left) &&
            !input.GetKeyDown(SDL_SCANCODE_LSHIFT)) {
            points.push_back(input.GetMousePosition());
        }

        // STEP TWO (&DRAG)
        if (input.GetMouseButtonDown(swaws::InputSystem::MouseButton::Left) &&
            input.GetKeyDown(SDL_SCANCODE_LSHIFT)) {
            swaws::vec2 position = input.GetMousePosition();
            if (points.empty()) points.push_back(position);
            else if (position.Length(points.back()) > 10) points.push_back(position);
        }

        // UNDO
        if (input.GetKeyPressed(SDL_SCANCODE_Z) && input.GetKeyDown(SDL_SCANCODE_LCTRL)) {
            if (!points.empty()) {
                points.pop_back();
            }
		}

        // AUDIO HANDLING && INPUT

        // Q = BASS_DRUM
        if (input.GetKeyDown(SDL_SCANCODE_Q) && !input.GetPreviousKeyDown(SDL_SCANCODE_Q)) audio->playSound(sounds[0], 0, false, 0);
        // W = SNARE
        if (input.GetKeyDown(SDL_SCANCODE_W) && !input.GetPreviousKeyDown(SDL_SCANCODE_W)) audio->playSound(sounds[1], 0, false, 0);
        // E = OPEN-HAT
        if (input.GetKeyDown(SDL_SCANCODE_E) && !input.GetPreviousKeyDown(SDL_SCANCODE_E)) audio->playSound(sounds[2], 0, false, 0);
        // R = CLOSE-HAT
        if (input.GetKeyDown(SDL_SCANCODE_R) && !input.GetPreviousKeyDown(SDL_SCANCODE_R)) audio->playSound(sounds[3], 0, false, 0);
        // T = CLAP
        if (input.GetKeyDown(SDL_SCANCODE_T) && !input.GetPreviousKeyDown(SDL_SCANCODE_T)) audio->playSound(sounds[4], 0, false, 0);
        // Y = COWBELL
        if (input.GetKeyDown(SDL_SCANCODE_Y) && !input.GetPreviousKeyDown(SDL_SCANCODE_Y)) audio->playSound(sounds[5], 0, false, 0);

        // Update Engine Systems
        input.Update();
        audio->update();

        float speed = 200;

        swaws::vec2 direction{ 0, 0 };
        if (input.GetKeyDown(SDL_SCANCODE_W)) direction.y = -1;
        if (input.GetKeyDown(SDL_SCANCODE_S)) direction.y = 1;
        if (input.GetKeyDown(SDL_SCANCODE_A)) direction.x = -1;
        if (input.GetKeyDown(SDL_SCANCODE_D)) direction.x = 1;

        if (direction.LengthSqr() > 0) 
        {
            direction = direction.Normalized();
            transform.position += (direction * speed) * time.GetDeltaTime();
        }
        swaws::vec3 color{ 1, 0, 0 };

        renderer.Clear(); // Clear the renderer

        for (int i = 0; i < (int)points.size() - 1; i++) {
            // set color or random color
            // I choose random
            renderer.SetColor((uint8_t)swaws::random::GetRandom(256), swaws::random::GetRandom(256), swaws::random::GetRandom(256), swaws::random::GetRandom(256)); // Set render draw color to random color
            renderer.DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
        }
        model.Draw(renderer, transform);

		// Reset color
        renderer.SetColor((uint8_t)0, 0, 0);
        renderer.Present();

    }

    renderer.ShutDown();

    return 0;
}