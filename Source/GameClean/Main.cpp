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
#include "Game/Scene.h"

#include "Game/Player.h"

#include <iostream>
#include <memory>

static void LoadSounds(FMOD::System* audio, std::vector<FMOD::Sound*>& sounds)
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

int main(int argc, char* argv[]) {
    // Initialize Engine Systems

    swaws::Time time;

    std::unique_ptr<swaws::Renderer> renderer = std::make_unique<swaws::Renderer>();

    renderer->Initialize();
    renderer->CreateWindow("Swaws Engine", 1280, 1024); 

    std::unique_ptr<swaws::InputSystem> input = std::make_unique<swaws::InputSystem>();
    input->Initialize();

    // Initialize Audio
    // create audio system
    std::unique_ptr<FMOD::System> audio = std::make_unique<FMOD::System>();
    FMOD::System_Create(&audio);


    // Loading Drum Sounds
    std::vector<FMOD::Sound*> sounds;
    LoadSounds(*audio, sounds);

    swaws::vec2 v(30, 40);

    std::vector<swaws::vec2> model_points{
        { -5, -5 },
        { 5, -5 },
        { 5, 5 },
        { -5, 5 },
        {-5, -5}
    };

    std::shared_ptr<swaws::Model> model = std::make_shared < swaws::Model>(model_points, swaws::vec3{ 0, 1, 1 });

    swaws::Scene scene;
    for (int i = 0; i < 10; i++) 
    {
        swaws::Transform transform(swaws::vec2{ swaws::random::GetRandomFloat() * 1280, swaws::random::GetRandomFloat() * 1020});
        std::unique_ptr<Player> player = std::make_unique<Player>(transform, model);
        scene.AddActor(std::move(player));
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
        if (input->GetMouseButtonPressed(swaws::InputSystem::MouseButton::Left) &&
            !input->GetKeyDown(SDL_SCANCODE_LSHIFT)) {
            points.push_back(input->GetMousePosition());
        }

        // STEP TWO (&DRAG)
        if (input->GetMouseButtonDown(swaws::InputSystem::MouseButton::Left) &&
            input->GetKeyDown(SDL_SCANCODE_LSHIFT)) {
            swaws::vec2 position = input->GetMousePosition();
            if (points.empty()) points.push_back(position);
            else if (position.Length(points.back()) > 10) points.push_back(position);
        }

        // UNDO
        if (input->GetKeyPressed(SDL_SCANCODE_Z) && input->GetKeyDown(SDL_SCANCODE_LCTRL)) {
            if (!points.empty()) {
                points.pop_back();
            }
		}

        // AUDIO HANDLING && INPUT

        // Q = BASS_DRUM
        if (input->GetKeyDown(SDL_SCANCODE_Q) && !input->GetPreviousKeyDown(SDL_SCANCODE_Q)) audio->playSound(sounds[0], 0, false, 0);
        // W = SNARE
        if (input->GetKeyDown(SDL_SCANCODE_W) && !input->GetPreviousKeyDown(SDL_SCANCODE_W)) audio->playSound(sounds[1], 0, false, 0);
        // E = OPEN-HAT
        if (input->GetKeyDown(SDL_SCANCODE_E) && !input->GetPreviousKeyDown(SDL_SCANCODE_E)) audio->playSound(sounds[2], 0, false, 0);
        // R = CLOSE-HAT
        if (input->GetKeyDown(SDL_SCANCODE_R) && !input->GetPreviousKeyDown(SDL_SCANCODE_R)) audio->playSound(sounds[3], 0, false, 0);
        // T = CLAP
        if (input->GetKeyDown(SDL_SCANCODE_T) && !input->GetPreviousKeyDown(SDL_SCANCODE_T)) audio->playSound(sounds[4], 0, false, 0);
        // Y = COWBELL
        if (input->GetKeyDown(SDL_SCANCODE_Y) && !input->GetPreviousKeyDown(SDL_SCANCODE_Y)) audio->playSound(sounds[5], 0, false, 0);

        // Update Engine Systems
        input->Update();
        audio->update();

        float speed = 200;

        swaws::vec2 direction{ 0, 0 };
        if (input->GetKeyDown(SDL_SCANCODE_W)) direction.y = -1;
        if (input->GetKeyDown(SDL_SCANCODE_S)) direction.y = 1;
        if (input->GetKeyDown(SDL_SCANCODE_A)) direction.x = -1;
        if (input->GetKeyDown(SDL_SCANCODE_D)) direction.x = 1;

        if (direction.LengthSqr() > 0) 
        {
            direction = direction.Normalized();
            for (auto& act : scene.GetActors())
            {
                act->GetTransform().position += (direction * speed) * time.GetDeltaTime();
            }
        }
        swaws::vec3 color{ 0, 0, 0 };

        renderer->Clear(); // Clear the renderer

        for (int i = 0; i < (int)points.size() - 1; i++) {
            // set color or random color
            // I choose random
            renderer->SetColor((uint8_t)swaws::random::GetRandom(256), swaws::random::GetRandom(256), swaws::random::GetRandom(256), swaws::random::GetRandom(256)); // Set render draw color to random color
            renderer->DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
        }

        for (auto& act : scene.GetActors())
        {
            act->Draw(*renderer);
        }

		// Reset color
        renderer->SetColor((uint8_t)0, 0, 0);
        renderer->Present();

    }

    renderer->ShutDown();

    return 0;
}