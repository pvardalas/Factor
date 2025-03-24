# Factorization

## Author

- **Panagiotis Vardalas**  

  
## Overview

This program factors a given semiprime number using Pollard's Rho algorithm.

## How It Works
### 1. String to u128 Conversion (``atoint128_t``)

Converts a string representation of a number to a u128 integer type for easy manipulation and calculations.

### 2. u128 to String Conversion (``qtoa``):

Converts a u128 integer type back to a string for printing.

### 3. GCD Calculation (``gcd``):

Computes the greatest common divisor of two numbers using the Euclidean algorithm.

### 4. Modular Multiplication (``mod_mul``)

Efficiently multiplies two numbers under a modulus to prevent overflow and ensure results fit within the desired range.

### 5. Pollard's Rho Algorithm (``pollards_rho``)

A probabilistic method for finding non-trivial factors of large integers. Suitable for larger numbers (outside the 19-22 digit range).

# Usage:
### Run the program with a semiprime as the argument like so:
```sh
./factor <semiprime>
```
# Output
### The program will output the factors of the given semiprime number if they are found:

```sh
Factors: 104723 107223761
```
### If no factors are found, it will indicate:

```sh
No factor found.
```
