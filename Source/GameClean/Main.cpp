#pragma once
#include <SDL3/SDL.h>
#include <fmod.hpp>

#include "EngineInc.h"

#include "Game/Player.h"
#include "Game/SpaceGame.h"

#include <iostream>
#include <memory>

int main(int argc, char* argv[]) {

    // Initialize Engine Systems
    swaws::GetEngine().Initialize();

    // Load a Font
    swaws::Font* font = new swaws::Font();
    font->Load("MotionPicture_PersonalUseOnly.ttf", 40);

    // Initialize Game
    std::unique_ptr<SpaceGame> game = std::make_unique<SpaceGame>();
    game->Initialize();

    swaws::vec2 v(30, 40);

    SDL_Event e;
    bool quit = false;

    std::vector<swaws::vec2> points; // These are used for drawing rn

    // Test getInt() variants
    std::cout << "Integer Functions:\n";
    std::cout << "getInt(): " << swaws::random::getInt() << "\n";
    std::cout << "getInt(): " << swaws::random::getInt() << "\n";
    std::cout << "getInt(10): " << swaws::random::getInt(10) << "\n";
    std::cout << "getInt(10): " << swaws::random::getInt(10) << "\n";
    std::cout << "getInt(5, 15): " << swaws::random::getInt(5, 15) << "\n";
    std::cout << "getInt(5, 15): " << swaws::random::getInt(5, 15) << "\n";
    std::cout << "getInt(-10, 10): " << swaws::random::getInt(-10, 10) << "\n\n";

    // Test getReal() variants with float
    std::cout << "Float Functions:\n";
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "getReal<float>(): " << swaws::random::getReal<float>() << "\n";
    std::cout << "getReal<float>(): " << swaws::random::getReal<float>() << "\n";
    std::cout << "getReal<float>(5.0f): " << swaws::random::getReal<float>(5.0f) << "\n";
    std::cout << "getReal<float>(2.5f, 7.5f): " << swaws::random::getReal<float>(2.5f, 7.5f) << "\n";
    std::cout << "getReal<float>(-1.0f, 1.0f): " << swaws::random::getReal<float>(-1.0f, 1.0f) << "\n\n";

    // Test getReal() variants with double
    std::cout << "Double Functions:\n";
    std::cout << std::setprecision(10);
    std::cout << "getReal<double>(): " << swaws::random::getReal<double>() << "\n";
    std::cout << "getReal<double>(100.0): " << swaws::random::getReal<double>(100.0) << "\n";
    std::cout << "getReal<double>(0.0, 2.0): " << swaws::random::getReal<double>(0.0, 2.0) << "\n\n";

    // Test getBool()
    std::cout << "Boolean Functions:\n";
    for (int i = 0; i < 10; ++i) {
        std::cout << "getBool(): " << std::boolalpha << swaws::random::getBool() << "\n";
    }
    std::cout << "\n";
    // MAIN LOOP
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        swaws::GetEngine().Update();
        game->Update(swaws::GetEngine().GetTime().GetDeltaTime());

        // STEP ONE (CLICK)
        if (swaws::GetEngine().GetInputSystem().GetMouseButtonPressed(swaws::InputSystem::MouseButton::Left) &&
            !swaws::GetEngine().GetInputSystem().GetKeyDown(SDL_SCANCODE_LSHIFT)) {
            points.push_back(swaws::GetEngine().GetInputSystem().GetMousePosition());
        }

        // STEP TWO (&DRAG)
        if (swaws::GetEngine().GetInputSystem().GetMouseButtonDown(swaws::InputSystem::MouseButton::Left) &&
            swaws::GetEngine().GetInputSystem().GetKeyDown(SDL_SCANCODE_LSHIFT)) {
            swaws::vec2 position = swaws::GetEngine().GetInputSystem().GetMousePosition();
            if (points.empty()) points.push_back(position);
            else if ((position.Length() - points.back().Length()) > 10) points.push_back(position);
        }

        // UNDO
        if (swaws::GetEngine().GetInputSystem().GetKeyPressed(SDL_SCANCODE_Z) && swaws::GetEngine().GetInputSystem().GetKeyDown(SDL_SCANCODE_LCTRL)) {
            if (!points.empty()) {
                points.pop_back();
            }
		}

        // AUDIO HANDLING && INPUT

        // Q = BASS_DRUM
        // if (input->GetKeyDown(SDL_SCANCODE_Q) && !input->GetPreviousKeyDown(SDL_SCANCODE_Q)) audio->playSound(0, 0, false, 0);
        // W = SNARE
        // if (input->GetKeyDown(SDL_SCANCODE_W) && !input->GetPreviousKeyDown(SDL_SCANCODE_W)) audio->playSound(1, 0, false, 0);
        // E = OPEN-HAT
        // if (input->GetKeyDown(SDL_SCANCODE_E) && !input->GetPreviousKeyDown(SDL_SCANCODE_E)) audio->playSound(2, 0, false, 0);
        // R = CLOSE-HAT
        // if (input->GetKeyDown(SDL_SCANCODE_R) && !input->GetPreviousKeyDown(SDL_SCANCODE_R)) audio->playSound(3, 0, false, 0);
        // T = CLAP
        // if (input->GetKeyDown(SDL_SCANCODE_T) && !input->GetPreviousKeyDown(SDL_SCANCODE_T)) audio->playSound(4, 0, false, 0);
        // Y = COWBELL
        // if (input->GetKeyDown(SDL_SCANCODE_Y) && !input->GetPreviousKeyDown(SDL_SCANCODE_Y)) audio->playSound(5, 0, false, 0);

        swaws::vec3 color{ 0, 0, 0 };

        swaws::GetEngine().GetRenderer().Clear(); // Clear the renderer

        for (int i = 0; i < (int)points.size() - 1; i++) {
            // set color or random color
            // I choose random
            swaws::GetEngine().GetRenderer().SetColor((uint8_t)swaws::random::getInt(256), swaws::random::getInt(256), swaws::random::getInt(256), swaws::random::getInt(256)); // Set render draw color to random color
            swaws::GetEngine().GetRenderer().DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
        }

        // Draw Actors
        game->Draw();

		// Reset color
        swaws::GetEngine().GetRenderer().SetColor((uint8_t)0, 0, 0);
        swaws::GetEngine().GetRenderer().Present();

    }

    game->Shutdown();
    game.release();
    swaws::GetEngine().Shutdown();

    return 0;
}