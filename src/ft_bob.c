#include "ft_diffie.h"
#include "ft_math.h"

void init_bob(t_user *bob, unsigned long long g, unsigned long long p)
{
  bob->name = "Bob";
  bob->private_key = 9876543210ULL;
  bob->public_key = ft_pow_mod(g, bob->private_key, p);
  bob->shared_secret = 0;
}

