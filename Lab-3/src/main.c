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
#include "../include/md5.h"
#include "../include/digsgnlib.h"



int main(int argc, char *argv[])
{

  RSA_sgn("./rsa.txt");
  /*if (rsa_sgn("./rsa.txt") == rsa_check("./rsa.txt.encode"))
    printf("RSA E/D result:\t[SUCCESS]\n");
  else
    printf("RSA E/D result:\t[FAILED]\n");

  cleanup();*/

  return EXIT_SUCCESS;
}
