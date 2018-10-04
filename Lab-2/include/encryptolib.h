#ifndef ENCRYPTOLIB_H
#define ENCRYPTOLIB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>

#define MAXINT 512000

long int vernam_encode(char* input_file);
long int vernam_decode(char* input_file);
int rsa_generate();
long int rsa_encode(char* input_file);
long int rsa_decode(char* input_file);
#endif
