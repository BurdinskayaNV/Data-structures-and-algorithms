/// \file Modul_sort.h
/// \brief Работа с сортировкой в массиве
/// \author Бурдинская Наталья ВМК-22
/// \date 18.02.2024
#pragma once
#include "Modul_array.h" // вызов заголовочного файла Modul_array

//--- функция, которая проверяет, отсортирован ли массив
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
			if (a[i] < a[i + 1]) return false;
		}
	else // сортировка по возврастанию
		for (size_t i = 0; i < size - 1; i++)
		{
			// если первый больше второго возвращаем false
			// потому что возрастающая
			if (a[i] > a[i + 1]) return false;
		}
	return true;
}

//---тест работы функции sortArr
void Test_sortArr()
{
	unsigned* sorInt = new unsigned[3] {1, 2, 3};   // сортированный Int
	unsigned* nosorInt = new unsigned[3] {4, 2, 3}; // несортированный Int, сортировка ломается в начале
	assert(sortArr(sorInt, 3) == true);
	assert(sortArr(nosorInt, 3) == false);
	delete[] sorInt;		// сортированный Int
	delete[] nosorInt;		// несортированный Int

	double* sortDob = new double[3] {1.11, 2.22, 3.33};   // сортированный double
	double* nosortDob = new double[3] {1.11, 2.22, 1.33}; // несортированный double, сортировка ломается в конце
	assert(sortArr(sortDob, 3) == true);
	assert(sortArr(nosortDob, 3) == false);
	delete[] sortDob;		// сортированный Double
	delete[] nosortDob;		// несортированный Double

	string* sortStr = new string[3]{ "aaa", "bbb", "ccc" };   // сортированный string
	string* nosortStr = new string[5]{ "aaa", "bbb", "eee", "ccc", "ddd" }; // несортированный string, сотиовка ломается в середине
	assert(sortArr(sortStr, 3) == true);
	assert(sortArr(nosortStr, 5) == false);
	delete[] sortStr;		// сортированный String
	delete[] nosortStr;		// несортированный String

	unsigned* decsortInt = new unsigned[3] {3, 2, 1};		// сортированный Int убывает
	assert(sortArr(decsortInt, 3, 'l') == true);
	double* decsortDob = new double[3] {3.33, 2.22, 1.11};	// сортированный Dob убывает
	assert(sortArr(decsortDob, 2.22, 'l') == true);
	/// *** порядок ломается в середине или в конце или начале assert
	delete[] decsortInt;
	delete[] decsortDob;

	cout << "--- Test_sortArr() выполнен успешно -----------------" << endl;
}

//---сортировка массива пузырьком по порядку - от меньшего к большему
/// \param a массив, тип TArray
/// \param size размер массива
/// \return ничего, просто сортирует массив a
/// цикл вложенный, то его BigO(n*n), O(n*n) - худший вариант, O(n) - лучший вариант слайд 147
template <typename TArray>
void Sorting_bubbles(TArray* a, size_t size)
{
	TArray temporary;	  // temporary - Временное хранение
	for (size_t i = 0; i < size - 1; i++) // Один цикл O(n)
	{
		for (size_t j = 0; j < size - i - 1; j++) // Второй цикл O(n*n)
		{
			if (a[j] > a[j + 1]) // Если пред > след
			{
				temporary = a[j]; // меняем элементы местами
				a[j] = a[j + 1];
				a[j + 1] = temporary;
			}
		}
	}
}

//---тест работы функции Sorting_bubbles
void Test_Sorting_bubbles()
{
	size_t sizemin = 6;

	int* a = new int[sizemin] {6, 2, 3, 4, 5, 1}; // несортированный Int
	double* b = new double[sizemin] {1.11, 2.22, 3.33, 4.44, 5.55, 6.66}; // сортированный double
	int* c = new int[sizemin] {5, 3, 1, 5, 3, 1}; // несортированный Int
	int* d = new int[sizemin] {6, 5, 4, 3, 2, 1}; // сортированный Int в обратном порядке

	int* a_result = new int[sizemin] {1, 2, 3, 4, 5, 6}; // результат сортировки массива a
	double* b_result = new double[sizemin] {1.11, 2.22, 3.33, 4.44, 5.55, 6.66}; // результат сортировки массива b
	int* c_result = new int[sizemin] {1, 1, 3, 3, 5, 5}; // результат сортировки массива c
	int* d_result = new int[sizemin] {6, 5, 4, 3, 2, 1}; // результат сортировки массива d

	// тестирование сортировки пузырьками
	Sorting_bubbles(a, sizemin);
	assert(a[0] == 1);
	assert(a[1] == 2);
	assert(a[2] == 3);
	assert(a[3] == 4);
	assert(a[4] == 5);
	assert(a[5] == 6);

	Sorting_bubbles(b, sizemin);
	Sorting_bubbles(c, sizemin);
	Sorting_bubbles(d, sizemin);
	for (size_t i = 0; i > sizemin; i++)
	{
		assert(a[i] == a_result[i]);
		assert(b[i] == b_result[i]);
		assert(c[i] == c_result[i]);
		assert(d[i] == d_result[i]);
	}
		
	delete[] a, b, c, d;
	delete[] a_result, b_result, c_result, d_result;
	cout << "--- Test_Sorting_bubbles() выполнен успешно ---------" << endl;
}

//---сортировка массива слиянием двух отсортированных подмассивов для Sorting_merge
/// \param a массив, тип TArray
/// \param разбиваем массив от середины middle на две части
/// \param left размер полумассива слева от middle
/// \param right размер полумассива справа от middle
/// \return ничего, просто сортирует массив a
template <typename TArray>
void Merge(TArray* a, int first, int last) // Merge - слияние
{
	int middle, left, right, j;
	int* mass = new int[100]; // временный массив
	middle = (first + last) / 2; // вычисление индекса среднего элемента
	left = first; //начало левой части
	right = middle + 1; //начало правой части
	for (j = first; j <= last; j++)
		if ((left <= middle) && ((right > last) || (a[left] < a[right])))
		{ mass[j] = a[left];	left++;	}
		else
		{ mass[j] = a[right]; right++; }
	//возвращение результата в последовательность
	for (j = first; j <= last; j++)	a[j] = mass[j];
	delete[] mass;
};

//---сортировка слиянием по возрастанию (рекурсивная)
/// \param a массив, тип TArray
/// \param first индекс элемента, с которого начинается сортировка
/// \param last индекс элемента, на котором заканчивается сортировка
/// \return просто сортирует массивы 
/// Big O::			слайд 118
/// Лучший случай: когда массив уже отсортирован, сортировка слиянием все равно выполняется за O(n log n) операций
/// Худший случай: Для сортировки слиянием худший случай также составляет O(n log n)
/// Средний случай: Средняя сложность сортировки слиянием также составляет O(n log n)
template <typename TArray>
void Sorting_merge(TArray* a, int first, int last)
{
	if (first < last)
	{
		Sorting_merge(a, first, (first + last) / 2); //сортировка левой части
		Sorting_merge(a, (first + last) / 2 + 1, last); //сортировка правой части
		Merge(a, first, last); //слияние двух частей
	}
};

//---тест работы функции Sorting_merge
void Test_Sorting_merge()
{
	size_t sizemin = 6;

	int* a = new int[sizemin] {6, 2, 3, 4, 5, 1}; // несортированный Int
	double* b = new double[sizemin] {1.11, 2.22, 3.33, 4.44, 5.55, 6.66}; // сортированный double
	int* c = new int[sizemin] {5, 3, 1, 5, 3, 1}; // несортированный Int
	int* d = new int[sizemin] {6, 5, 4, 3, 2, 1}; // сортированный Int в обратном порядке

	int* a_result = new int[sizemin] {1, 2, 3, 4, 5, 6}; // результат сортировки массива a
	double* b_result = new double[sizemin] {1.11, 2.22, 3.33, 4.44, 5.55, 6.66}; // результат сортировки массива b
	int* c_result = new int[sizemin] {1, 1, 3, 3, 5, 5}; // результат сортировки массива c
	int* d_result = new int[sizemin] {6, 5, 4, 3, 2, 1}; // результат сортировки массива d

	// тестирование сортировки пузырьками
	Sorting_merge(a, 0, 5);
	assert(a[0] == 1);
	assert(a[1] == 2);
	assert(a[2] == 3);
	assert(a[3] == 4);
	assert(a[4] == 5);
	assert(a[5] == 6);

	Sorting_merge(b, 0, 5);
	Sorting_merge(c, 0, 5);
	Sorting_merge(d, 0, 5);
	for (size_t i = 0; i > sizemin; i++)
	{
		assert(a[i] == a_result[i]);
		assert(b[i] == b_result[i]);
		assert(c[i] == c_result[i]);
		assert(d[i] == d_result[i]);
	}

	delete[] a, b, c, d;
	delete[] a_result, b_result, c_result, d_result;
	cout << "--- Test_Sorting_merge() выполнен успешно ---------" << endl;
}

//---функция для определения опорного элемента в массиве
/// \param a массив, тип TArray
/// \param left - указывает на левую границу массива (для первого вызова является 0)
/// \param right - указывает на правую границу массива (n - последним индексом массива)
/// \return просто сортирует массивы 
template <typename TArray>
size_t Search_element(TArray* a, size_t left, size_t right) {
	TArray element = a[right]; 		// Выбираем последний элемент в качестве опорного
	size_t i = (left - 1); 			// Инициализация индекса меньших элементов

	for (size_t j = left; j <= right - 1; j++) {
		if (a[j] < element) {
			i++; 				// Увеличиваем индекс меньших элементов
			swap(a[i], a[j]);   // Меняем элементы местами
		}
	}
	swap(a[i + 1], a[right]); 	// Меняем опорный элемент с элементом в позиции i + 1
	return (i + 1); 			// Возвращаем индекс опорного элемента
}

//---рекурсивная функция для сортировки массива
/// \param a массив, тип TArray
/// \param left - указывает на левую границу массива (для первого вызова является 0)
/// \param right - указывает на правую границу массива (n - последним индексом массива)
/// \return просто сортирует массивы 
template <typename Array>
void Sorting_quick(Array* a, size_t left, size_t right) {
	if (left < right) {
		size_t element = Search_element(a, left, right);// Находим опорный элемент
		if (element > 0) {
			Sorting_quick(a, left, element - 1); 		// рекурсивно сортируем элементы перед опорным
		}
		Sorting_quick(a, element + 1, right); 			// рекурсивно сортируем элементы после опорного
	}
}

//---тест работы функции Sorting_quick
void Test_Sorting_quick()
{
	size_t sizemin = 6;

	int* a = new int[sizemin] {6, 2, 3, 4, 5, 1};
	double* b = new double[sizemin] {1.04, 1.05, 1.03, 1.01, 1.02, 1.06};
	int* c = new int[sizemin] {5, 3, 2, 5, 3, 2};
	int* d = new int[sizemin] {6, 5, 4, 3, 2, 1};

	int* a_result = new int[sizemin] {1, 2, 3, 4, 5, 6};
	double* b_result = new double[sizemin] {1.01, 1.02, 1.03, 1.04, 1.05, 1.06};
	int* c_result = new int[sizemin] {2, 2, 3, 3, 5, 5};
	int* d_result = new int[sizemin] {6, 5, 4, 3, 2, 1};

	Sorting_quick(a, 0, 5);
	Sorting_quick(b, 0, 5);
	Sorting_quick(c, 0, 5);
	Sorting_quick(d, 0, 5);
	for (size_t i = 0; i > sizemin; i++)
	{
		assert(a[i] == a_result[i]);
		assert(b[i] == b_result[i]);
		assert(c[i] == c_result[i]);
		assert(d[i] == d_result[i]);
	}
	
	delete[] a, b, c;
	delete[] a_result, b_result, c_result, d_result;
	cout << "--- Test_Sorting_quick() выполнен успешно ---------" << endl;
}

