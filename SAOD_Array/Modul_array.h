/// \file Modul_array.h
/// \author Бурдинская Наталья ВМК-22
/// \date 18.02.2024

#pragma once
#include <string>    // для использования строк
#include <iomanip>   // для setw setprecision
#include <cassert>   // для assert
//#include <thread>
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
			a[i] = rand() % (2*high) + low;
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
//---последовательный поиск по массиву,
	// если index будет найден, то вернется его индекс,
	// если нет, то вернется число -1
	template <typename TArray>
	long long Poisk_sequential(const TArray *a, long long size, TArray index)
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

// ПРОСТРАНСТВО ИМЕН ДЛЯ МАССИВА В ФАЙЛЕ
namespace NamespaceFile
{
//---процедурa записи в текстовый файл TxtArray.txt
	// массив a, size, file_name - формальные параметры
	// ничего не возвращает, просто пишет массив в файл
	template <typename TArray>
	void WriteFile(const string& file_name, const TArray* a, size_t size)
	{
		// режим открытия файла дл¤ записи ios::out
		// устанавливаетс¤ при создании файла
		ofstream Fin(file_name, ios::out); //затирает старые и пишет новые данные
		if (!Fin.is_open())	  // Если не открыт файл
		{
			throw runtime_error("Файл не найден");
		}
		// пишем в файл отправленный массив
		for (size_t i = 0; i < size; ++i)
		{
			Fin << a[i] << " " << endl;
		}
		Fin.close(); // функция close() закрывает поток файла
		cout << "Пишем в текстовый файл. Конец записи в файл." << endl;
	}
//-----процедурa чтения из текстового файла TxtArray.txt
    // массив a, size, file_name - формальные параметры
    // возвращает прочитанный массив a из файла
	template <typename TArray>
	void ReadFile(const string& file_name, TArray *a, size_t size)
	{
		ifstream Fout; // объявляем имя Fout для чтения
		//Режим открыть файл для чтения ios::in можно установить при
		//вызове метода open(), необязательно при создании файла(процедура выше)
		Fout.open(file_name, ios::in); //открываем файл для чтения на начале
		//проверяю на наличие файла
		if (!Fout.is_open())	  // Если не открыт файл
		{
			throw runtime_error("Файл не найден");
		}
		if (!Fout.eof()) // делаем пока не конец файла
		{
			for (size_t i = 0; i < size; ++i) { Fout >> a[i]; }
		}
		Fout.close(); // Функция close() закрывает поток файла
		cout << "Читаем из текстового файла. Конец файла." << endl;
	}
//---функция поиска количества элементов массива в текстовом файле TxtArray.txt
	size_t SizeFile(const string& file_name)
	{
		size_t res = 0; // Переменная для счета количества строк
		ifstream file(file_name); // Открытие файла 
		if (!file.is_open()) // Если не открыт файл
		{
			throw runtime_error("Файл не найден!"); // Если что, то в ошибку
		}
		// Цикл счёта количества строк -> количества элементов массива
		while (!file.eof()) // делаем пока не конец файла
		{
			char c;
			file >> c;
			res++; // Цикл будет жить, пока getline делает переходы
		}
		file.close(); // Закрыть файл
		if (res == 0) // Ошибка, если файл пуст
			throw runtime_error("Массив не найден в текстовом файле - файл пуст");
		return res;
	}
//---процедурa записи в бинарный файл BinArray.txt
	template <typename TArray>
	void WriteFileBin(const string& file_name, const TArray* arr, size_t size)
	{
		ofstream file(file_name, ios::binary);
		// Оператор приведения reinterpret_cast используется для приведения несовместимых типов
		file.write(reinterpret_cast<const char*>(&size), sizeof(size));
		file.write(reinterpret_cast<const char*>(arr), sizeof(TArray) * size);
		file.close();
		cout << "Пишем в бинарный файл. Конец записи в файл." << endl;
	}
//-----процедурa чтения из бинарного файла BinArray.txt
	template <typename TArray>
	void ReadFileBin(const string& file_name, TArray*& arr, size_t& size)
	{
		// Оператор приведения reinterpret_cast используется для приведения несовместимых типов
		ifstream file(file_name, ios::binary);
		file.read(reinterpret_cast<char*>(&size), sizeof(size));
		arr = new TArray[size];
		file.read(reinterpret_cast<char*>(arr), sizeof(TArray) * size);
		file.close();
		cout << "Читаем из бинарного файла. Конец файла." << endl;
	}
}
