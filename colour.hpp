#pragma once

#include <bits/stdc++.h>

/**
 * @brief Structure for an RGB pixel. Also contains an alpha byte.
 */
struct RGB
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;

	RGB() {}

	RGB(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
};

/**
 * @brief Calculates a colour based on a ratio.
 * Low ratios have a hue more towards red,
 * high ratios have a hue more towards blue.
 * @param ratio The ratio to calculate the colour for.
 * @returns The colour.
 */
RGB
ratio_to_rgb(double ratio);