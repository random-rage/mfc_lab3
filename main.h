#ifndef LAB3_LAB3_H
#define LAB3_LAB3_H

#include <random>

// Число потоков
#define THREAD_COUNT 4

// Битность хэша: HASH_32 или HASH_64
#define HASH_32

#ifdef HASH_32

#define BUF_LEN 16
#define TABLE_SIZE 65536 / THREAD_COUNT
typedef unsigned int hash_t;

#else

#define BUF_LEN 32
#define TABLE_SIZE 262144 / THREAD_COUNT
typedef unsigned long int hash_t;

#endif

struct BigInt               // Структура для быстрого заполнения буфера
{
	uint_fast64_t p1, p2;
#ifdef HASH_64
	uint_fast64_t p3, p4;
#endif
};

union Buffer                // Буфер, в который кладётся рандомное значение
{
	BigInt val;
	u_char buf[BUF_LEN];
	
	bool operator==(const Buffer& other) const
	{
		return val.p1 == other.val.p1 && val.p2 == other.val.p2
#ifdef HASH_64
		       && val.p3 == other.val.p3 && val.p4 == other.val.p4
#endif
				;
	}
	
	void print()
	{
		for (size_t i = 0; i < BUF_LEN; ++i)
			printf("%02x", buf[i]);
	}
};

struct Table                // Таблица рандомных значений и их хэшей
{
	Buffer b;               // Буфер, в который кладётся рандомное значение
	hash_t h;               // Хэш этого рандомного значения
};

#endif //LAB3_LAB3_H