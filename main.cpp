#include <iostream>
#include <random>
#include <time.h>
#include <RSA.h>

using namespace std;

int main()
{
    RSA rsa;
    rsa.generate_keys();

    return 0;
}


