#include "rand.hpp"

void
seed_rng()
{
	srand(now());
}

double
rng(double min, double max)
{
	double random = (double) rand() / RAND_MAX;
	return min + random * (max - min);
}