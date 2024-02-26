/// \file Modul_search.h
/// \brief Работа с поиском в массиве
/// \author Бурдинская Наталья ВМК-22
/// \date 18.02.2024
#pragma once

#include "Modul_array.h" // вызов заголовочного файла Modul_array
#include "Modul_sort.h" // вызов заголовочного файла Modul_sort
using namespace NamespaceMassiv; // пространство имён для работы с массивом
using namespace NamespaceSort; // пространство имён для работы с сортировкой в массиве 
// ПРОСТРАНСТВО ИМЕН ДЛЯ ПОИСКА В МАССИВЕ
namespace NamespaceSearch
{
	//---последовательный поиск по массиву,
		// если index будет найден, то вернется его индекс,
		// если нет, то вернется число -1
	template <typename TArray>
	long long Poisk_sequential(const TArray* a, long long size, TArray index)
	{
		for (long long i = 0; i < size; ++i)
			if (a[i] == index) return i; // значение найдено, возвращаем индекс
		return -1; // значение не найдено, возращаем -1
	}
	//---тест работы функции Poisk_sequential
	void Test_Poisk_sequential()
	{
		long long sizemin = 3;
		// для проверки шаблона TArray
		int* a = new int[sizemin] {1, 2, 3};
		double* b = new double[sizemin] {1.11, 2.22, 3.33};
		string* c = new string[sizemin]{ "Sunday", "Monday", "Tuesday" };

		long long test1 = Poisk_sequential(a, sizemin, 3);
		assert(test1 == 2);
		long long test2 = Poisk_sequential(b, sizemin, 1.11);
		assert(test2 == 0);
		string str = "Wednesday";
		long long temp3 = Poisk_sequential(c, sizemin, str);
		assert(temp3 == -1);

		delete[] a;
		delete[] b;
		delete[] c;
		cout << "--- Test_Poisk_sequential() выполнен успешно --------" << endl;
	}
	//---бинарный поиск в массиве 
		// если index будет найден, то вернется его индекс,
		// если нет, то вернется число -1, если массив не отсортирован, то вернется число -2
		// бинарный поиск работает только с упорядочными данными 
	template <typename TArray>
	long long Poisk_binary(TArray* arr, long long size, TArray index)
	{
		// если массив не отсортирован, возращаем -2
		if (sortArr(arr, size) == false) { return -2; }

		int low = 0;     // нижняя граница, начальное значение = 0
		int high = size; // верхняя граница, начальное значение = размерности массива
		int middle;	     // cередина [low,high]

		while (low <= high)
		{
			middle = (low + high) / 2; // срединный индекс [low,high]
			if (arr[middle] == index) // если середина равна искомому элементу
				return middle;
			if (arr[middle] > index) // в какой части находится искомый элемент
				high = middle - 1;	// к верхней границе
			else
				low = middle + 1;    // к нижней границе
		}
		return -1; // значение не найдено, возращаем -1
	}
	//---тест работы функции Poisk_binary
	void Test_Poisk_binary()
	{
		long long sizemin = 3;
		// для проверки шаблона TArray
		int* a = new int[sizemin] {1, 2, 3}; // отсортирован
		double* b = new double[sizemin] {1.11, 2.22, 3.33}; // отсортирован
		int* c = new int[sizemin] {5, 3, 2}; // не отсортирован

		long long test1 = Poisk_binary(a, sizemin, 3);
		assert(test1 == 2);
		long long test2 = Poisk_binary(b, sizemin, 1.11);
		assert(test2 == 0);
		long long test3 = Poisk_binary(c, sizemin, 2);
		assert(test3 == -2);

		delete[] a;
		delete[] b;
		delete[] c;
		cout << "--- Test_Poisk_binary() выполнен успешно ------------" << endl;
	}
	//---интерполяционный поиска в массиве
		// если index будет найден, то вернется его индекс,
		// если нет, то вернется число -1, если массив не отсортирован, то вернется число -2
		// бинарный поиск работает только с упорядочными данными 
	template <typename TArray>
	long long Poisk_interpolation(TArray* arr, long long size, TArray index)
	{
		// если массив не отсортирован, возращаем -2
		if (sortArr(arr, size) == false) { return -2; }
		long long low = 0;         // нижняя граница, начальное значение = 0
		long long high = size - 1; // верхняя граница, начальное значение = размерности массива

		while (low <= high && index >= arr[low] && index <= arr[high]) // Пока не найдем индекц нашего index
		{
			if (low == high) // если в массиве 1 элемент
			{
				if (arr[low] == index) return low; // если этот элемент есть index, возращаем его индекс
				return -1;	// если нет то -1, что значит index не найден
			}
			// Формула интерполяции для определения предполагаемого положения искомого элемента
			long long pos = low + ((index - arr[low]) * (high - low) / (arr[high] - arr[low]));
			if (arr[pos] == index) return pos; // если позиция pos элемента и есть index, то возращаем pos
			if (arr[pos] < index) low = pos + 1; // если позиция pos элемента меньше, тогда увеличиваем нижнюю границу на pos
			else high = pos - 1; // иначе увеличиваем верхнюю границу на pos 
		}
		return -1; // значение не найдено, возращаем -1
	}

	//---тест работы функции Poisk_interpolation
	void Test_Poisk_interpolation()
	{
		long long sizemin = 3;
		// для проверки шаблона TArray
		int* a = new int[sizemin] {1, 2, 3}; // отсортирован
		double* b = new double[sizemin] {1.11, 2.22, 3.33}; // отсортирован
		int* c = new int[sizemin] {5, 3, 2}; // не отсортирован

		long long test1 = Poisk_interpolation(a, sizemin, 3);
		assert(test1 == 2);
		long long test2 = Poisk_interpolation(b, sizemin, 1.11);
		assert(test2 == 0);
		long long test3 = Poisk_interpolation(c, sizemin, 2);
		assert(test3 == -2);

		delete[] a;
		delete[] b;
		delete[] c;
		cout << "--- Test_Poisk_interpolation() выполнен успешно ------" << endl;
	}
}