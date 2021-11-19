/**
 * @brief Seeds the random number generator.
 * Seeding is done by calling `srand()` with the current time
 * in microseconds since UNIX epoch.
 */
void
seed_rng()
{
	srand(now());
}

/**
 * @brief Generates a random double floating point number in a given range.
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 * @returns A random double floating point number in the given range.
 */
double
rng(double min, double max)
{
	double random = (double) rand() / RAND_MAX;
	return min + random * (max - min);
}