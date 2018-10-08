#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>

#include "../include/encryptolib.h"
#include "../include/cryptolib.h"
#include "../include/extralib.h"
#include "../include/hashtab.h"

int main(int argc, char *argv[])
{
  printf("VE result:\t%ld\n", vernam_encode("./vernam.txt"));
  printf("VD result:\t%ld\n", vernam_decode("./vernam.txt.encode"));

  //rsa_generate();
  printf("RSA encode result:\t%ld\n", rsa_encode("./rsa.txt"));
  printf("RSA decode result:\t%ld\n", rsa_decode("./rsa.txt.encode"));

  //printf("SE result:\t%ld\n", shamir_encode("./shamir.txt"));
  //printf("SD result:\t%ld\n", shamir_decode("./shamir.txt.encode"));

  elgamal_generate();
  printf("EGE result:\t%ld\n", elgamal_encode("./elgamal.txt"));
  printf("EGD result:\t%ld\n", elgamal_decode("./elgamal.txt.encode"));

  return EXIT_SUCCESS;
}
