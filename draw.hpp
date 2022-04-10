#pragma once

#include <bits/stdc++.h>

#include "globals.hpp"
#include "colour.hpp"
#include "frame.hpp"

const int NUM_THREADS = std::thread::hardware_concurrency();

/**
 * @brief Draws the frame in an interlaced manner.
 * This function is executed by all threads.
 * Each thread draws the frame for all rows it is responsible for.
 * A thread is responsible for all rows `y_start` + k * `NUM_THREADS`,
 * where `k` is an integer.
 * @param y_start The thread start y coordinate.
 * @param pixels A pointer to the pixel buffer.
 * @param pitch The pitch value of the pixel buffer. (number of bytes per row)
 */
void
draw_work(int y_start, void *pixels, int pitch);

/**
 * @brief Draws the frame. This function is executed by the main thread and
 * will spawn `NUM_THREADS` threads to draw the frame.
 */
void
draw();