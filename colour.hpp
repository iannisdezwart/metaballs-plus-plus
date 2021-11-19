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

	RGB(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255)
		: r(r), g(g), b(b), a(a) {}
};

/**
 * @brief Calculates a colour based on a ratio.
 * Low ratios have a hue more towards red,
 * high ratios have a hue more towards blue.
 * @param ratio The ratio to calculate the colour for.
 * @returns The colour.
 */
RGB
ratio_to_rgb(double ratio)
{
	// We multiply the `ratio` by 6 and cast it to an int.
	// This will initialise `int angle_sector` to an integer between [0, 6].
	// The edge case `angle_sector == 6` will be handled by the switch below.

	uint8_t angle_sector = ratio * 6; // [0, 6] (int)

	// We calculate how far the angle is from the `angle_sector` base.
	// We store this value into `int remaining_value` and multiply it by 255
	// to make it a pixel value.

	uint8_t remaining_value = ((ratio * 6) - (double) angle_sector) * 255.0;

	// The switch will return the correct RGB value

	switch (angle_sector) {
		case 0:
		default: // If the `angle_sector` is 6 (equivalent to 6 mod 6 == 0)
			return RGB(255, remaining_value, 0);
		case 1:
			return RGB(255 - remaining_value, 255, 0);
		case 2:
			return RGB(0, 255, remaining_value);
		case 3:
			return RGB(0, 255 - remaining_value, 255);
		case 4:
			return RGB(remaining_value, 0, 255);
		case 5:
			return RGB(255, 0, 255 - remaining_value);
	}
}