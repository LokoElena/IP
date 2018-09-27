/*	Import section	*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>

#include "hashtab.h"

struct listnode *hashtab[HASHTAB_SIZE];

/*	Func section	*/

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

int test_prime_num(unsigned long long int p)
{
	unsigned long long int i = 1;

	for (i = 2; i < sqrt(p); ++i) {
		if (p % i == 0) return 0;
	}
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

int dectobin(unsigned long long int value)
{
	if (value < 2)
		return value;
	else
		return (dectobin(value / 2) * 10 + value % 2);
}

void expmod_func(unsigned long long int base, unsigned long long int exponent, unsigned long long int module, unsigned long long int *result)
{	
	*result = 1;
	while (exponent) {
		if (exponent & 0x1) {
			*result = (*result * base) % module;
		}
		base = (base * base) % module;
		exponent = exponent >> 1;
	}
	*result = *result % module;
}

void euclid(unsigned long long int a, unsigned long long int b, unsigned long long int *res)
{
	if (a < b) mkswap(&a, &b);

	long int U[2] = {1, 0};
	long int V[2] = {0, 1};
	long int T[2];
	long int buff;
	double q = a / b;

	while (b > 0)
	{
		T[0] = U[0] - q * U[1];
		T[1] = V[0] - q * V[1];

		U[0] = U[1];
		V[0] = V[1];

		U[1] = T[0];
		V[1] = T[1];

		buff = a % b;
		a = b;
		b = buff;
	}

	res[0] = U[0];
	res[1] = V[0];
	res[2] = a;
}

void diffyhellman(unsigned long long int* K1, unsigned long long int* K2)
{
	srand(time(NULL));
	unsigned long long int g = generate_prime_number(1, 1000);
	unsigned long long int p;

	p = generate_prime_number(1, 1000);
	unsigned long long int KeyA = 0, KeyB = 0;
	unsigned long long int a, b;

	a = rand() % (1000000 - 10000) + 10000;
	expmod_func(g, a, p, &KeyA);
	b = rand() % (1000000 - 10000) + 10000;
	expmod_func(g, b, p, &KeyB);

	expmod_func(KeyB, a, p, &*K1);
	expmod_func(KeyA, b, p, &*K2);
}

int child_giant(long long base, long long moduli, long long answer)
{
	hashtab_init(hashtab);
	struct listnode *node;
	int m = sqrt(moduli) + 2;
	int k = sqrt(moduli) + 1;

	printf("%d\t%d\n", m, k);

	unsigned long long int *row_y = (unsigned long long int*)malloc(m + 1);
	unsigned long long int *row_a = (unsigned long long int*)malloc(k + 1);

	double t;
	t = wtime();
	
	for(int i = 0; i < m; i++){
		expmod_func(base, i, moduli, &row_y[i]);
		row_y[i] = (row_y[i] * (answer % moduli)) % moduli;
		hashtab_add(hashtab, row_y[i], i);
	}
	int x;
	for(int j = 1; j < k + 1; j++){
		expmod_func(base, j * m, moduli, &row_a[j]);
		node = hashtab_lookup(hashtab, row_a[j]);
		if(node != NULL){
				x = j * m - node->value;
				t = wtime() - t;
//				printf("Time: %.6f sec.\n", t);
				return x;
			}
//		}
	}
	return -1;
}


/*	Main section	*/

int main(int argc, char const *argv[])
{
	if (argc < 4) {
		fprintf(stderr, "Not enough arguments for FEM func!\n");
		return EXIT_FAILURE;
	} else if (argc < 6) {
		fprintf(stderr, "Not enough arguments for GEA func!\n");
		return EXIT_FAILURE;
	}

	unsigned long long int base = atoi(argv[1]);
	unsigned long long int exponent = atoi(argv[2]);
	unsigned long long int module = atoi(argv[3]);
	unsigned long long int fem_res = 1;

	unsigned long long int euclid_a = atoi(argv[4]);
	unsigned long long int euclid_b = atoi(argv[5]);
	unsigned long long int euclid_res[3];

	unsigned long long int KeyA = 5;
	unsigned long long int KeyB = 5;

	expmod_func(base, exponent, module, &fem_res);
	euclid(euclid_a, euclid_b, euclid_res);
	diffyhellman(&KeyA, &KeyB);
	int child_giant_res = child_giant(2, 23, 9);

	printf("FEM's result:\t%lld\n", fem_res);
	printf("GEA's result:\t%lld, %lld and their GCD: %lld\n", euclid_res[0], euclid_res[1], euclid_res[2]);
	printf("DH's result:\t%lld = %lld\n", KeyA, KeyB);
	printf("CGS's result:\t%d\n", child_giant_res);

	return EXIT_SUCCESS;
}