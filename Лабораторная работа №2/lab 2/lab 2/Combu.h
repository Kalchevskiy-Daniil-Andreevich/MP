#pragma once
#include "Combo.h"
#include "Comba.h"
namespace combu
{
    struct  accomodation  // генератор размещений 
    {
        short  n,      // количество элементов исходного множества  
            m,      // количество элементов в размещении 
            * sset;      // массив индесов текущего размещения  
        combo::xcombination* cgen;   // указатель на генератор сочетаний
        comba::permutation* pgen;   // указатель на генератор перестановок
        accomodation(short n = 1, short m = 1);  // конструктор  
        void reset();     // сбросить генератор, начать сначала 
        short getfirst();     // сформировать первый массив индексов   
        short getnext();      // сформировать следующий массив индексов  
        short ntx(short i);   // получить i-й элемент массива индексов  
        unsigned __int64 na;  // номер размещения 0, ..., count()-1 
        unsigned __int64 count() const;  // общее количество размещений 
    };
}


