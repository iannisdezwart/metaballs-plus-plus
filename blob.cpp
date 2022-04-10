#include "blob.hpp"

double
Blob::operator()(double x, double y)
const
{
	double x1 = x - this->x;
	double y1 = y - this->y;
	return radius / sqrt(x1 * x1 + y1 * y1);
}