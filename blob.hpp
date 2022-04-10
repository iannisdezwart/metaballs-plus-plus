#pragma once

#include <bits/stdc++.h>

/**
 * @brief Structure for a blob. A blob is a metaball with a position, a radius,
 * a heading and a speed.
 */
struct Blob
{
	double x;
	double y;
	double radius;
	double heading;
	double speed;

	/**
	 * @brief Computes the value of the blob at a given point.
	 * Values on the blob are between 0 and 1.
	 * Values on the edge are near 1.
	 * Values outside the blob are above 1.
	 * @param x The x coordinate of the point.
	 * @param y The y coordinate of the point.
	 * @returns The value of the blob at the given point.
	 */
	double
	operator()(double x, double y)
	const;
};