#include "RSA.h"

#include <random>(std::mt19937_64)
#include <time.h>
#include <iostream>
#include <cstdio>


unsigned long long RSA::get_rand_number(unsigned long long from, unsigned long long to){

    std::mt19937_64 generator(time(0));
    std::uniform_int_distribution<unsigned long long> draw(from, to);

    return draw(generator);
}

unsigned long long RSA::multi_mod(unsigned long long a, unsigned long long b, unsigned long long n){

    unsigned long long res = 0;

    for(unsigned long long m = 1; m; m <<= 1){

        if(b&m)
            res = (res+a)%n;
        a = (a<<1)%n;
    }
    return res;
}

unsigned long long RSA::expo_mod(unsigned long long a, unsigned long long b, unsigned long long n){

    unsigned long long p = a, res = 1;

    for(unsigned long long m = 1; m; m <<= 1){

        if(b&m)
            res = multi_mod(res, p, n);
        p = multi_mod(p, p, n);
    }
    return res;
}

bool RSA::is_prime(unsigned long long number, int num_of_tests){

    unsigned long long d, num_of_div_2 = 0;
    for(d = number-1; d%2==0; num_of_div_2++)
        d /= 2;

    bool t = true;
    unsigned long long a,x;
    for(int i = 1; i <= num_of_tests; i++){

        a = get_rand_number(2,number-2);
        x = expo_mod(a,d,number);
        if(( x == 1 ) || (x == number-1))
            continue;

        for(unsigned long long j = 1; (j<num_of_div_2 ) && (x != number-1); j++){

            x = multi_mod(x,x,number);
            if(x == 1){
                t = false;
                break;
            }
        }
        if( !t )
            break;
        if(x != number-1)
        {
            t = false;
            break;
        }
  }

  return t;
}

bool RSA::is_prime_prim(unsigned long long number){

    for(unsigned long long i = 2; i<=sqrt(number); i++){
        if(number%i == 0)
            return false;
    }
    return true;

}

unsigned long long RSA::gcd(unsigned long long a, unsigned long long b){

    unsigned long long t;
    while( b ){

        t = b;
        b = a % b;
        a = t;
    }
    return a;
}

unsigned long long RSA::ext_euc_algo(unsigned long long a, unsigned long long b){

    long long q, u = 1, w = a, x = 0, z = b;
    while(w){

        if(w<z){
            q = u;
            u = x;
            x = q;
            q = w;
            w = z;
            z = q;
        }
        q = w / z;
        u -= q * x;
        w -= q * z;
    }

    if( x < 0 )
        x += b;

  return x;
}

std::string RSA::dec_to_hex(unsigned long long x){

    char hexaDeciNum[16];
    for(int i=0; i<16; i++)
        hexaDeciNum[i] = '0';
    int i = 0;
    while(x!=0){

        int temp  = 0;
        temp = x % 16;

        if(temp < 10){
            hexaDeciNum[i] = temp + 48;
            i++;
        }
        else{
            hexaDeciNum[i] = temp + 55;
            i++;
        }

        x = x/16;
    }

    std::string res="";
    for(int i = 0; i<16; i+=2){
        res+= hexaDeciNum[i+1];
        res+= hexaDeciNum[i];
    }

    return res;
}

void RSA::generate_keys(){
    std::cout << "Generating the key...\nWait! Finding BIG prime numbers is not easy...\n";

    unsigned long long p = get_rand_number(65536, 4294967295);
    //unsigned long long p = 21932789;
    while(!is_prime_prim(p)){
        while(!is_prime(p,20))
            p = get_rand_number(65536, 4294967295);
    }
    std::cout << "p = " << p << std::endl;

    unsigned long long q = get_rand_number(65536, 4294967295);
    //unsigned long long q = 2212563877;
    while(!is_prime_prim(q) || q==p){
        while(!is_prime(q,20) || q==p)
            q = get_rand_number(65536, 4294967295);
    }
    std::cout << "q = " << q << std::endl;

    unsigned long long totient = (p-1)*(q-1);
    unsigned long long n = p*q;

    unsigned long long e = 101;
    while(gcd(e,totient)!=1)
        e+=2;
    std::cout << "e = " << e << std::endl;

    unsigned long long d = ext_euc_algo(e,totient);
    std::cout << "d = " << d << std::endl;

    std::cout << "klucz publiczny = (" << n << ", " << e << ")" << std::endl;
    std::cout << "klucz prywatny = (" << n << ", " << d << ")" << std::endl;

    private_key[0] = n;
    private_key[1] = d;
    public_key[0] = n;
    public_key[1] = e;

    FILE *priv = fopen("private_key.txt", "w");
    FILE *publ = fopen("public_key.txt", "w");

    char pub_mag_num[] = {'P','U','B','0'};
    char priv_mg_num[] = {'P','R','I','V'};
    fwrite(&pub_mag_num, 1, 4, publ);
    fwrite(&priv_mg_num, 1, 4, priv);

    fwrite(&n, 8,1,publ);
    fwrite(&e, 8,1,publ);

    fwrite(&n, 8,1,priv);
    fwrite(&d, 8,1,priv);

    fclose(priv);
    fclose(publ);

}

void RSA::encrypt(const char *name_of_file){

    std::string name1 = name_of_file;
    std::string name2 = name_of_file;
    name1+=".txt";
    name2+="_encrypted.txt";

    FILE * file_in = fopen(name1.c_str(),"r");
    FILE * file_out = fopen(name2.c_str(),"w");

}

void RSA::decrypt(const char *name_of_file, unsigned long long n, unsigned long long d){

    std::string name1 = name_of_file;
    std::string name2 = name_of_file;
    name1+=".txt";
    name2+="_decrypted.txt";
    FILE * file_in = fopen(name1.c_str(),"r");
    FILE * file_out = fopen(name2.c_str(),"w");



}
