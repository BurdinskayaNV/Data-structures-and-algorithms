/// \file Modul_sort.h
/// \brief Работа с сортировкой в массиве
/// \author Бурдинская Наталья ВМК-22
/// \date 18.02.2024
#pragma once

#include "Modul_array.h" // вызов заголовочного файла Modul_array
using namespace NamespaceMassiv; // пространство имён для работы с массивом
// ПРОСТРАНСТВО ИМЕН ДЛЯ СОРТИРОВКИ В МАССИВЕ
namespace NamespaceSort
{
//--- Функцию, которая проверяет, отсортирован ли массив
	// два вида сортировки: по возрастанию (по умолчанию)
	// и убыванию (задается третьим параметром rule: 'l' по убыванию)
	template <typename TArray>
	bool sortArr(const TArray* a, size_t size, const char rule = '2')
	{
		if (size == 0 || size == 1) return true; // 1 или 0 возращаем true
		if (rule == 'l') // сортировка по убыванию
			for (size_t i = 0; i < size - 1; i++)
			{
				// если первый меньше второго возвращаем false
				// потому что убывающая
				if (a[i] <= a[i + 1]) return false;
			}
		else // сортировка по возврастанию
			for (size_t i = 0; i < size - 1; i++)
			{
				// если первый больше второго возвращаем false
				// потому что возрастающая
				if (a[i] >= a[i + 1]) return false;
			}
		return true;
	}
//---тест работы функции sortArr
	void Test_sortArr()
	{
		unsigned* sorInt = new unsigned[3] {1, 2, 3};   // сортированный Int
		unsigned* nosorInt = new unsigned[3] {4, 2, 3}; // несортированный Int
		assert(sortArr(sorInt, 3) == true);
		assert(sortArr(nosorInt, 3) == false);

		double* sortDob = new double[3] {1.11, 2.22, 3.33};   // сортированный double
		double* nosortDob = new double[3] {1.11, 2.22, 1.33}; // несортированный double
		assert(sortArr(sortDob, 3) == true);
		assert(sortArr(nosortDob, 3) == false);

		string* sortStr = new string[3]{ "aaa", "bbb", "ccc" };   // сортированный string
		string* nosortStr = new string[3]{ "eee", "aaa", "ccc" }; // несортированный string
		assert(sortArr(sortStr, 3) == true);
		assert(sortArr(nosortStr, 3) == false);

		unsigned* decsortInt = new unsigned[3] {3, 2, 1}; // сортированный Int убывает
		assert(sortArr(decsortInt, 3, 'l') == true);

		delete[] sorInt;
		delete[] nosorInt;
		delete[] sortDob;
		delete[] nosortDob;
		delete[] sortStr;
		delete[] nosortStr;
		delete[] decsortInt;
		cout << "--- Test_sortArr() выполнен успешно -----------------" << endl;
	}
}