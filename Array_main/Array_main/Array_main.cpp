/// \file Massiv_main.cpp
/// \brief тело основной программы
/// \brief подготовительный код для работы с массивами,
/// \brief использован одномерный динамический массив
/// \brief для хранения размера массива, индексов использован тип size_t
/// \brief выделение памяти для массива, освобождение памяти массива
/// \brief передача массива в функции, возврат из функции через return, указатели * и ссылки &
/// \brief использованы шаблонные функции template с типом <typename TArray>
/// \brief применение srand(time(NULL)) и rand() для случайных чисел
/// \brief демонстрация работы с библиотекой <fstream> с файлами
/// \brief записи в файлы текстовый и бинарный
/// \brief созданы пространства имён NamespaceMassiv и NamespaceFile
/// \brief проверка, отсортирован ли массив, автоматический тест для шаблонной функции (assert)
/// \brief измерение времени работы кода
/// \brief последовательный поиск значения в массиве, автоматический тест для шаблонной функции (assert) 
/// \brief бинарный поиск значения в массиве, автоматический тест для шаблонной функции (assert) 
/// \brief интерполяционный поиск значения в массиве, автоматический тест для шаблонной функции (assert)
/// \brief
/// \brief автоматическое тестирование программы с помощью assert
/// \brief оформлен через модули из четырех файлов
/// \brief создан репозиторий в GitHub
/// \author Бурдинская Наталья ВМК-22
/// \date 18.02.2024

#include "Modul_array.h" // вызов заголовочного файла Modul_array
#include "Modul_file.h" // вызов заголовочного файла Modul_file
#include "Modul_search.h" // вызов заголовочного файла Modul_search
#include "Modul_sort.h" // вызов заголовочного файла Modul_sort

int main()
{
	system("chcp 65001 > nul"); //подключение русского языка 
	setlocale(LC_ALL, "RUSSIAN");
	// Генерирует случайное число, используя текущею дату, для непредсказуемости результата
	srand(time(0));
	/// *** выделены в отдельные тесты
	//Test_Work_array(); // работа с массивами в Modul_array.h
	//Test_Work_files(); // работа с файлами в Modul_file.h

    // Работа для построения графика времени работы посиковых функций
	size_t big_n = 100;
	std::cout << fixed << setprecision(5); // три знака после запятой
	int el = 0; // число для поиска
	for (int j = 0; j < 5; j++)
	{
	   std::cout << j + 1 << " итерация" << endl;
	   int *a = new int[big_n];
	   std::cout << "Размерность = " << big_n << endl;
	   Set_array(a, big_n, 1, 10000);
	   // измеряем Последовательный поиск
	   auto begin1 = steady_clock::now();
	   for (int i = 0; i < 5; i++)
	   {
	      el = (int)rand() / RAND_MAX * 10000 + 1; // случайное число для поиска 
		  Search_sequential(a, big_n, el);
	   }
	   auto end1 = steady_clock::now();
	   //auto MilliSeconds1 = duration_cast<milliseconds>(end1 - begin1).count();
	   auto MilliSeconds1 = duration_cast<seconds>(end1 - begin1).count();
	   // измеряем Бинарный поиск
	   auto begin2 = steady_clock::now();
	   for (int i = 0; i < 5; i++)
	   {
	      el = (int)rand() / RAND_MAX * 10000 + 1; // случайное число для поиска 
		  Search_binary(a, big_n, el);
	   }
	   auto end2 = steady_clock::now();
	   //auto MilliSeconds2 = duration_cast<milliseconds>(end2 - begin2).count();
	   auto MilliSeconds2 = duration_cast<seconds>(end2 - begin2).count();
	   // измеряем Интерполяционный поиск
	   auto begin3 = steady_clock::now();
	   for (int i = 0; i < 5; i++)
	   {
	      el = (int)rand() / RAND_MAX * 10000 + 1; // случайное число для поиска 
		  Search_interpolation(a, big_n, el);
	   }
	   auto end3 = steady_clock::now();
	   //auto MilliSeconds3 = duration_cast<milliseconds>(end3 - begin3).count();
	   auto MilliSeconds3 = duration_cast<seconds>(end3 - begin3).count();
	   // сколько заняло миллисекунд 5 итераций
	   //std::cout << "Прошедшее время (в миллисекундах) для Sequential Search: " << MilliSeconds1 / 5 << endl;
	   //std::cout << "Прошедшее время (в миллисекундах) для Binary Search: " << MilliSeconds2 / 5 << endl;
	   //std::cout << "Прошедшее время (в миллисекундах) для Interpolation Search: " << MilliSeconds3 / 5 << endl;

	   std::cout << "Прошедшее время (в секундах) для Sequential Search: " << MilliSeconds1 / 5 << endl;
	   std::cout << "Прошедшее время (в секундах) для Binary Search: " << MilliSeconds2 / 5 << endl;
	   std::cout << "Прошедшее время (в секундах) для Interpolation Search: " << MilliSeconds3 / 5 << endl;
	   std::cout << "-----------------------------------------------------" << endl;
	   std::cout << "-----------------------------------------------------" << endl;
	   std::cout << endl;

	   delete[] a;
	}
/*	// Измерение времени работы кода
	/// *** в секундах
	double el = 100.0;
	//cout << fixed << setprecision(5); // три знака после запятой
	double* time = new double[5];
	double key = 0;
	for (int i = 0; i < 5; i++)
	{
		cout << i + 1 << " итерация" << endl;

		auto begin = steady_clock::now();
		(Search_sequential(Darr, Asize, el) == -1) ?
			cout << el << " не найден в этом массиве" << endl :
			cout << el << " был найден по указателю: " << key << endl;
		auto end = steady_clock::now();

		auto elapsedSeconds = duration_cast<seconds>(end - begin).count();
		//auto elapsedSeconds = duration_cast<milliseconds>(end - begin).count();
		time[i] = elapsedSeconds;
		cout << "Прошедшее время (в секундах): " << elapsedSeconds << endl; // сколько заняло секунд
		//cout << "Прошедшее время (в миллисекундах): " << elapsedSeconds << endl; // сколько заняло секунд
	}
	// вычисляем среднее время итераций
	double everageTime = (time[0] + time[1] + time[2] + time[3] + time[4]) / 5;
	cout << endl << "Затраченное время (среднее): " << everageTime << " сек." << endl;
	//cout << endl << "Затраченное время (среднее): " << everageTime << " мсек." << endl;
	cout << "-----------------------------------------------------" << endl;
	cout << "-----------------------------------------------------" << endl;
	cout << endl;
*/
	delete[] Iarr;
	delete[] Darr;

	// Тесты ASSERT
	std::cout << "--- Тест ASSERT отсортирован ли массив ? ------------" << endl;
	Test_sortArr();
	std::cout << endl;
	std::cout << "--- Тест ASSERT Последовательный поиск по массиву ---" << endl;
	Test_Search_sequential();
	std::cout << endl;
	std::cout << "--- Тест ASSERT Бинарный поиск по массиву -----------" << endl;
	Test_Search_binary();
	std::cout << endl;
	std::cout << "--- Тест ASSERT Интерполяционный поиск по массиву ---" << endl;
	Test_Search_interpolation();
	std::cout << endl;

	std::cout << "--- Тест ASSERT Сортировка массива пузырьком --------" << endl;
	Test_Sorting_bubbles();
	std::cout << endl;
	std::cout << "--- Тест ASSERT Сортировка массива merge слиянием ---" << endl;
	Test_Sorting_merge();
	std::cout << endl;
	std::cout << "--- Тест ASSERT Сортировка массива quick быстро -----" << endl;
	Test_Sorting_quick();
	std::cout << endl;

	std::cout << "-----------------------------------------------------" << endl;
	std::cout << "-----------------------------------------------------" << endl;
	return 0;
}