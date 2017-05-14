#include "Random.h"

Random::Random(u_long seed)
{
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

