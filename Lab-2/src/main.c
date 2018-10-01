#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>

#include "../include/encryptolib.h"
#include "../include/extralib.h"

int main(int argc, char *argv[])
{
  printf("VE's result:\t%ld\n", vernam_encode("./vernam.txt", "./vernam_code.txt", "./vernam_key.txt"));
  printf("VD's result:\t%ld\n", vernam_decode("./vernam_code.txt", "./vernam_res.txt", "./vernam_key.txt"));

  //printf("\n");
  //rsa_generate();
  //printf("rsa_encode return %ld\n", rsa_encode("./rsa.txt", "./rsa_code.txt"));
  //printf("rsa_decode return %ld\n", rsa_decode("./rsa_code.txt", "./rsa_res.txt"));

  return EXIT_SUCCESS;
}
