/// \file Recursion.cpp
/// \brief Вариант 6
/// \brief Написать функцию умножения двух чисел, используя только операцию сложения.
/// \author Бурдинская Наталья ВМК-22
/// \date 04.03.2024

#include <iostream>
#include <assert.h>
#include <iomanip>
#include <locale>
using namespace std;
int result;
int m, n;

///Вычисляет умножения двух чисел, используя только операцию сложения
/// \param m первое целое число
/// \param n второе целое число
/// \return результат умножения через рекурсию
int rmultiply(int m, int n) // rmultiply - перевод многократно
{
   if(n > 1)
      return(m + (rmultiply(m,n - 1)));
      // если m=6 n=3
	  // 6 + rmultiply(3 - 1)
	  // 6 + 6 + rmultiply(2 - 1)
	  // 6 + 6 + 6 + всё rmultiply(1 - 1) n =1
	  // return 6 + 6 + 6
   else if ((m == 0) || (n == 0))
      return 0;
      // умножение на 0 равно 0
   else if (n == 1)
      return m;
      // умножение на 1 равно m
   else if (m == 1)
      return n;
      // умножение на 1 равно n
}

/// Измерение размера стека с помощью бесконечной рекурсии
int StackSizeMeasurement(int& i) // StackSizeMeasurement - перевод Измерение размера стека
{
    cout << i << "   ";
    i += 1;
    StackSizeMeasurement(i);
    return 0;
}

void Test_StackSizeMeasurement() {
    assert(rmultiply(2, 4) == 8);    // 2 * 4 = 8
    assert(rmultiply(8, 50) == 400); // 8 * 50 = 400
    assert(rmultiply(1, 25) == 25);  // 1 * 25 = 25
	cout << "Тест выполнен успешно " << endl;
	cout << endl;
}

int main()
{
	// «Rus» локализация произойдёт на русский язык
	setlocale(LC_ALL, "russian");
    cout << "Введите два целых числа для умножения" << endl; 
    // сохраняем их в m и n
    cin >> m >> endl;
    cin >> n >> endl;
	try {
       result = rmultiply(m,n);
	}
    catch (const std::invalid_argument& error) {
        std::cout << error.what();
    }
    cout << "результат умножения через рекурсию " << result << endl;
	cout << endl;
	Test_StackSizeMeasurement();
	//int n = 1;
    //StackSize(n);
    return 0;	
}

