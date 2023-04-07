#include <iostream>
#ifndef RSA_H
#define RSA_H

class RSA
{
    public:
        void generate_keys(); /// generate and save public and private key, Trzeba  wkleic funkcje Micha³a
        void encrypt(const char *name_of_file);  /// encrypt and save file the name_of_file, new name: name_of_file_encrypted.txt, give the file name without ".txt" Trzeba  wkleic funkcje Micha³a
        void decrypt(const char *name_of_file,unsigned long long n, unsigned long long d);  /// decrypt and save file the name_of_file,
                                                                                            /// new name: name_of_file_decrypted.txt, give the file name without ".txt"
                                                                                            /// private key: (n,d)
    private:
        unsigned long long public_key[2]; /// [n][e]
        unsigned long long private_key[2]; /// [n][d]
        unsigned long long get_rand_number(unsigned long long from, unsigned long long to); /// return random number from interval <from, to>
        unsigned long long expo_mod(unsigned long long a, unsigned long long b, unsigned long long n); /// return a^b % n
        unsigned long long multi_mod(unsigned long long a, unsigned long long b, unsigned long long n); /// return a*b % n
        bool is_prime(unsigned long long number, int num_of_tests); /// return true if number is prime, false otherwise, Miller-Rabin test, probability: 1-(1/4)^num_of_tests
        bool is_prime_prim(unsigned long long number); /// return true if number is prime, false otherwise, probability: 1
        unsigned long long gcd(unsigned long long a, unsigned long long b); /// return greatest common divisor
        unsigned long long ext_euc_algo(unsigned long long a, unsigned long long b); /// extended Euclidean algorithm, return the modular inverse
        std::string dec_to_hex(unsigned long long x); /// return the number x in hexadecimal

};

#endif // RSA_H
