#ifndef EXTRALIB_H
#define EXTRALIB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>

double wtime();
int test_prime_num(unsigned long long int p);
unsigned long long int generate_prime_number(unsigned long long int min, unsigned long long int max);
void mkswap(unsigned long long int *a, unsigned long long int *b);

#endif