#include "frame.hpp"
#include "globals.hpp"

Frame::Frame(int width, int height, size_t n_blobs)
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

void
Frame::init()
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

Frame::~Frame()
{
	SDL_DestroyTexture(pixels);
}

double
Frame::operator()(double x, double y)
{
	double sum = 0;

	for (const Blob &blob : blobs)
	{
		sum += blob(x, y);
	}

	return sum;
}

void
Frame::update()
{
	for (Blob &blob : blobs)
	{
		double c;
		double s;

		// Calculate the sine and cosine of the heading
		// simultaneously.

		__sincos(blob.heading, &s, &c);

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