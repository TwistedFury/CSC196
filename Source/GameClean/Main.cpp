#include <SDL3/SDL.h>

#include "Renderer/Renderer.h"
#include "Core/Random.h"
#include "Math/Math.h"
#include "Math/Vector2.h"

#include <iostream>

int main(int argc, char* argv[]) {

    swaws::Renderer renderer;

    renderer.Initialize();
    renderer.CreateWindow("Swaws Engine", 1280, 1024); 

    SDL_Event e;
    bool quit = false;

    swaws::vec2 v(30, 40);

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        renderer.SetColor(swaws::random::GetRandom(256), swaws::random::GetRandom(256), swaws::random::GetRandom(256), swaws::random::GetRandom(256)); // Set render draw color to random color
        renderer.Clear(); // Clear the renderer

        renderer.SetColor(swaws::random::GetRandom(256), swaws::random::GetRandom(256), swaws::random::GetRandom(256)); // Set render draw color to random color
        renderer.DrawLine(
                    swaws::random::GetRandomFloat() * renderer.GetWindowWidth(), 
                    swaws::random::GetRandomFloat() * renderer.GetWindowHeight(),
                    swaws::random::GetRandomFloat() * renderer.GetWindowWidth(), 
                    swaws::random::GetRandomFloat() * renderer.GetWindowHeight()
                );

        // Drawing lines
        for (int i = 0; i < 10; i++) {
            renderer.SetColor(swaws::random::GetRandom(256), swaws::random::GetRandom(256), swaws::random::GetRandom(256)); // Set render draw color to random color

            swaws::vec2 v(
                swaws::random::GetRandomFloat() * renderer.GetWindowWidth(),
                swaws::random::GetRandomFloat() * renderer.GetWindowHeight()
            );

            swaws::vec2 v2(
                swaws::random::GetRandomFloat() * renderer.GetWindowWidth(),
                swaws::random::GetRandomFloat() * renderer.GetWindowHeight()
            );

            renderer.DrawLine(v.x, v.y, v2.x, v2.y);
        }

        // Drawing points
        for (int i = 0; i < 20; i++) {
            renderer.SetColor(swaws::random::GetRandom(256), swaws::random::GetRandom(256), swaws::random::GetRandom(256)); // Set render draw color to random color

            swaws::vec2 v(
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