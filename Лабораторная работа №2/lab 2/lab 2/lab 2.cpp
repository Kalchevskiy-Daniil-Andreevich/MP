using namespace std;

#include "stdio.h"
#include <iomanip>
#include <iostream>
#include <TCHAR.H>
#include "Combi.h"
#include "Combo.h"
#include "Comba.h"
#include "Combu.h"
#include "Boat.h"
#include "Auhil.h"


#define minSIZE 25
#define maxSIZE 40
#define NN (sizeof(v)/sizeof(int))
#define MM 5
#define N (sizeof(AA)/2)
#define M 3

int Combi()
{
    char  AA[][2] = { "A", "B", "C", "D" };
    std::cout << std::endl << " - Генератор множества всех подмножеств -";
    std::cout << std::endl << "Исходное множество: ";
    std::cout << "{ ";
    for (int i = 0; i < sizeof(AA) / 2; i++)
        std::cout << AA[i] << ((i < sizeof(AA) / 2 - 1) ? ", " : " ");
    std::cout << "}";
    std::cout << std::endl << "Генерация всех подмножеств  ";
    combi::subset s1(sizeof(AA) / 2);         // создание генератора   
    int  n = s1.getfirst();                // первое (пустое) подмножество    
    while (n >= 0)                          // пока есть подмножества 
    {
        std::cout << std::endl << "{ ";
        for (int i = 0; i < n; i++)
            std::cout << AA[s1.ntx(i)] << ((i < n - 1) ? ", " : " ");
        std::cout << "}";
        n = s1.getnext();                   // cледующее подмножество 
    };
    std::cout << std::endl << "всего: " << s1.count() << std::endl;
    system("pause");
    return 0;
}
int Combo()
{
    char  AA[][2] = { "A", "B", "C", "D", "E" };
    std::cout << std::endl << " --- Генератор сочетаний ---";
    std::cout << std::endl << "Исходное множество: ";
    std::cout << "{ ";
    for (int i = 0; i < sizeof(AA) / 2; i++)

        std::cout << AA[i] << ((i < sizeof(AA) / 2 - 1) ? ", " : " ");
    std::cout << "}";
    std::cout << std::endl << "Генерация сочетаний ";
    combo::xcombination xc(sizeof(AA) / 2, 3);
    std::cout << "из " << xc.n << " по " << xc.m;
    int  n = xc.getfirst();
    while (n >= 0)
    {

        std::cout << std::endl << xc.nc << ": { ";

        for (int i = 0; i < n; i++)


            std::cout << AA[xc.ntx(i)] << ((i < n - 1) ? ", " : " ");

        std::cout << "}";

        n = xc.getnext();
    };
    std::cout << std::endl << "всего: " << xc.count() << std::endl;
    system("pause");
    return 0;

}
//Перестановка – это комбинация элементов из N разных элементов взятых в определенном порядке.В перестановке важен порядок следования элементов
// и в перестановке должны быть задействованы все N элементов.
int Comba()
{
    char  AA[][2] = { "A", "B", "C", "D" };
    std::cout << std::endl << " --- Генератор перестановок ---";
    std::cout << std::endl << "Исходное множество: ";
    std::cout << "{ ";
    for (int i = 0; i < sizeof(AA) / 2; i++)

        std::cout << AA[i] << ((i < sizeof(AA) / 2 - 1) ? ", " : " ");
    std::cout << "}";
    std::cout << std::endl << "Генерация перестановок ";
    comba::permutation p(sizeof(AA) / 2);
    __int64  n = p.getfirst();
    while (n >= 0)
    {
        std::cout << std::endl << std::setw(4) << p.np << ": { ";

        for (int i = 0; i < p.n; i++)

            std::cout << AA[p.ntx(i)] << ((i < p.n - 1) ? ", " : " ");

        std::cout << "}";

        n = p.getnext();
    };
    std::cout << std::endl << "всего: " << p.count() << std::endl;
    system("pause");
    return 0;

}
int Combu()
{
    char  AA[][2] = { "A", "B", "C", "D" };
    std::cout << std::endl << " --- Генератор размещений ---";
    std::cout << std::endl << "Исходное множество: ";
    std::cout << "{ ";
    for (int i = 0; i < N; i++)

        std::cout << AA[i] << ((i < N - 1) ? ", " : " ");
    std::cout << "}";
    std::cout << std::endl << "Генерация размещений  из  " << N << " по " << M;
    combu::accomodation s(N, M);
    int  n = s.getfirst();
    while (n >= 0)
    {

        std::cout << std::endl << std::setw(2) << s.na << ": { ";

        for (int i = 0; i < 3; i++)

            std::cout << AA[s.ntx(i)] << ((i < n - 1) ? ", " : " ");

        std::cout << "}";

        n = s.getnext();
    };
    std::cout << std::endl << "всего: " << s.count() << std::endl;
    system("pause");
    return 0;

}

void BoatF()
{
    int V = 1500,
        v[25] = { },
        c[NN] = { 10, 15, 20, 25, 30,
                  35, 40, 45, 50, 55,
                  60, 65, 70, 75, 80,
                  85, 90, 95, 100, 105,
                  110, 120, 130, 140, 150 };
    short  r[MM];

    auxil::start();
    for (int i = 0; i < NN; i++)
    {
        v[i] = auxil::iget(100, 900);
    }
    int cc = boat(
        V,   // [in]  максимальный вес груза
        MM,  // [in]  количество мест для контейнеров     
        NN,  // [in]  всего контейнеров  
        v,   // [in]  вес каждого контейнера  
        c,   // [in]  доход от перевозки каждого контейнера     
        r    // [out] результат: индексы выбранных контейнеров  
    );

    cout << endl << "- Задача о размещении контейнеров на судне";
    cout << endl << "- общее количество контейнеров    : " << NN;
    cout << endl << "- количество мест для контейнеров : " << MM;
    cout << endl << "- ограничение по суммарному весу  : " << V;
    cout << endl << "- вес контейнеров                 : ";
    for (int i = 0; i < NN; i++) cout << setw(3) << v[i] << " ";
    cout << endl << "- доход от перевозки              : ";
    for (int i = 0; i < NN; i++) cout << setw(3) << c[i] << " ";
    cout << endl << "- выбраны контейнеры (0,1,...,m-1): ";
    for (int i = 0; i < MM; i++) cout << r[i] << " ";
    cout << endl << "- доход от перевозки              : " << cc;
    cout << endl << "- общий вес выбранных контейнеров : ";
    int s = 0; for (int i = 0; i < MM; i++) s += v[r[i]]; cout << s;
    cout << endl << endl;
    system("pause");
}

void BoatS(int sizeOfArray)
{
    clock_t  t1 = 0, t2 = 0;
    t1 = clock();
    int V = 1500,
        * v = new int[sizeOfArray],
        * c = new int[sizeOfArray];
    short  r[MM];

    auxil::start();
    for (int i = 0; i < sizeOfArray; i++)
    {
        v[i] = auxil::iget(100, 900);
        c[i] = auxil::iget(10, 150);
    }

    int cc = boat(
        V,   // [in]  максимальный вес груза
        MM,  // [in]  количество мест для контейнеров     
        sizeOfArray, // [in]  всего контейнеров  
        v,   // [in]  вес каждого контейнера  
        c,   // [in]  доход от перевозки каждого контейнера     
        r    // [out] результат: индексы выбранных контейнеров  
    );
    t2 = clock();
    cout << endl << "Amount of containers: " << sizeOfArray << endl;
    cout << "Elapsed time (sec): "
        << ((double)(t2 - t1)) / ((double)CLOCKS_PER_SEC) << endl;
    if (sizeOfArray < maxSIZE)
        BoatS(sizeOfArray + 1);
}


int main(int argc, _TCHAR* argv[])
{
    setlocale(LC_ALL, "rus");
    int numberOfChoice;
    std::cout << "Select the desired function:\n";
    std::cout << " 1. Combi\n 2. Combo\n 3. Comba\n 4. Combu\n 5. BoatF\n 6. boatS" << std::endl;
    std::cin >> numberOfChoice;
    switch (numberOfChoice)
    {
    case 1:
        Combi();
        break;
    case 2:
        Combo();
        break;
    case 3:
        Comba();
        break;
    case 4:
        Combu();
        break;
    case 5:
        BoatF();
        break;
    case 6:
        BoatS(minSIZE);
        break;
    default:
        break;
    }
}
