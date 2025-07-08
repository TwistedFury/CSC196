#include <SDL3/SDL.h>
#include <iostream>

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

	int windowWidth = 1280;
	int windowHeight = 1024;

    SDL_Window* window = SDL_CreateWindow("SDL3 Project", windowWidth, windowHeight, 0);
    if (window == nullptr) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
    if (renderer == nullptr) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Event e;
    bool quit = false;

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }


        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set render draw color to black
        SDL_RenderClear(renderer); // Clear the renderer

        // Drawing lines
        for (int i = 0; i < 100; i++) {

            int rand1 = std::rand() % 256;
            int rand2 = std::rand() % 256;
            int rand3 = std::rand() % 256;
            int rand4 = std::rand() % 256;


            SDL_SetRenderDrawColor(renderer, rand1, rand2, rand3, rand4); // Set render draw color to random color

            int rand5 = std::rand();
            int rand6 = std::rand();
            int rand7 = std::rand();
            int rand8 = std::rand();
            SDL_RenderLine(renderer, rand5, rand6, rand7 % windowWidth, rand8 % windowHeight);
        }

        // Drawing points
        for (int i = 0; i < 200; i++) {

            int rand1 = std::rand() % 256;
            int rand2 = std::rand() % 256;
            int rand3 = std::rand() % 256;
            int rand4 = std::rand() % 256;


            SDL_SetRenderDrawColor(renderer, rand1, rand2, rand3, rand4); // Set render draw color to random color

            int rand5 = std::rand();
            int rand6 = std::rand();
            SDL_RenderPoint(renderer, rand5 % windowWidth, rand6 % windowHeight);
        }

        SDL_RenderPresent(renderer); // Render the screen
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}