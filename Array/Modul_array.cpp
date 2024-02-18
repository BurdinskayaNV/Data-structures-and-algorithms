/// \file ModulMassiv.cpp
/// \brief cpp-файл модуль ModulMassiv.cpp
/// \author Бурдинская Наталья ВМК-22
/// \date 18.02.2024

#include "Modul_array.h" // вызов заголовочного файла Modul_array.cpp

// ПРОСТРАНСТВО ИМЕН ДЛЯ МАССИВА
namespace NamespaceMassiv
{
//---процедура ввода массива размерности size случайными числами
	// динамические массивы в функции передаютс¤ как векторы
	// ничего не возвращает, просто вводит данные в массив
		void Vvod_array(vector<double>& a)
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
	void Screen_Mass(const vector<double>& a)
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
	bool sortArr(const vector<double>& a, const char rule = '2')
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
				if (a[i] >= a[i + 1])
					return false;
			}
		return true;
	}
//--- Последовательный поиск по массиву, если key будет найден, то вернется его индекс, если же нет, то вернется число -1
	size_t sequential_search(const vector<double>& a, size_t size, const double key)
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
	void WriteFile(const string& file_name, const vector<double>& a) // по ссылке на константу
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
	vector<double> ReadFile(const string& file_name, size_t n)
	{
		vector<double> a{ 0 };
		a.resize(n);
		ifstream Fout; // объявляем имя Fout для чтения
		//Режим открыть файл для чтения ios::in можно установить при
		//вызове метода open(), необязательно при создании файла(процедура выше)
		Fout.open(file_name, ios::in); //открываем файл для чтения на начале
		//проверяю на наличие файла
		if (!Fout.is_open())	  // Если не открыт файл
		{
			throw runtime_error("Файл не найден");
		}
		if (!Fout.eof()) // делаем пока не конец 
			for (int i = 0; i < n; ++i)	{ Fout >> a[i];	}
		Fout.close(); // Функция close() закрывает поток файла
		cout << "Читаем. Конец файла." << endl;
		cout << "\n";
		return a;
	}
//---функция поиска количества элементов массива в файле
	unsigned SizeFile(const string& file_name)
	{
		unsigned res = 0; // Переменная для счета количества строк
		string line; // Строка, с помощью которой ищем количество строк
		ifstream file(file_name); // Открытие файла 
		if (!file.is_open()) // Если не открыт файл
		{
			throw runtime_error("Файл не найден!"); // Если что, то в ошибку
		}
		// Цикл счёта количества строк -> количества элементов массива
		while (getline(file, line))
		{
			res++; // Цикл будет жить, пока getline делает переходы
		}
		file.close(); // Закрыть файл
		if (res == 0) // Ошибка, если файл пуст
			throw runtime_error("Массив не найден в файле - файл пуст");
		return res;
	}
}
