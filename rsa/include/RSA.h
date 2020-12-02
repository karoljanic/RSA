#include <iostream>
#ifndef RSA_H
#define RSA_H

class RSA
{
    public:
        void generate_keys(); /// generate and save public and private key
        void encrypt();  /// to do
        void decrypt();  /// to do

    private:
        unsigned long long public_key[2]; /// [e][n]
        unsigned long long private_key[2]; /// [d][n]
        unsigned long long get_rand_number(unsigned long long from, unsigned long long to); /// return random number from interval <from, to>
        unsigned long long expo_mod(unsigned long long a, unsigned long long b, unsigned long long n); /// return a^b % n
        unsigned long long multi_mod(unsigned long long a, unsigned long long b, unsigned long long n); /// return a*b % n
        bool is_prime(unsigned long long number, int num_of_tests); /// return true if number is prime, false otherwise, Miller-Rabin test, probability: 1-(1/4)^num_of_tests
        unsigned long long gcd(unsigned long long a, unsigned long long b); /// return greatest common divisor
        unsigned long long ext_euc_algo(unsigned long long a, unsigned long long b); /// extended Euclidean algorithm, return the modular inverse
        std::string dec_to_hex(unsigned long long x); /// return the number x in hexadecimal



};

#endif // RSA_H
