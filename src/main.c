#include "ft_diffie.h"
#include "ft_math.h"

int main(void)
{
  t_user alice;
  t_user bob;
  unsigned long long p = 18446744073709551557ULL;
  unsigned long long g = 2;

  init_alice(&alice, g, p);
  init_bob(&bob, g, p);
  printf("Public Channel: p= %llu, g= %llu\n", p, g);
  printf("Alice broacasts Public Key: %llu\n", alice.public_key);
  printf("Bob broadcasts Public Key: %llu\n", bob.public_key);
  alice.shared_secret = ft_pow_mod(bob.public_key, alice.private_key, p);
  bob.shared_secret = ft_pow_mod(alice.public_key, bob.private_key, p);
  printf("\n--- Results ---\n");
  printf("Alice's Secret: %llu\n", alice.shared_secret);
  printf("Bob's Secret: %llu\n", bob.shared_secret);
  if (alice.shared_secret == bob.shared_secret)
    printf("\nSuccess: Shared secrets match.\n");
  else
    printf("\nError: Secrets do not match.\n");
}
