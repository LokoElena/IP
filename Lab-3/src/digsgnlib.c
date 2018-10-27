#include "../include/extralib.h"
#include "../include/encryptolib.h"
#include "../include/cryptolib.h"
#include "../include/md5.h"


int hashMD5(FILE* fd_input, MD5_CTX *md5handler)
{
  int bytes;
  unsigned char data[1024];
  if (fd_input == NULL) {
    return 1;
  }

  MD5Init(md5handler);
  while ((bytes = fread (data, 1, 1024, fd_input)) != 0){
    MD5Update (md5handler, data, bytes);
  }
  MD5Final(md5handler);
  fclose(fd_input);
  return 0;
}

int RSA_sgn(char* input_file)
{
  unsigned long long int p, q, e, key_check = 0, s;
  unsigned long long int eiler_res;
  unsigned long long int d = 0, n;
  int fd_public, fd_private;
  FILE* in_file = fopen(input_file, "rb");

  MD5_CTX md5handler;
  if (hashMD5(in_file, &md5handler)) {
    return 1;
  }

  if ((fd_public = open("./.keyrsa.pub",  O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1) {
    printf("[ERROR] Can't open file .keyrsa.pub\n");
    return -1;
  }
  if ((fd_private = open("./.keyrsa",  O_WRONLY | O_CREAT | O_TRUNC, 0600)) == -1) {
    printf("[ERROR] Can't open file .keyrsa\n");
    closefiles(1, fd_public);
    return -1;
  }
  unsigned long long int gcd = 0;
  unsigned long long int euclid_res[3];
  do {
    generate_prime_number(1, 100000, &p);
    generate_prime_number(1, 100000, &q);
  } while (p == q);
  n = p * q;
  eiler_res = (p - 1) * (q - 1);

  while (gcd != 1) {
    generate_prime_number(1, 10000, &d);
    euclid(d, eiler_res, euclid_res);
    gcd = euclid_res[2];
  }

  while (key_check != 1) {
    e = rand();
    key_check = (e*d) % eiler_res;
  }
//printf("key_check = %lld\n", key_check);
//printf("gcd = %lld\n", gcd);
//expmod_func(s, e, n, &s);
//printf("signature = %lld\n", s);

  write(fd_public, &e, sizeof(e));
  write(fd_public, &n, sizeof(n));
  write(fd_private, &d, sizeof(d));
  write(fd_private, &n, sizeof(n));
  closefiles(2, fd_public, fd_private);
  printf("eiler_res = %lld\n", eiler_res);
  printf("p = %lld\n", p);
  printf("q = %lld\n", q);
  printf("e = %lld\n", e);
  printf("n = %lld\n", n);
  printf("d = %lld\n", d);
  printf("n = %lld\n", n);
  return 0;
}
/*


long int rsa_sgn_check(char* input_file)
{

}
*/
