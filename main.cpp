#define BUF_LEN 16
#define THREAD_COUNT 4
#define TABLE_SIZE 65536

#include <iostream>
#include <random>
#include <thread>

#include "Hash.h"

using namespace std;

struct Int128
{
	uint_fast64_t hi, lo;
};

union Buffer
{
	Int128 val;
	u_char buf[BUF_LEN];
};

struct TableCell
{
	Buffer val;
	u_int hash;
};

static unsigned long long counter;
static u_int target;
static bool done;
static Hash *h;
static mt19937_64 rnd;

void bruteforce()
{
	Buffer buffer;
	u_int result;
	do
	{
		if (done)
			return;
		
		buffer.val.hi = rnd();
		buffer.val.lo = rnd();
		
		result = h->LY(buffer.buf);
		counter++;
	}
	while (target != result);
	
	done = true;
	cout << "\nFound collision \"src -> hash\":" << endl;
	
	for (size_t i = 0; i < BUF_LEN; ++i)
		printf("%02x", buffer.buf[i]);
	
	printf(" -> %08x\n", result);
}

void findPair()
{
	TableCell left[TABLE_SIZE], right[TABLE_SIZE];
	do
	{
		for (size_t i = 0; i < TABLE_SIZE; ++i)
		{
			if (done)
				return;
			
			left[i].val.val.hi = rnd();
			left[i].val.val.lo = rnd();
			left[i].hash = h->LY(left[i].val.buf);
			right[i].val.val.hi = rnd();
			right[i].val.val.lo = rnd();
			right[i].hash = h->LY(right[i].val.buf);
			counter++;
		}
		for (size_t i = 0; i < TABLE_SIZE; ++i)
			for (size_t j = 0; j < TABLE_SIZE; ++j)
			{
				if (done)
					return;
				
				if (left[i].hash == right[j].hash)
				{
					if (left[i].val.val.hi == right[j].val.val.hi &&
					    left[i].val.val.lo == right[j].val.val.lo)
						continue;
					
					done = true;
					cout << "\nFound collision \"hash -> src1 : src2\":" << endl;
					
					printf("%08x -> ", left[i].hash);
					
					for (size_t k = 0; k < BUF_LEN; ++k)
						printf("%02x", left[i].val.buf[k]);
					
					cout << " : ";
					
					for (size_t k = 0; k < BUF_LEN; ++k)
						printf("%02x", right[j].val.buf[k]);
					
					cout << endl;
				}
			}
	}
	while (!done);
}

int main()
{
	string str;
	cout << "Enter string to find collision:" << endl;
	cin >> str;
	
	h = new Hash(str.size());
	rnd.seed(time(0));
	
	target = h->LY((unsigned char *)str.c_str());
	h->setLen(BUF_LEN);
	done = false;
	
	printf("Target hash: %08x\n", target);
	
	time_t start = time(0);
	thread t[THREAD_COUNT];
	for (size_t i = 0; i < THREAD_COUNT; ++i)
		t[i] = thread(findPair);
	
	cout << "Hashes tested:" << endl;
	while (!done)
	{
		cout << counter << "\r";
		for (size_t i = 0; i < 100000; ++i)
			this_thread::yield();
	}
	printf("Time elapsed: %lds\nTotal hashes tested: %lld", time(0) - start, counter);

	delete h;
	return 0;
}