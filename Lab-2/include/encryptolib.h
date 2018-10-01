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

long int vernam_encode(char* input_file, char* output_file, char* key_file);
long int vernam_decode(char* input_file, char* output_file, char* key_file);

#endif
