#include "Hash.h"

hash_t Hash::calc(u_char *buf)
{
#ifdef HASH_16
	return fletcher16(buf, BUF_LEN);
#endif

#ifdef HASH_32
	return XXH32(buf, BUF_LEN, HASH_SEED);
#endif

#ifdef HASH_64
	return XXH64(buf, BUF_LEN, HASH_SEED);
#endif
}

uint16_t Hash::fletcher16(uint8_t const *data, size_t bytes)
{
	uint16_t sum1 = 0xff, sum2 = 0xff;
	size_t tlen;
	
	while (bytes) {
		tlen = ((bytes >= 20) ? 20 : bytes);
		bytes -= tlen;
		do {
			sum2 += sum1 += *data++;
			tlen--;
		} while (tlen);
		sum1 = (sum1 & (uint16_t)0xff) + (sum1 >> 8);
		sum2 = (sum2 & (uint16_t)0xff) + (sum2 >> 8);
	}
	/* Second reduction step to reduce sums to 8 bits */
	sum1 = (sum1 & (uint16_t)0xff) + (sum1 >> 8);
	sum2 = (sum2 & (uint16_t)0xff) + (sum2 >> 8);
	return (sum2 << 8) | sum1;
}

void Hash::print(hash_t h)
{
#ifdef HASH_16
	printf("%04x", h);
#endif

#ifdef HASH_32
	printf("%08x", h);
#endif

#ifdef HASH_64
	printf("%16lx", h);
#endif
}

void Hash::println(hash_t h)
{
#ifdef HASH_16
	printf("%04x\n", h);
#endif

#ifdef HASH_32
	printf("%08x\n", h);
#endif

#ifdef HASH_64
	printf("%16lx\n", h);
#endif
}