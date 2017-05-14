// Обёртка над Mersenne Twister 19937
#ifndef LAB3_RANDOM_H
#define LAB3_RANDOM_H

#include "main.h"

using namespace std;

class Random
{
private:
	mt19937_64 rnd;
	
public:
	Random(u_long seed);
	
	void fill(Buffer *buf);
};

#endif //LAB3_RANDOM_H