// Necessary Libraries

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef __uint128_t u128;

// Convert string to u128
u128 atoint128_t(const char *s) {
  u128 val = 0;
  while (*s >= '0' && *s <= '9') {
    val = (10 * val) + (*s - '0');
    s++;
  }
  return val;
}

// Convert u128 to string
char *qtoa(u128 n) {
  // Buffer to hold the string representation
  static char buf[40];

  // Pointer to the end of the buffer
  char *p = buf + sizeof(buf) - 1;

  // Null-terminate the string
  *p = '\0';

  // Convert each digit to a character
  do {
    // Store the last digit as a character
    *--p = '0' + (n % 10);

    // Remove the last digit from the number
    n /= 10;
  } while (n > 0);

  return p;
}

// Fast GCD implementation
u128 gcd(u128 a, u128 b) {
  while (b) {
    u128 temp = b;
    b = a % b;
    a = temp;
  }
  return a;
}

// Efficient modular multiplication
u128 mod_mul(u128 a, u128 b, u128 mod) {
  u128 result = 0;
  // Ensure a is within the range of mod to prevent overflow
  a %= mod;

  // Loop until b becomes zero
  while (b) {
    // If the least significant bit of b is 1, add a to result
    if (b & 1) {
      result = (result + a) % mod;
    }
    // Double a and take modulo mod
    a = (a << 1) % mod;
    // Dividing b by 2
    b >>= 1;
  }

  return result;
}

// Pollard's Rho Algorithm
void pollards_rho(u128 n, u128 *factor) {
  // Initialize variables x and y with random values mod n
  u128 x = rand() % n;
  u128 y = x;

  // Choose a random constant c
  u128 c = rand() % n;
  u128 d = 1;

  // Loop until a non-trivial factor is found
  while (d == 1) {
    // Update x with the formula (x*x + c) mod n
    x = (mod_mul(x, x, n) + c) % n;

    // Update y with the same formula twice (to simulate "tortoise and hare"
    // method)
    y = (mod_mul(y, y, n) + c) % n;
    y = (mod_mul(y, y, n) + c) % n;

    // Compute the GCD of |x - y| and n
    d = gcd((x > y) ? (x - y) : (y - x), n);
  }
  // If d equals n, no factor was found
  *factor = (d == n) ? 0 : d;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: %s <semiprime>\n", argv[0]);
    return 1;
  }

  u128 semiprime = atoint128_t(argv[1]);
  u128 factor = 0;

  // Use Pollard's Rho for larger numbers
  pollards_rho(semiprime, &factor);

  // If a valid factor is found
  if (factor) {
    // Print the factors in the correct format
    factor = (factor < semiprime / factor) ? factor : semiprime / factor;
    printf("Factors: %s ", qtoa(factor));
    printf("%s\n", qtoa(semiprime / factor));
  } else {
    // If no factor is found, print an error message and return 1
    printf("No factor found.\n");
    return 1;
  }

  return 0;
}
