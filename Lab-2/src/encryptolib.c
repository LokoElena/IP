#include "../include/encryptolib.h"
#include "../include/extralib.h"

long int vernam_encode(char* input_file, char* output_file, char* key_file)
{
  int fd_if, fd_of, fd_kf;
  char c = '\0';
  char keych = '\0';
  long int encrypted_symbols = 0;
  srand(time(NULL));
  if ((fd_if =  open(input_file, O_RDONLY)) == -1) {
    printf("Can't open file %s\n", input_file);
    return -1;
  }
  if ((fd_of = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1) {
    printf("Can't open file %s\n", output_file);
    closefiles(1, fd_if);
    return -1;
  }
  if ((fd_kf = open(key_file, O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1) {
    printf("Can't open file %s\n", key_file);
    closefiles(2, fd_if, fd_of);
    return -1;
  }
  while (read(fd_if, &c, 1) != 0) {
    keych = (rand() % 256);
    c = c ^ keych;
    write(fd_of, &c, 1);
    write(fd_kf, &keych, 1);
    ++encrypted_symbols;
  }
  closefiles(3, fd_if, fd_of, fd_kf);
  return encrypted_symbols;
}

long int vernam_decode(char* input_file, char* output_file, char* key_file)
{
  int fd_if, fd_of, fd_kf;
  char c = '\0';
  char keych = '\0';
  long int decrypted_symbols = 0;
  if ((fd_if =  open(input_file, O_RDONLY)) == -1) {
    printf("Can't open file %s\n", input_file);
    return -1;
  }
  if ((fd_of = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1) {
    printf("Can't open file %s\n", output_file);
    closefiles(1, fd_if);
    return -1;
  }
  if ((fd_kf = open(key_file, O_RDONLY)) == -1) {
    printf("Can't open file %s\n", key_file);
    closefiles(2, fd_if, fd_of);
    return -1;
  }
  while (read(fd_if, &c, 1) != 0) {
    if (read(fd_kf, &keych, 1) == 0) {
      printf("\nlength files is not equal\n");
      return decrypted_symbols;
    }
    c = c ^ keych;
    write(fd_of, &c, 1);
    ++decrypted_symbols;
  }
  closefiles(3, fd_if, fd_of, fd_kf);
  return decrypted_symbols;
}
