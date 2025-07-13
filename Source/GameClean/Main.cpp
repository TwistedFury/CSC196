#include <SDL3/SDL.h>

#include "Renderer/Renderer.h"
#include "Core/Random.h"
#include "Math/Math.h"
#include "Math/Vector2.h"
#include "Input/InputSystem.h"

#include <iostream>

int main(int argc, char* argv[]) {
    // Initialize Engine Systems

    //swaws::Time time;

    swaws::Renderer renderer;

    renderer.Initialize();
    renderer.CreateWindow("Swaws Engine", 1280, 1024); 

    swaws::InputSystem input;
    input.Initialize();

    // Initialize Audio

    swaws::vec2 v(30, 40);

    SDL_Event e;
    bool quit = false;

    std::vector<swaws::vec2> points;

    // MAIN LOOP
    while (!quit) {
        //time.Tick();
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
            else if (position.length(points.back()) > 10) points.push_back(position);
        }

        // UNDO
        if (input.GetKeyPressed(SDL_SCANCODE_Z) && input.GetKeyDown(SDL_SCANCODE_LCTRL)) {
            if (!points.empty()) {
                points.pop_back();
            }
		}

        // Update Engine Systems

        input.Update();

        swaws::vec2 mouse = input.GetMousePosition();
        std::cout << mouse.x << "," << mouse.y << std::endl;

        if (input.GetKeyPressed(SDL_SCANCODE_A)) std::cout << "pressed\n";

        if (input.GetMouseButtonDown(swaws::InputSystem::MouseButton::Left)) std::cout << "mouse pressed\n";

        // DRAW
        renderer.Clear(); // Clear the renderer

        for (int i = 0; i < (int)points.size() - 1; i++) {
            // set color or random color
            // I choose random
            renderer.SetColor(swaws::random::GetRandom(256), swaws::random::GetRandom(256), swaws::random::GetRandom(256), swaws::random::GetRandom(256)); // Set render draw color to random color
            renderer.DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
        }

		// Reset color
        renderer.SetColor(0, 0, 0);
        renderer.Present();

    }

    renderer.ShutDown();

    return 0;
}