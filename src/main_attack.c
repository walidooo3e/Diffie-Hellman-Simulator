#include "ft_diffie.h"
#include "ft_math.h"
#include <time.h>

typedef struct s_test {
    unsigned long long p;
    unsigned long long g;
    char *difficulty;
} t_test;


void run_benchmark(unsigned long long g, unsigned long long p, char *diff)
{
    clock_t start, end;
    double time_used;
    unsigned long long alice_priv = (p * 3) / 4;
    unsigned long long pub_a;
    unsigned long long cracked;

    pub_a = ft_pow_mod(g, alice_priv, p);
    printf("\n[Testing %s] p: %llu, g: %llu\n", diff, p, g);
    printf("Alice's Public Key: %llu\n", pub_a);
    printf("Cracking...");
    fflush(stdout);

    start = clock();
    cracked = ft_attack(g, pub_a, p);
    end = clock();

    time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nResult: %s | Cracked Private Key: %llu | Time: %f seconds\n", 
           (cracked == alice_priv) ? "SUCCESS" : "FAIL", cracked, time_used);
}

int main(void)
{
    int i = 0;
    t_test tests[] = {
        {23, 5, "Trivial"},
        {7919, 7, "Easy"},
        {104729, 3, "Moderate"},
        {15485863, 2, "Hard (Seconds)"},
        {1000000007, 5, "Extreme (Minutes - CTRL+C to skip)"},
        {0, 0, NULL}
    };

    printf("--- Diffie-Hellman Brute Force Benchmark ---\n");
    while (tests[i].p != 0)
    {
      run_benchmark(tests[i].g, tests[i].p, tests[i].difficulty);
      i++;
    }
}
