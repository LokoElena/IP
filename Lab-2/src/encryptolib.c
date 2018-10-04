#include "../include/encryptolib.h"
#include "../include/extralib.h"
#include "../include/cryptolib.h"
#include "../include/hashtab.h"

long int vernam_encode(char* input_file) {
  int fd_input, fd_output;
  char c = '\0';
  char key = 0;
  char *keystr = malloc(sizeof(char));
  char *keych = malloc(sizeof(char));
  char out[256] = {0};
  strcat(out, input_file);
  strcat(out, ".encode");
  long int k = 0;
  long int ki = 0;
  char cipherstr[8] = "vernam";
  srand(time(NULL));
  if ((fd_input =  open(input_file, O_RDONLY)) == -1) {
    printf("[ERROR] Can't open file %s\n", input_file);
    return -1;
  }
  if ((fd_output = open(out, O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1) {
    printf("[ERROR] Can't open file %s\n", out);
    closefiles(1, fd_input);
    return -1;
  }

  while (read(fd_input, &c, sizeof(char)) != 0) {
    keych[ki] = (rand() % 256);
    keystr[ki] = c ^ keych[ki];
    ++ki;
    keych = realloc(keych, sizeof(char) * (ki + 1));
    keystr = realloc(keystr, sizeof(char) * (ki + 1));
  }

  write(fd_output, &key, sizeof(char));
  write(fd_output, cipherstr, 6 * sizeof(char));

  for (k = 0; k < ki; ++k) {
    write(fd_output, &keych[k], sizeof(char));
  }
  for (k = 0; k < ki; ++k) {
    write(fd_output, &keystr[k], sizeof(char));
  }

  closefiles(2, fd_input, fd_output);
  return k;
}

long int vernam_decode(char* input_file) {
  int fd_input, fd_output;
  char c = '\0';
  char out[256] = {0};
  strcat(out, input_file);
  strcat(out, ".decode");
  char *keystr = malloc(sizeof(char));
  char cipherstr[8] = "vernam";
  long int k = 0;
  long int keyi = 0;
  long int ki = 0;
  if ((fd_input =  open(input_file, O_RDONLY)) == -1) {
    printf("[ERROR] Can't open file %s\n", input_file);
    return -1;
  }
  if ((fd_output = open(out, O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1) {
    printf("[ERROR] Can't open file %s\n", out);
    closefiles(1, fd_input);
    return -1;
  }

  if (read(fd_input, cipherstr, 7 * sizeof(char)) == 0) return 0;
  while (read(fd_input, &c, sizeof(char)) != 0) {
    keystr[ki] = c;
    ++ki;
    keystr = realloc(keystr, sizeof(char) * (ki + 1));
  }
  keyi =  ki / 2;

  for (k = 0; k < keyi; ++k) {
    c = keystr[k] ^ keystr[k + keyi];
    write(fd_output, &c, sizeof(char));
  }
  closefiles(2, fd_input, fd_output);
  return k;
}

int rsa_generate() {
  unsigned long long int p, q, e;
  long int eiler_res;
  unsigned long int d, n;
  int fd_public, fd_private;

  if ((fd_public = open("./.keyrsa.pub",  O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1) {
    printf("[ERROR] Can't open file .keyrsa.pub\n");
    return -1;
  }
  if ((fd_private = open("./.keyrsa",  O_WRONLY | O_CREAT | O_TRUNC, 0600)) == -1) {
    printf("[ERROR] Can't open file .keyrsa\n");
    closefiles(1, fd_public);
    return -1;
  }
  long int nod = 0;
  while (nod != 1 || test_prime_num(d) == 0 || d > 0xFFFF) {
    do {
      generate_prime_number(1, MAXINT, &p);
      generate_prime_number(1, MAXINT, &q);
    } while (p == q);
    n = p * q;
    eiler_res = (p - 1) * (q - 1);
    e = generate_prime_too_number(eiler_res, 1, eiler_res);

    euclid_with_roots(e, eiler_res, &d, NULL, &nod);
    d = d % eiler_res;
  }
  write(fd_public, &e, sizeof(e));
  write(fd_public, &n, sizeof(n));
  write(fd_private, &d, sizeof(d));
  write(fd_private, &n, sizeof(n));
  closefiles(2, fd_public, fd_private);
  return 0;
}

long int rsa_encode(char* input_file) {
  int fd_input, fd_output, fd_key;
  unsigned long int pubkey_e = 0, pubkey_n = 0;
  unsigned long long int c = '\0';
  long int *keystr = malloc(sizeof(long int));
  long int k = 0;
  long int ki = 0;
  char key = 0;
  char cipherstr[5] = "rsa";
  char out[256] = {0};
  strcat(out, input_file);
  strcat(out, ".encode");
  if ((fd_input =  open(input_file, O_RDONLY)) == -1) {
    printf("[ERROR] Can't open file %s\n", input_file);
    return -1;
  }
  if ((fd_output = open(out, O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1) {
    printf("[ERROR] Can't open file %s\n", out);
    closefiles(1, fd_input);
    return -1;
  }
  if ((fd_key = open(".keyrsa.pub", O_RDONLY)) == -1) {
    printf("[ERROR] Can't open file %s\n", out);
    closefiles(2, fd_input, fd_output);
    return -1;
  }
  read(fd_key, &pubkey_e, sizeof(unsigned long int));
  read(fd_key, &pubkey_n, sizeof(unsigned long int));

  while (read(fd_input, &c, sizeof(char)) != 0) {
    expmod_func(c, pubkey_e, pubkey_n, &c);
    keystr[ki] = c;
    ++ki;
    keystr = realloc(keystr, sizeof(long int) * (ki + 1));
    c = 0;
  }
  write(fd_output, &key, sizeof(char));
  write(fd_output, cipherstr, 3 * sizeof(char));

  for (k = 0; k < ki; ++k) {
    write(fd_output, &keystr[k], sizeof(long int));
  }

  closefiles(3, fd_input, fd_output, fd_key);
  return k;
}

long int rsa_decode(char* input_file) {
  int fd_input, fd_output, fd_key;
  unsigned long int privkey_d, privkey_n;
  unsigned long long int c = '\0';
  char *keystr = malloc(sizeof(char));
  long int k = 0;
  long int ki = 0;
  char cipherstr[5] = "rsa";
  char out[256] = {0};
  strcat(out, input_file);
  strcat(out, ".decode");
  if ((fd_input =  open(input_file, O_RDONLY)) == -1) {
    printf("[ERROR] Can't open file %s\n", input_file);
    return -1;
  }
  if ((fd_output = open(out, O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1) {
    printf("[ERROR] Can't open file %s\n", out);
    closefiles(1, fd_input);
    return -1;
  }

  if ((fd_key = open(".keyrsa", O_RDONLY)) == -1) {
    printf("[ERROR] Can't open file %s\n", out);
    closefiles(2, fd_input, fd_output);
    return -1;
  }
  read(fd_key, &privkey_d, sizeof(unsigned long int));
  read(fd_key, &privkey_n, sizeof(unsigned long int));

  if (read(fd_input, cipherstr, 4 * sizeof(char)) == 0) return 0;
  while (read(fd_input, &c, sizeof(long int)) != 0) {
    expmod_func(c, privkey_d, privkey_n, &c);
    keystr[ki] = c;
    ++ki;
    keystr = realloc(keystr, sizeof(char) * (ki + 1));
    c = 0;
    ++k;
  }

  for (k = 0; k < ki; ++k) {
    write(fd_output, &keystr[k], sizeof(char));
  }
  closefiles(3, fd_input, fd_output, fd_key);
  return k;
}
