#include <SDL3/SDL.h>

#include "Renderer/Renderer.h"
#include "Core/Random.h"
#include "Math/Math.h"
#include "Math/Vector2.h"
#include "Input/InputSystem.h"

#include <iostream>

int main(int argc, char* argv[]) {

    //swaws::Time time;

    swaws::Renderer renderer;

    renderer.Initialize();
    renderer.CreateWindow("Swaws Engine", 1280, 1024); 

    swaws::InputSystem input;
    input.Initialize();

    SDL_Event e;
    bool quit = false;

    swaws::vector::vec2 v(30, 40);

    // MAIN LOOP
    while (!quit) {
        //time.Tick();
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        renderer.SetColor(swaws::random::GetRandom(256), swaws::random::GetRandom(256), swaws::random::GetRandom(256), swaws::random::GetRandom(256)); // Set render draw color to random color
        renderer.Clear(); // Clear the renderer

        input.Update();

        swaws::vector::vec2 mouse = input.GetMousePosition();
        std::cout << mouse.x << "," << mouse.y << std::endl;


        if (input.GetKeyPressed(SDL_SCANCODE_A)) std::cout << "pressed\n";

        if (input.GetMouseButtonDown(0)) std::cout << "mouse pressed\n";

        // Drawing lines
        for (int i = 0; i < 10; i++) {
            renderer.SetColor(swaws::random::GetRandom(256), swaws::random::GetRandom(256), swaws::random::GetRandom(256)); // Set render draw color to random color

            swaws::vector::vec2 v(
                swaws::random::GetRandomFloat() * renderer.GetWindowWidth(),
                swaws::random::GetRandomFloat() * renderer.GetWindowHeight()
            );

            swaws::vector::vec2 v2(
                swaws::random::GetRandomFloat() * renderer.GetWindowWidth(),
                swaws::random::GetRandomFloat() * renderer.GetWindowHeight()
            );

            renderer.DrawLine(v.x, v.y, v2.x, v2.y);
        }

        // Drawing points
        for (int i = 0; i < 20; i++) {
            renderer.SetColor(swaws::random::GetRandom(256), swaws::random::GetRandom(256), swaws::random::GetRandom(256)); // Set render draw color to random color

            swaws::vector::vec2 v(
                swaws::random::GetRandomFloat() * renderer.GetWindowWidth(),
                swaws::random::GetRandomFloat() * renderer.GetWindowHeight()
            );
            renderer.DrawPoint(v.x, v.y);
        }

        renderer.Present();

    }

    renderer.ShutDown();

    return 0;
}