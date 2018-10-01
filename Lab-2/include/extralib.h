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

#endif
