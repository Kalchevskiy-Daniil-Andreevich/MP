#include "stdio.h"
#include "Auxil.h"                            
#include <iostream>
#include <ctime>
#include <locale>                      
#define N 100

clock_t SS[N];

unsigned int fibonacci(unsigned int n) 
{
    return n < 2 ? n : fibonacci(n - 2) + fibonacci(n - 1);
}

int main()
{
    setlocale(LC_ALL, "rus");

    int V = 1000,
        v[N],
        c[N];
    short m[N];
    int maxcc = 0;
    int n = 0;
    unsigned int as[N];

    auxil::start();

    for (int i = 0; i < N; i++) v[i] = auxil::iget(10, 100);
    for (int i = 0; i < N; i++) c[i] = auxil::iget(5, 50);
    for (int i = 0; i < N; i++) as[i] = auxil::iget(30, 45);

    for (int n = 10; n < 21; n++)
    {
        SS[n] = clock();
        maxcc = fibonacci(as[n]);
        SS[n] = -(SS[n] - clock());
        std::cout << std::endl << "Number: " << std::endl << "n = " << as[n] << std::endl <<  "Time: " << std::endl << "t = " <<  SS[n] << std::endl;
    }

	system("pause");
	return 0;
}