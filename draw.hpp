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
draw_work(int y_start, void *pixels, int pitch)
{
	// Go over all rows this thread is responsible for.

	for (int y = y_start; y < HEIGHT; y += NUM_THREADS)
	{
		// Get a pointer to the first pixel of the row.
		// We are going to increment this pointer to get the next pixel.

		RGB *pixel = (RGB *) ((uint8_t *) pixels + y * pitch);

		for (int x = 0; x < WIDTH; x++)
		{
			// If the coordinate is empty, set the pixel to black.

			double val = abs(1 - frame(x, y));

			if (val > DELTA)
			{
				*pixel++ = RGB(0, 0, 0);
				continue;
			}

			// Get the colour of the pixel and write it.

			double ratio = val / DELTA;
			RGB rgb = ratio_to_rgb(ratio);

			*pixel++ = rgb;
		}
	}
}

/**
 * @brief Draws the frame. This function is executed by the main thread and
 * will spawn `NUM_THREADS` threads to draw the frame.
 */
void
draw()
{
	void *pixels;
	int pitch;

	// Get a buffer to draw to.

	int res = SDL_LockTexture(frame.pixels, nullptr, &pixels, &pitch);

	if (res < 0)
	{
		std::cerr << "Failed to lock texture: "
			<< SDL_GetError() << std::endl;
		printf("%p\n", frame.pixels);
		return;
	}

	// Spawn `NUM_THREADS` threads to draw the frame.

	std::vector<std::thread> threads(NUM_THREADS);

	for (int i = 0; i < NUM_THREADS; i++)
	{
		threads[i] = std::thread(draw_work, i, pixels, pitch);
	}

	// Wait for all threads to finish.

	for (int i = 0; i < NUM_THREADS; i++)
	{
		threads[i].join();
	}

	// Write the buffer to the screen.

	SDL_UnlockTexture(frame.pixels);
	SDL_RenderCopy(renderer, frame.pixels, nullptr, nullptr);
	SDL_RenderPresent(renderer);
}