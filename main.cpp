#include <bits/stdc++.h>
#include <sys/time.h>
#include <SDL2/SDL.h>
#include <unistd.h>

#include "globals.hpp"
#include "timing.hpp"
#include "rand.hpp"
#include "blob.hpp"
#include "frame.hpp"
#include "colour.hpp"
#include "draw.hpp"
#include "io.hpp"

int
main()
{
	// Seed the random number generator from `rand.hpp`.

	seed_rng();

	// Initialise SDL.

	SDL_Init(SDL_INIT_VIDEO);

	// Get the refresh rate of the monitor.

	SDL_DisplayMode display_mode;
	SDL_GetCurrentDisplayMode(0, &display_mode);

	frame_time = 1000000 / display_mode.refresh_rate;

	// Create the window.

	window = SDL_CreateWindow("SDL2", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

	// Create the renderer.

	renderer = SDL_CreateRenderer(window, -1, 0);

	// Initialise the frame.

	frame.init();

	// Call the main loop function.

	handle_events();

	// Clean up.

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}