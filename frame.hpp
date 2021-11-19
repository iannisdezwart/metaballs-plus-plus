/**
 * @brief Structure for the frame to be displayed.
 * Holds the size, the blobs and the pixels of the frame.
 */
struct Frame
{
	int width;
	int height;

	std::vector<Blob> blobs;
	SDL_Texture *pixels = nullptr;

	Frame() {}

	/**
	 * @brief Constructs a new Frame object.
	 * Initialises the blobs with random values.
	 * Creates a new `SDL_Texture` for the pixels.
	 * @param width The width of the frame.
	 * @param height The height of the frame.
	 * @param n_blobs The number of blobs in the frame.
	 */
	Frame(int width, int height, size_t n_blobs)
		: width(width), height(height), blobs(n_blobs)
	{
		// Initialise the blobs with random values.

		for (Blob &blob : blobs)
		{
			blob.x = rng(0, width);
			blob.y = rng(0, height);
			blob.radius = rng(5, 30);
			blob.heading = rng(0, M_PI * 2);
			blob.speed = rng(1, 3);
		}
	}

	/**
	 * @brief Initialises the pixels of the frame.
	 */
	void
	init()
	{
		// Create a new `SDL_Texture` for the pixels.

		pixels = SDL_CreateTexture(renderer,
			SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING,
			WIDTH, HEIGHT);

		if (!pixels)
		{
			std::cerr << "Failed to create texture: "
				<< SDL_GetError() << std::endl;
		}
	}

	/**
	 * @brief Destroys the Frame object.
	 * Destroys the `SDL_Texture` for the pixels.
	 */
	~Frame()
	{
		SDL_DestroyTexture(pixels);
	}

	/**
	 * @brief Computes the value of all blobs on the frame combined
	 * at a given point.
	 * Values inside a blob are between 0 and 1.
	 * Values on an edge are near 1.
	 * Valuse outside a blob are above 1.
	 * @param x The x coordinate of the point.
	 * @param y The y coordinate of the point.
	 * @returns The value of all blobs on the frame combined
	 * at the given point.
	 */
	double
	operator()(double x, double y)
	{
		double sum = 0;

		for (const Blob &blob : blobs)
		{
			sum += blob(x, y);
		}

		return sum;
	}

	/**
	 * @brief Updates the position of all blobs on the frame.
	 * The blobs are moved according to their speed and heading.
	 */
	void
	update()
	{
		for (Blob &blob : blobs)
		{
			double c;
			double s;

			// Calculate the sine and cosine of the heading
			// simultaneously.

			sincos(blob.heading, &s, &c);

			// Move the blob.

			blob.x += c * blob.speed;
			blob.y += s * blob.speed;

			// Bounce the blob if its edge goes off the screen.

			if (blob.x < 0)
			{
				blob.x = 0;
				blob.heading = M_PI - blob.heading;
			}
			else if (blob.x >= width)
			{
				blob.x = width - 1;
				blob.heading = M_PI - blob.heading;
			}

			if (blob.y < 0)
			{
				blob.y = 0;
				blob.heading = -blob.heading;
			}
			else if (blob.y >= height)
			{
				blob.y = height - 1;
				blob.heading = -blob.heading;
			}
		}
	}
};