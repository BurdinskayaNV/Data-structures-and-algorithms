/// \file Dynamic.cpp
/// \brief Dynamic programming - Динамическое программирование
/// \brief Вариант 6 - Задача Отравленный пирог
/// \brief Для игры «Отравленный пирог» используется прямоугольный пирог, разделенный на 
/// \brief M «строк» горизонтальными разрезами и на N «столбцов» – вертикальными.
/// \brief Таким образом, пирог должен быть разбит на M × N клеток, правая нижняя из которых «отравлена».
/// \brief Играют двое игроков, ходы делаются по очереди. 
/// \brief Каждый ход заключается в том, что игрок выбирает одну из еще не съеденных клеток пирога и съедает все клетки,
/// \brief расположенные левее и выше выбранной (в том числе и выбранную). 
/// \brief Проигрывает тот, кто съедает отравленную клетку.
/// \brief Входные данные Данные во входном файле расположены в следующем порядке: M, N (1 ≤ M, N ≤ 9), X1, ...,XM. 
/// \brief Здесь Xi – число оставшихся клеток в i-м снизу горизонтальном ряду. 
/// \brief Все числа во входном файле разделяются пробелами и/или символами перевода строки.
/// \brief Выходные данные В первую строку выходного файла необходимо вывести количество различных выигрышных ходов К,
/// \brief а в последующие K строк – сами выигрышные ходы.
/// \brief Каждый ход задается парой чисел (i, j), где i – номер (снизу) горизонтального ряда, а j –номер (справа) вертикального ряда,
/// \brief которому принадлежит выбранная клетка (1 ≤ i ≤ M, 1≤ j ≤ N). 
/// \brief https://github.com/ivtipm/Data-structures-and-algorithms/blob/main/tasks/task_s1_dynamic_programming.md
/// \author Бурдинская Наталья ВМК-22
/// \date 10.03.2024

#include <iostream> //объявляет cin cout
#include <cassert>  //для assert
#include <locale>   // определяет функцию setlocale для установки русской локали
#include <string>   //для использования строк
#include <fstream>   // для работы с файлами
#include <exception> // обработка исключений
using namespace std;
const string infile = "input.txt";
const string outfile = "output.txt";

/// функция выделение памяти для двумерного массива N х М
/// \param n первое целое число 
/// \param m второе целое число
/// \param n x m размерность матрицы
/// \return ** объявляет указатель на int, на выходе будет целочисленная матрица А
static int** Memo_Array(int n, int m)
{
	// инициализация всего двумерного массива нулями
	int** a = new int* [n]; // строк N
	for (size_t i = 1; i <= n; i++)	a[i] = new int[m+1] {0}; // столбцов M
	a[n][m] = 2;  // правый нижний из которых «отравлен» равен 2
	// если a[n][m] = 0 - это кусок пирога
	// если a[n][m] = 1 - этот кусок пирога съели
	// если a[n][m] = 2 - это отравленный кусок пирога
	return a; // возврат двумерного массива А из функции Memo_Array
}

/// процедура вывода на экран двумерного массива N х М
/// \param a матрица - пирог
/// \param n первое целое число 
/// \param m второе целое число
/// \param n x m размерность матрицы
/// \return процедура ничего не возвращает, просто выводит массив на экран
static void Screen_Array(int** a, size_t n, size_t m)
{
	cout << "если a[n][m] = 0 - это кусок пирога" << endl;
	cout << "если a[n][m] = 1 - этот кусок пирога съели" << endl;
	cout << "если a[n][m] = 2 - это отравленный кусок пирога" << endl;
	cout << endl;
	for (size_t i = 1; i <= n; i++) // строк N
	{
		for (size_t j = 1; j <= m; j++) // столбцов M
			cout << a[i][j] << " ";
		cout << endl;
	}
	cout << endl;
}
/// функция поиска не съеденных кусков
/// \param n первое целое число 
/// \param m второе целое число
/// \param n x m размерность матрицы
/// \return функция boolean, на выходе будет false или true
static bool Search_pie(int** a, size_t n, size_t m)
{
	for (size_t i = 1; i <= n; i++) // строк N
	{
		for (size_t j = 1; j <= m; j++) // столбцов M
		{
			if ((a[i][j] == 0) || (a[i][j] == 2)) {
				return true; break;
			}
			else return false;
		}
	}
}

/// <summary>
/// Входные данные. Начальное открытие файла.
/// Данные во входном файле расположены в следующем порядке: M, N (1 ≤ M, N ≤ 9), X1, ...,XM.
/// Здесь Xi – число оставшихся клеток в i-м снизу горизонтальном ряду.
/// </summary>
/// <param infile = "input.txt"></param>
/// <param name="a"></param>
/// <param name="n"></param>
/// <param name="m"></param>
static void WriteInFile(const string& infile, int** a, size_t n, size_t m)
{
	string str;
	// режим открытия файла дл¤ записи ios::out
	// устанавливаетс¤ при создании файла
	ofstream Fin(infile, ios::out); //затирает старые и пишет новые данные
	if (!Fin.is_open())	  // Если не открыт файл
	{
		throw runtime_error("Файл input.txt не найден");
	}
	// пишем в файл заданные n и m
	Fin << n << " " << m << endl;
	// пишем в файл оставшиеся куски пирога
	for (size_t i = 1; i <= n; i++) // строк N
	{
		str = "";
		for (size_t j = 1; j <= m; j++) // столбцов M
		{
			if ((a[i][j] == 0) || (a[i][j] == 2)) str = str + to_string(a[i][j]) + " ";
		}
		Fin << str << endl;
	}
	Fin << endl;
	Fin.close(); // функция close() закрывает поток файла
	cout << "Пишем в текстовый файл input.txt. Конец записи в файл." << endl;
	cout << "-----------------------------------------------------" << endl;
	cout << endl;
}
/// <summary>
/// Входные данные. добавление записей в файл
/// Данные во входном файле расположены в следующем порядке: M, N (1 ≤ M, N ≤ 9), X1, ...,XM.
/// Здесь Xi – число оставшихся клеток в i-м снизу горизонтальном ряду.
/// </summary>
/// <param infile = "input.txt"></param>
/// <param name="a"></param>
/// <param name="n"></param>
/// <param name="m"></param>
static void AddInFile(const string& infile, int** a, size_t n, size_t m)
{
	string str;
	// режим открытия файла дл¤ записи ios::app
	// устанавливаетс¤ при создании файла
	ofstream Fin(infile, ios::app); //добавляет данные
	if (!Fin.is_open())	  // Если не открыт файл
	{
		throw runtime_error("Файл input.txt не найден");
	}
	// пишем в файл заданные n и m
	Fin << n << " " << m << endl;
	// пишем в файл оставшиеся куски пирога
	for (size_t i = 1; i <= n; i++) // строк N
	{
		str = "";
		for (size_t j = 1; j <= m; j++) // столбцов M
		{
			if ((a[i][j] == 0) || (a[i][j] == 2)) str = str + to_string(a[i][j]) + " ";
			else str = str + "  ";
		}
		Fin << str << endl;
	}
	Fin << endl;
	Fin.close(); // функция close() закрывает поток файла
	cout << "Пишем в текстовый файл input.txt. Конец записи в файл." << endl;
	cout << "-----------------------------------------------------" << endl;
	cout << endl;
}

/// <summary>
/// Выходные данные В первую строку выходного файла необходимо вывести количество различных выигрышных ходов К,
/// а в последующие K строк – сами выигрышные ходы.
/// Каждый ход задается парой чисел (i, j), где i – номер (снизу) горизонтального ряда, а j –номер (справа) вертикального ряда,
/// которому принадлежит выбранная клетка (1 ≤ i ≤ M, 1≤ j ≤ N). 
/// </summary>
/// <param outfile = "output.txt"></param>
/// <param name="a"></param>
/// <param name="n"></param>
/// <param name="m"></param>
static void AddOutFile(const string& outfile, string fstr, int k)
{
	// режим открытия файла дл¤ записи ios::app
	// устанавливаетс¤ при создании файла
	ofstream Fout(outfile, ios::app); //добавляет данные
	if (!Fout.is_open())	  // Если не открыт файл
	{
		throw runtime_error("Файл output.txt не найден");
	}
	// пишем в файл k количество удачных ходов
	Fout << k << endl;
	// пишем в файл съевшие куски пирога
	Fout << fstr << endl;
	Fout << endl;
	Fout.close(); // функция close() закрывает поток файла
	cout << "Пишем в текстовый файл output.txt. Конец записи в файл." << endl;
	cout << "-----------------------------------------------------" << endl;
	cout << endl;
}

/// функция поедания пирога
/// \param a матрица - пирог
/// \param n первое целое число 
/// \param m второе целое число
/// \param n x m размерность матрицы
/// \return процедура ничего не возвращает, просто выводит массив на экран
/// \return Мемоизация
static string Eating_pie(int** a, size_t n, size_t m)
{
	int x, y; string str; string fstr; int k;
	cout << "Введите координаты куска пирога x <= n и y <= m" << endl;
	// сохраняем их в x и y
	cout << "x = "; cin >> x;
	cout << "y = "; cin >> y;
	cout << endl;
	// если координаты выходят за пределы массива
	if ((x > n) || (y > m)) {
	   cout << "Такого куска нет в пироге, задайте новые координаты... " << endl;
	   cout << endl;
	   str = Eating_pie(a, n, m);
	}
	// если по координатам кусок уже съеден
	else if (a[x][y] == 1) {
	   cout << "Этот кусок пирога съели, возьмите другой... " << endl;
	   cout << endl;
	   str = Eating_pie(a, n, m);
	}
	// если по координатам кусок отправлен
	else if (a[x][y] == 2) str = "ВЫ ПРОИГРАЛИ, кусок отравлен...";
	// кусок можно съесть
	else
	{
	   fstr = ""; k = 0;
	   for (size_t i = 1; i <= x; i++) // строк N
	   {
		  for (size_t j = 1; j <= y; j++) // столбцов M
		  {
			  if (a[i][j] == 0) 
			  { 
				  fstr = fstr + to_string(a[i][j]) + " ";
				  k = k + 1;
				  a[i][j] = 1;
			  }
			 //fstr = fstr + "/n";
		  }
	   }
	   Screen_Array(a, n, m);
	   AddInFile(infile, a, n, m);
	   AddOutFile(outfile, fstr, k);
	   bool v = Search_pie(a, n, m);
	   if (v = true) str = Eating_pie(a, n, m);
	}
	return str;
}

static void Test_Eating_pie() {
	int n = 3; int m = 3;
    int** a = new int* [n]; // строк N
	for (size_t i = 1; i <= n; i++)	a[i] = new int[m+1] {0}; // столбцов M
	a[n][m] = 2;
//	assert(Eating_pie(a, 3, 3) == );    

    cout << "Тест Test_Eating_pie выполнен успешно " << endl;
    cout << endl;
}

/// функция освобождение памяти двумерного массива N х М
/// \param a матрица - пирог
/// \param n первое целое число 
/// \param m второе целое число
/// \param n x m размерность матрицы
/// \return процедура ничего не возвращает, просто очищает память массива
static void Del_Array(int** a, size_t n, size_t m)
{
	for (size_t i = 1; i <= n; i++)
	{
		delete[] a[i];
	}
	delete[] a;
}

int main()
{
	// «Rus» локализация произойдёт на русский язык
	setlocale(LC_ALL, "russian");

	int n, m;
	cout << "Введите два целых числа для деления пирога на части" << endl;
	// сохраняем их в m и n
	cout << "n = "; cin >> n;
	cout << "m = "; cin >> m;
	cout << endl;
	int** a = Memo_Array(n, m);
	Screen_Array(a, n, m);
	WriteInFile(infile, a, n, m);
	ofstream Fout(outfile, ios::out);
	Fout << "Начало" << endl;
	Fout << endl;
	Fout.close(); // функция close() закрывает поток файла
	// поедание пирога
	string str = Eating_pie(a, n, m);
	cout << str << endl;
	cout << endl;
   // Test_Eating_pie();
    Del_Array(a, n, m);
	return 0;
}
