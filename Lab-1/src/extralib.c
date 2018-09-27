#include "../include/cryptolib.h"
#include "../include/extralib.h"

double wtime()
{
	struct timeval t;
	gettimeofday(&t, NULL);
	return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

int test_prime_num(unsigned long long int p)
{
	unsigned long long int i = 1;

	for (i = 2; i < sqrt(p); ++i)
		if (p % i == 0) return 0;
	return 1;
}

unsigned long long int generate_prime_number(unsigned long long int min, unsigned long long int max)
{
	unsigned long int p = 1;
	do {
		p = (rand()) % (max - min ) + min;
	} while (!test_prime_num(p));
	return p;
}

void mkswap(unsigned long long int *a, unsigned long long int *b)
{
	unsigned long long int buff = *b;
	*b = *a;
	*a = buff;
}