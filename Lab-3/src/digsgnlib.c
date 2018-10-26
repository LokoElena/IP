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

