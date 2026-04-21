#ifndef FT_DIFFIE_H
#define FT_DIFFIE_H

#include <stdio.h>
#include <time.h>

typedef struct s_user{
  char      *name;
  unsigned long long private_key;
  unsigned long long public_key;
  unsigned long long shared_secret;
} t_user;

void init_alice(t_user *alice, unsigned long long g, unsigned long long p);
void init_bob(t_user *bob, unsigned long long g, unsigned long long p);
unsigned long long ft_attack(unsigned long long g, unsigned long long public_key, unsigned long long p);

#endif
