
#include <stdio.h>
#include <time.h>
#include "libclk.h"

unsigned long getTics(void)
{
  unsigned long n = 10000000L;

  time_t current, expected;
  time(&current);
  expected = current + 3;
  while ((expected > current) && n)
  {
      --n;
      time(&current);
  }
    return n;
}
