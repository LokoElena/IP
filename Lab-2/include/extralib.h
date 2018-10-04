#ifndef EXTRALIB_H
#define EXTRALIB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>

void closefiles(int N, ...);
void prime_sqrt_mod(unsigned long long int p, unsigned long long *g);
double wtime();
int test_prime_num(unsigned long long int p);
void generate_prime_number(unsigned long long int min, unsigned long long int max, unsigned long long int *p);
void mkswap(unsigned long long int *a, unsigned long long int *b);
void generate_primitive_root(unsigned long long int	p, unsigned long long *g);
int test_prime_too_num(long int p, long int e);
long int generate_prime_too_number(long int e, long int min, long int max);

#endif
