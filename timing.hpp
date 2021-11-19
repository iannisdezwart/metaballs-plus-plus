/**
 * @returns The number of microseconds since UNIX epoch.
 */
uint64_t
now()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000000 + tv.tv_usec;
}