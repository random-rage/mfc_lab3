#include "Hash.h"

Hash::Hash(size_t size)
{
	len = size;
}

u_int Hash::FAQ6(u_char *str)
{
	u_int hash = 0;
	for (size_t i = 0; i < len; i++) {
		hash += str[i];
		hash += (hash << 10);
		hash ^= (hash >> 6);
	}
	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);
	
	return hash;
}

u_int Hash::LY(u_char *str)
{
	u_int hash = 0;
	for (size_t i = 0; i < len; i++) {
		hash = (hash * 1664525) + str[i] + 1013904223;
	}
	return hash;
}

size_t Hash::getLen() const
{
	return len;
}

void Hash::setLen(size_t len)
{
	Hash::len = len;
}