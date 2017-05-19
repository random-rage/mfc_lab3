#ifndef LAB3_LAB3_H
#define LAB3_LAB3_H

#include <random>

// Число потоков
#define THREAD_COUNT 4

// Битность хэша: HASH_16, HASH_32 или HASH_64
#ifdef HASH_16
#define BUF_LEN 8
#define TABLE_SIZE 256
typedef unsigned short int hash_t;
#endif

#ifdef HASH_32
#define BUF_LEN 16
#define TABLE_SIZE 65536
typedef unsigned int hash_t;
#endif

#ifdef HASH_64
#define BUF_LEN 32
#define TABLE_SIZE 4194304
typedef unsigned long int hash_t;
#endif

struct BigInt               // Структура для быстрого заполнения буфера
{
	uint_fast64_t p1;
	
#ifdef HASH_32
	uint_fast64_t p2;
#endif

#ifdef HASH_64
	uint_fast64_t p2, p3, p4;
#endif
};

union Buffer                // Буфер, в который кладётся рандомное значение
{
	BigInt val;
	u_char buf[BUF_LEN];
	
	bool operator==(const Buffer& other) const
	{
		return val.p1 == other.val.p1
		
#ifdef HASH_32
			&& val.p2 == other.val.p2
#endif

#ifdef HASH_64
			&& val.p2 == other.val.p2 && val.p3 == other.val.p3 && val.p4 == other.val.p4
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