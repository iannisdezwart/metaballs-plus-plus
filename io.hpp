/**
 * @brief Main event loop. Handles quit events and renders the frames.
 */
void
handle_events()
{
	SDL_Event event;

	next_event:

	// Save the start time.

	uint64_t start = now();

	// Handle all pending events.

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				exit(0);
		}
	}

	// Render the frame.

	draw();
	frame.update();

	// Calculate the time it took to render the frame.

	uint64_t elapsed = now() - start;

	// Schedule the next frame.

	if (elapsed < frame_time)
	{
		usleep(frame_time - elapsed);
	}

	goto next_event;
}