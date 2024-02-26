/// \file Modul_array.h
/// \brief Работа с массивами
/// \author Бурдинская Наталья ВМК-22
/// \date 18.02.2024

#pragma once
#include <string>    // для использования строк
#include <iomanip>   // для setw setprecision
#include <cassert>   // для assert
#include <iostream>  // объявляет cin cout
#include <ctime>    // время для рандомных элементов массива
#include <fstream>   // для работы с файлами
#include <exception> // обработка исключений
#include <locale>    // определ¤ет функцию setlocale для русской локали 
#include <chrono>    // Измерение времени работы кода
using namespace std::chrono;
using namespace std; // пространоство имен std::

// ПРОСТРАНСТВО ИМЕН ДЛЯ МАССИВА
namespace NamespaceMassiv
{
	//---процедура ввода массива размерности size случайными числами
		// динамические массивы в функции передаютс¤ как векторы
		// ничего не возвращает, просто вводит данные в массив
	template <typename TArray>
	void Vvod_array(TArray* a, size_t size, int high, int low)
	{
		// массив a, size, high, low - формальные параметры
		// заполнение массива случайными числами от low до high включительно
		for (size_t i = 0; i < size; ++i) // нумерация с нул¤ до size-1
		{
			a[i] = rand() % (2 * high) + low;
			// rand() возвращает случайное целое число
		}
	}
	//---процедура вывода на экран массива N
		// ничего не возвращает, просто выводит на консоль
	template<typename TArray>
	void Screen_array(const TArray* a, size_t size)
	{
		// массив a, size - формальные параметры
		for (size_t i = 0; i < size; i++)
		{
			cout << a[i] << "  ";
			// cout << "a[" << i << "] = " << a[i] << " ";
		}
		cout << endl;
	}
}
