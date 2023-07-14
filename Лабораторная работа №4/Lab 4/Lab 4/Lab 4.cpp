#include "stdio.h"
#include <algorithm>
#include <iostream>
#include <ctime>
#include "Auxil.h"
#include <iomanip>
#include "Levenshtein.h"
#include "LCS.h"
#include "LCH.h"

#define S1SIZE 200
#define S2SIZE 300
#define OUTPUTROWSIZE 20

using namespace std;

void TaskLevenshtein()
{
	char s1[S1SIZE] = "";
	char s2[S2SIZE] = "";
	for (int i = 0; i < S1SIZE; i++)
	{
		s1[i] = auxil::cget();
	}
	for (int i = 0; i < S2SIZE; i++)
	{
		s2[i] = auxil::cget();
	}


	cout << "\t\tS1:" << endl;
	for (int i = 0; i < S1SIZE / OUTPUTROWSIZE; i++)
	{
		cout << "\t";
		for (int j = 0; j < OUTPUTROWSIZE; j++)
		{
			cout << s1[j + i * OUTPUTROWSIZE];
		}
		cout << endl;
	}
	cout << "\t\tS2:" << endl;
	for (int i = 0; i < S2SIZE / OUTPUTROWSIZE; i++)
	{
		cout << "\t";
		for (int j = 0; j < OUTPUTROWSIZE; j++)
		{
			cout << s2[j + i * OUTPUTROWSIZE];
		}
		cout << endl;
	}

	clock_t t1 = 0, t2 = 0, t3, t4;
	double dividers[7] = { 1.0 / 25.0, 1.0 / 20.0, 1.0 / 15.0, 1.0 / 10.0, 1.0 / 5.0, 1.0 / 2.0, 1.0 };

	int  lx = sizeof(s1) - 1, ly = sizeof(s2) - 1;
	std::cout << std::endl;
	std::cout << std::endl << "-- расстояние Левенштейна -----" << std::endl;
	std::cout << std::endl << "--длина --- рекурсия -- дин.програм. ---" << std::endl;
	for (int i = 0; i < 7; i++)
	{

		t1 = clock(); levenshtein_r(lx * dividers[i], s1, ly * dividers[i], s2); t2 = clock();
		t3 = clock(); levenshtein(lx * dividers[i], s1, ly * dividers[i], s2); t4 = clock();
		std::cout << std::right << std::setw(2) << 1 << "/" << std::setw(2) << 1 / (double)dividers[i]<< "        " << std::left << std::setw(10) << (t2 - t1)
		<< "   " << std::setw(10) << (t4 - t3) << std::endl;
	}
}

void recursive_solution()
{
	clock_t t1 = 0, t2 = 0;

	char X[] = "ABCDFGIABCDFGIABCDFGIABCDFGI", Y[] = "EATUFIEATUFIEATUFIEATUFI";
	std::cout << std::endl << "-- вычисление длины LCS для X и Y(рекурсия)";
	std::cout << std::endl << "-- последовательность X: " << X;
	std::cout << std::endl << "-- последовательность Y: " << Y;

	t2 = clock();
	int s = lcs(
		sizeof(X) - 1,  // длина   последовательности  X   
		"ABCDFGIABCDFGIABCDFGIABCDFGI",       // последовательность X
		sizeof(Y) - 1,  // длина   последовательности  Y
		"EATUFIEATUFIEATUFIEATUFI"       // последовательность Y
	);
	t2 = clock();

	std::cout << std::endl << "-- длина LCS: " << s << std::endl;
	cout << "Время выполнения: " << (t2 - t1) << endl;
}

void dynamic_solution()
{
	clock_t t1 = 0, t2 = 0;

	char z[100] = "";
	char x[] = "ABCDFGI",
		y[] = "EATUFI";

	int l = lcsd(x, y, z);
	std::cout << std::endl
		<< "-- наибольшая общая подпоследовательость - LCS(динамическое"
		<< "программирование)" << std::endl;
	std::cout << std::endl << "последовательость X: " << x;
	std::cout << std::endl << "последовательость Y: " << y;
	std::cout << std::endl << "                LCS: " << z;
	std::cout << std::endl << "          длина LCS: " << l;
	std::cout << std::endl;
	cout << "Время выполнения: " << (t2 - t1) << endl;
}

int main()
{
	setlocale(LC_ALL, "rus");

	int choice;

	cout << "Введите номер задания" << endl;
	cout<< "Задания 1-2 (1)" << "\n";
	cout << "Задания 5" << endl;

	cin >> choice;

	switch (choice)
	{
	case 1:
		TaskLevenshtein();
			break;
	case 2:
		recursive_solution();
		dynamic_solution();
		break;
	}
}
