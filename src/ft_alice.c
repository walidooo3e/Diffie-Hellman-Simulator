#include "ft_diffie.h"
#include "ft_math.h"

void init_alice(t_user *alice, unsigned long long g, unsigned long long p)
{
  alice->name = "Alice";
  alice->private_key = 6;
  alice->public_key = ft_pow_mod(g, alice->private_key, p);
  alice->shared_secret = 0;
}
