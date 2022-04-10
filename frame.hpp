#pragma once

#include <bits/stdc++.h>
#include <SDL2/SDL.h>

#include "blob.hpp"
#include "rand.hpp"

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
	Frame(int width, int height, size_t n_blobs);

	/**
	 * @brief Initialises the pixels of the frame.
	 */
	void
	init();

	/**
	 * @brief Destroys the Frame object.
	 * Destroys the `SDL_Texture` for the pixels.
	 */
	~Frame();

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
	operator()(double x, double y);

	/**
	 * @brief Updates the position of all blobs on the frame.
	 * The blobs are moved according to their speed and heading.
	 */
	void
	update();
};