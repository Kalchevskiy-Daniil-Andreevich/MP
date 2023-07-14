//#include "stdio.h"
//#include "Auxil.h"                            
//#include <iostream>
//#include <ctime>
//#include <locale>                    
//
//int main()
//{
//
//	double  av1 = 0, av2 = 0;
//	clock_t  t1 = 0, t2 = 0;
//
//	int CYCLE = 50000;
//
//	setlocale(LC_ALL, "rus");
//
//	auxil::start();                          // ����� ��������� 
//	for (size_t i = 0; i < 10; i++)
//	{
//		t1 = clock();                            // �������� ������� 
//		for (int i = 0; i < CYCLE; i++)
//		{
//			av1 += (double)auxil::iget(-100, 100); // ����� ��������� ����� 
//			av2 += auxil::dget(-100, 100);         // ����� ��������� ����� 
//		}
//		t2 = clock();                            // �������� ������� 
//
//
//		std::cout << std::endl << "���������� ������:         " << CYCLE;
//		std::cout << std::endl << "������� �������� (int):    " << av1 / CYCLE;
//		std::cout << std::endl << "������� �������� (double): " << av2 / CYCLE;
//		std::cout << std::endl << "����������������� (�.�):   " << (t2 - t1);
//		std::cout << std::endl << "                  (���):   "
//			<< ((double)(t2 - t1)) / ((double)CLOCKS_PER_SEC);
//		std::cout << std::endl;
//
//		CYCLE += 50000;
//	}
//	system("pause");
//	return 0;
//}
