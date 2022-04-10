#pragma once

#include <bits/stdc++.h>
#include <SDL2/SDL.h>

#include "frame.hpp"

#define WIDTH 800
#define HEIGHT 600
#define N_BLOBS 10
#define DELTA 0.1

extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern uint64_t frame_time;
extern Frame frame;