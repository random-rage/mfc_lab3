#define BUF_LEN 16
#define THREAD_COUNT 4

#include <iostream>
#include <random>
#include <thread>

#include "Hash.h"

using namespace std;

struct Int64
{
	uint_fast64_t hi, lo;
};

union Buffer
{
	Int64 val;
	u_char buf[BUF_LEN];
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
	
	for (int i = 0; i < BUF_LEN; ++i)
		printf("%02x", buffer.buf[i]);
	
	printf(" -> %08x\n", result);
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
	for (int i = 0; i < THREAD_COUNT; ++i)
		t[i] = thread(bruteforce);
	
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