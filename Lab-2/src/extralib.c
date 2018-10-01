#include "../include/extralib.h"

void closefiles(int N, ...)
{
  int* p = &N;
  int i = 1;
  p++;
  for (i = 1; i <= N; ++i) {
    if (*p == -1) continue;
    close(*p);
    p++;
  }
}
