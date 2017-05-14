#include "Hash.h"

hash_t Hash::calc(u_char *buf)
{
#ifdef HASH_32
	return XXH32(buf, BUF_LEN, HASH_SEED);
#else
	return XXH64(buf, BUF_LEN, HASH_SEED);
#endif
}

void Hash::print(hash_t h)
{
#ifdef HASH_32
	printf("%08x", h);
#else
	printf("%16lx", h);
#endif
}

void Hash::println(hash_t h)
{
#ifdef HASH_32
	printf("%08x\n", h);
#else
	printf("%16lx\n", h);
#endif
}