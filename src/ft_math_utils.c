#include "ft_diffie.h"
#include "ft_math.h"
unsigned long long ft_russian_peasant(unsigned long long a, unsigned long long b, unsigned long long m)
{
  unsigned long long res = 0;
  a %= m;
  while (b > 0)
  {
    if (b % 2 == 1)
    {
      if (res >= m - a)
        res -= (m - a);
      else
      res += a;
    }
    if (a >= m - a)
      a -=(m - a);
    else
      a += a;
    b /= 2;
  }
  return res;
}

unsigned long long  ft_pow_mod(unsigned long long base, unsigned long long exp, unsigned long long mod)
{
  unsigned long long res = 1;
  base %= mod;
  while (exp > 0)
  {
    if (exp % 2 == 1)
      res = ft_russian_peasant(res, base, mod);
    base = ft_russian_peasant(base, base, mod);
    exp /= 2;
  }
  return res;
}

unsigned long long ft_attack(unsigned long long g, unsigned long long public_key, unsigned long long p)
{
  clock_t start, end;
  double cpu_time;
  unsigned long long i;

  i = 0;
  start = clock();
  while (i < p - 1)
  {
    if (ft_pow_mod(g, i, p) == public_key)
    {
      end = clock();
      cpu_time = (end - start) / CLOCKS_PER_SEC;
      printf("Key crakced: %llu in %f seconds\n", i, cpu_time);
      return (i);
    }
    i++;
  }
  return(0);
}

