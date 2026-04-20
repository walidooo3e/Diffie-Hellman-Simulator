#ifndef FT_DIFFIE_H
#define FT_DIFFIE_H

#include <stdio.h>

typedef struct s_user{
  char      *name;
  unsigned long long private_key;
  unsigned long long public_key;
  unsigned long long shared_secret;
} t_user;

#endif
