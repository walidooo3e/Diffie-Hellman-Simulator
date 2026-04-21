## Abstract

This report presents a C-based simulation of the **Diffie-Hellman Key Exchange**, an algorithmic project centered on cryptography and secure communication over insecure channels. The objective is to simulate the establishment of a shared secret using abstract algebra, accompanied by an empirical attack benchmark evaluating the computational boundaries of the underlying mathematical principles.

## 1. Introduction

The secure exchange of cryptographic keys is a fundamental problem in modern computer science. The Diffie-Hellman protocol introduces a method for two parties to establish a shared secret without prior key distribution, relying heavily on the properties of finite cyclic groups and the computational asymmetry of the Discrete Logarithm Problem (DLP).

Let $(G, \cdot)$ be a finite cyclic group of order $q$ with a generator $g \in G$. The security of the protocol is predicated on the intractability of finding the unique integer $x$ such that $g^x \equiv h \pmod p$, given $g$, $h$, and a large prime $p$. While exponentiation is computationally trivial, its inverse—computing the discrete logarithm—is exceptionally difficult. 

## 2. Methodology

### 2.1 The Protocol
The system models the cryptographic handshake in a deterministic sequence:
1.  **Public Parameters:** Both parties agree on a large prime $p$ and a generator $g$ of the multiplicative group $\mathbb{Z}_p^*$.
2.  **Key Generation:** Each party selects a random private key ($a$ and $b$) and computes a public key ($A = g^a \pmod p$ and $B = g^b \pmod p$).
3.  **Shared Secret:** By exchanging public keys, both parties locally compute the shared secret $S = g^{ab} \pmod p$.

### 2.2 Algorithmic Approach
Because standard C lacks native arbitrary-precision integers, the implementation required specific classical computer arithmetic algorithms to handle massive cryptographic exponents without triggering integer overflow.

1.  **Fast Modular Exponentiation (`ft_pow_mod`):**
    A **Square-and-Multiply algorithm** is utilized. By evaluating the exponent recursively based on its binary representation, the algorithm squares the base and multiplies it into the result only when the current bit is odd. The modulo $p$ is applied at every step to tightly bound the working variables.

2.  **Overflow-Safe Modular Multiplication (`ft_russian_peasant`):**
    To safely compute $(A \cdot B) \pmod p$ without exceeding the `unsigned long long` 64-bit boundary, **Russian Peasant Multiplication** (Double-and-Add) is implemented. To prevent intermediate addition overflows, an algebraic rearrangement is used. Instead of verifying if `res + A >= p` (which risks a hard overflow), the system evaluates `res >= p - A`. If true, it performs a subtraction `res -= (p - A)`, safely computing the exact modulo result without crossing hardware boundaries.

## 3. Implementation Details

### 3.1 Compilation
The software is built using the GNU `make` utility. The build process enforces high code quality standards.

```bash
make
```
Standard cleaning targets are provided:
*   `make clean`: Removes intermediate object files.
*   `make fclean`: Removes object files and the generated binaries.
*   `make re`: Recompiles the application from scratch.

### 3.2 Execution
Two binaries are generated upon compilation: the main simulator and the brute-force benchmark.

```bash
./diffie_sim
```
Runs the standard Diffie-Hellman key exchange simulation between Alice and Bob.

```bash
./diffie_attack
```
Executes the empirical benchmark. The program iterates through a pre-defined array of primes with escalating sizes (e.g., from $p = 7919$ up to $p = 1000000007$), attempting an exhaustive brute-force search to crack the private keys, outputting the algorithmic execution time in seconds.

## 4. Complexity Analysis

The algorithmic complexity highlights the stark contrast between executing the protocol and breaking it.

### 4.1 Time Complexity
*   **Honest Key Generation:**
    Utilizing the Square-and-Multiply algorithm, the time complexity for exponentiation is logarithmically bounded by **$\mathcal{O}(\log x)$** operations, resolving in fractions of a millisecond.
    
*   **Attack Execution (Brute Force):**
    The attack module iteratively checks every possible exponent $i \in [0, p-1]$. The worst-case time complexity is strictly linear with respect to the prime, **$\mathcal{O}(p)$**. Given that $p$ grows exponentially with its bit-length $n$, this translates to a bit complexity of **$\mathcal{O}(2^n)$**, demonstrating the cryptographic intractability of the DLP for sufficiently large primes.

### 4.2 Space Complexity
The space complexity for both the key generation and the attack algorithms is strictly **$\mathcal{O}(1)$**. The algorithms evaluate values in-place utilizing localized scalar variables (`unsigned long long`), requiring no dynamic memory allocation or complex data structures.

## 5. Conclusion

The Diffie-Hellman Key Exchange Simulator demonstrates that the foundation of modern cryptography relies heavily on the asymmetric computational costs of specific mathematical operations. By implementing overflow-safe algorithms natively in C, this project successfully translates pure abstract algebra and theoretical constraints into deterministic, performant code.
