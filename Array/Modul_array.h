/// \file Modul_array.h
/// \brief Заголовочный файл модул¤ Modul_array.cpp
/// \author Бурдинская Наталья ВМК-22
/// \date 18.02.2024

#pragma once
#include <string>    // для использования строк
#include <iomanip>   // для setw setprecision
#include <cassert>   // для assert
#include <iostream>  // объявляет cin cout
#include <time.h>    // время для рандомных элементов массива
#include <fstream>   // для работы с файлами
#include <exception> // обработка исключений
#include <vector>    // объявляет класс векторов
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
	void Vvod_array(vector<TArray>& a)
	{
		// массив a - формальные параметры
		// заполнение массива случайными числами от -100 до 100 включительно
		for (unsigned i = 0; i < a.size(); ++i) // нумерация с нул¤ до 
		{
			a[i] = rand() % 200 - 100;
			// rand() возвращает случайное целое число от 0 до RAND_MAX
		}
	}

//---процедура вывода на экран массива N
	// ничего не возвращает, просто выводит на консоль
	template<typename TArray>
	void Screen_array(const vector<TArray>& a)
	{
		// массив a - формальные параметры
		for (unsigned i = 0; i < a.size(); i++)
		{
			cout << a[i] << "  ";
			// cout << "a[" << i << "] = " << a[i] << " ";
		}
		cout << "\n";
	}
//--- Функцию, которая проверяет, отсортирован ли массив
	// два вида сортировки: по возростанию(по умолчанию) и убыванию(задается третьим параметром rule: 'l' по убыванию)
	template <typename TArray>
	bool sortArr(const vector<TArray>& a, const char rule = '2')
	{
		unsigned n = a.size();
		if (n == 0 || n == 1) // Если 1 или 0 элементов возращаем true
			return true;

		if (rule == 'l')
			for (size_t i = 0; i < n - 1; i++)
			{
				if (a[i] <= a[i + 1])
					return false;
			}
		else
			for (size_t i = 0; i < n - 1; i++)
			{
				if (a[i] >= a[i + 1]) return false;
			}
		return true;
	}
//--- Последовательный поиск по массиву, если key будет найден, то вернется его индекс, если же нет, то вернется число -1
	template <typename TArray>
	size_t sequential_search(const vector<TArray>& a, size_t size, const double key)
	{
		for (size_t i = 0; i < size; ++i)
			if (a[i] == key)
				return i; // значение найдено, возвращаем индекс
		return -1;		  // значение не найдено, возращаем -1
	}
}

// ПРОСТРАНСТВО ИМЕН ДЛЯ МАССИВА В ФАЙЛЕ
namespace NamespaceFile
{
//---процедурa записи в файл MyArray.txt
    // массив a - формальные параметры
    // ничего не возвращает, просто пишет массив в файл
	template <typename TArray>
	void WriteFile(const string& file_name, const vector<TArray>& a) // по ссылке на константу
	{
		// режим открытия файла дл¤ записи ios::out
		// устанавливаетс¤ при создании файла
		ofstream Fin(file_name, ios::out); //затирает старые и пишет новые данные
		if (!Fin.is_open())	  // Если не открыт файл
		{
			throw runtime_error("Файл не найден"); 
		}
		// пишем в файл отправленный массив
		for (unsigned i = 0; i < a.size(); ++i)
		{
			Fin << a[i] << " ";
		}
		Fin << endl;
		Fin.close(); // функция close() закрывает поток файла
		cout << "Пишем. Конец записи в файл." << endl;
	}
//-----процедурa чтени¤ из файла MyArray.txt
    // n - формальные параметры - размерность массива
    // возвращает прочитанный массив a из файла
	vector<double> ReadFile(const string& file_name, size_t n);
//---функция поиска количества элементов массива в файле
	unsigned SizeFile(const string& file_name);
}
