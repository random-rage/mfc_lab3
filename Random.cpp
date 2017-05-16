#include "Random.h"

Random::Random()
{
	FILE *f = fopen("/dev/urandom", "r");
	u_long seed;
	fread(&seed, sizeof(u_long), 1, f);
	fclose(f);
	rnd.seed(seed);
}

void Random::fill(Buffer *buf)
{
	buf->val.p1 = rnd();
	buf->val.p2 = rnd();
	#ifdef HASH_64
	buf->val.p3 = rnd();
	buf->val.p4 = rnd();
	#endif
}

