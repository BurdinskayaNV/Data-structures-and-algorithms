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
using namespace NamespaceMassiv; // пространство имён для работы с массивом
using namespace NamespaceFile; // пространство имён для работы с массивом в файлах
using namespace NamespaceSearch; // пространство имён для работы с поиском в массиве 
using namespace NamespaceSort; // пространство имён для работы с сортировкой в массиве 

int main()
{
	system("chcp 65001 > nul"); //подключение русского языка 
	setlocale(LC_ALL, "RUSSIAN");
	// Генерирует случайное число, используя текущею дату, для непредсказуемости результата
	srand(time(0));
	// для проверки шаблона TArray
	size_t Asize = 100; // размерность массива

	int* Iarr = new int[Asize] {0}; // описываем динамический массив Int
	double* Darr = new double[Asize] {0}; // описываем динамический массив double
	string fileTxt = "TxtArray.txt";
	string fileBin = "BinArray.txt";

	cout << "----- Проверка шаблонной функции при вводе массива рандомными элементами -----" << endl;
	cout << "------- Массив Int ----------------------------------" << endl;
	Vvod_array(Iarr, Asize, 100, -100); // выполняем ввод массива Int
	Screen_array(Iarr, Asize); // выводим на экран массив Int
	cout << endl;
	// вызвать в программе один раз, перед выводом чисел.
	cout << fixed << setprecision(2); // два знака после запятой
	cout << "------- Массив Double -------------------------------" << endl;
	Vvod_array(Darr, Asize, 100, -100); // выполняем ввод массива Double
	Screen_array(Darr, Asize); // выводим на экран массив Double
	cout << endl;

	cout << "------- Работа с текстовым файлом -------------------" << endl;
	// выполняем запись массива в текстовый файл TxtArray.txt
	try { WriteFile(fileTxt, Iarr, Asize); }
	catch (const invalid_argument& error) {
		cout << error.what();
	}
	// читаем из текстового файла TxtArray.txt массив и выдаем на консоль
	try   // проверка на исключения
	{
		// Находим количество элементов массива из файла TxtArray.txt
		size_t size_1 = SizeFile(fileTxt);
	}
	catch (const exception& error) // файл TxtArray.txt не открыт или пуст
	{
		// Код, который выполняется при возникновении исключения типа
		// Exception генерируется в блоке try
		cout << error.what() << endl; // Завершить
	}
	// выводим на экран массив введеных коэффициентов
	int* arrtxt = new int[Asize] {0}; // описываем динамический массив Int
	try { ReadFile(fileTxt, arrtxt, Asize); }
	catch (const invalid_argument& error) {
		cout << error.what();
	}
	Screen_array(arrtxt, Asize); // выводим на экран массив введеных коэффициентов
	cout << endl;

	cout << "------- Работа с бинарным файлом --------------------" << endl;
	// выполняем запись массива в текстовый файл TxtArray.txt
	try { WriteFileBin(fileBin, Iarr, Asize); }
	catch (const invalid_argument& error) {
		cout << error.what();
	}
	// выводим на экран массив введеных коэффициентов
	int* arrbin = new int[Asize] {0}; // описываем динамический массив Int
	try { ReadFileBin(fileBin, arrbin, Asize); }
	catch (const invalid_argument& error) {
		cout << error.what();
	}
	Screen_array(arrbin, Asize); // выводим на экран массив введеных коэффициентов
	cout << endl;

	cout << "-----------------------------------------------------" << endl;
	cout << "-----------------------------------------------------" << endl;
	// Измерение времени работы кода
	double el = 100.0;
	double* time = new double[5];
	double key = 0;
	for (int i = 0; i < 5; i++)
	{
		cout << i + 1 << " итерация" << endl;

		auto begin = steady_clock::now();
		(Poisk_sequential(Darr, Asize, el) == -1) ?
			cout << el << " не найден в этом массиве" << endl :
			cout << el << " был найден по указателю: " << key << endl;
		auto end = steady_clock::now();

		auto elapsedSeconds = duration_cast<milliseconds>(end - begin).count();
		time[i] = elapsedSeconds;
		cout << "Прошедшее время (в миллисекундах): " << elapsedSeconds << endl; // сколько заняло секунд
	}
	// вычисляем среднее время итераций
	double everageTime = (time[0] + time[1] + time[2] + time[3] + time[4]) / 5;
	cout << endl << "Затраченное время (среднее): " << everageTime << endl;
	cout << "-----------------------------------------------------" << endl;
	cout << "-----------------------------------------------------" << endl;
	cout << endl;
	delete[] Iarr;
	delete[] Darr;
	delete[] arrtxt;
	delete[] arrbin;

	// Тесты ASSERT
	cout << "--- Тест ASSERT отсортирован ли массив --------------" << endl;
	Test_sortArr();
	cout << endl;
	cout << "--- Тест ASSERT Последовательный поиск по массиву ---" << endl;
	Test_Poisk_sequential();
	cout << endl;
	cout << "--- Тест ASSERT Бинарный поиск по массиву -----------" << endl;
	Test_Poisk_binary();
	cout << endl;
	cout << "--- Тест ASSERT Интерполяционный поиск по массиву ---" << endl;
	Test_Poisk_interpolation();
	cout << endl;

	return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
