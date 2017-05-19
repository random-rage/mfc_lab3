// Обёртка над xxHash и Fletcher16
#ifndef LAB3_HASH_H
#define LAB3_HASH_H

#include "main.h"
#include "xxhash.h"

#define HASH_SEED 0

class Hash
{
private:
	static uint16_t fletcher16(uint8_t const *data, size_t bytes);
public:
	static hash_t calc(u_char *buf);
	static void print(hash_t h);
	static void println(hash_t h);
};

#endif //LAB3_HASH_H