#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>

int hashMD5(FILE* fd_input, MD5_CTX *md5handler);
int RSA_sgn(char* input_file);
/*long int rsa_sgn(char* input_file)
long int rsa_sgn_check(char* input_file)*/
