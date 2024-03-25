/// \file Analysis_modul.h
/// \brief Ðàáîòà ñ ìàññèâàìè
/// \author Áóðäèíñêàÿ Íàòàëüÿ ÂÌÊ-22
/// \date 04.03.2024

#pragma once
#include <string>    // äëÿ èñïîëüçîâàíèÿ ñòðîê
#include <iomanip>   // äëÿ setw setprecision
#include <cassert>   // äëÿ assert
#include <iostream>  // îáúÿâëÿåò cin cout
#include <ctime>     // âðåìÿ äëÿ ðàíäîìíûõ ýëåìåíòîâ ìàññèâà
#include <fstream>   // äëÿ ðàáîòû ñ ôàéëàìè
#include <exception> // îáðàáîòêà èñêëþ÷åíèé
#include <locale>    // îïðåäåë¤åò ôóíêöèþ setlocale äëÿ ðóññêîé ëîêàëè 
using namespace std; // ïðîñòðàíîñòâî èìåí std::

int result;
int x = 0, n = 200;

int* Iarr = new int[n] {0}; // Int
double* Darr = new double[n] {0}; // double
string fileTxt = "TxtArray.txt";
string fileBin = "BinArray.txt";
string file_name;

//---ïðîöåäóðà ââîäà ìàññèâà ðàçìåðíîñòè n ñëó÷àéíûìè ÷èñëàìè
// äèíàìè÷åñêèå ìàññèâû â ôóíêöèè ïåðåäàþòñÿ êàê âåêòîðû
// íè÷åãî íå âîçâðàùàåò, ïðîñòî ââîäèò äàííûå â ìàññèâ
template <typename TArray>
void Set_array(TArray* a, size_t size, int high, int low)
//void Set_array(TArray* a, size_t size, TArray high, TArray low)
{
	// ìàññèâ a, size, high, low - ôîðìàëüíûå ïàðàìåòðû
	// çàïîëíåíèå ìàññèâà ñëó÷àéíûìè ÷èñëàìè îò low äî high âêëþ÷èòåëüíî
	TArray delta = high - low; // äèàïàçîí ðàíäîìà
	for (size_t i = 0; i < size; ++i) // íóìåðàöèÿ ñ íóë¤ äî size-1
	{
		//a[i] = (((TArray)rand() / RAND_MAX) * delta) + low;
		a[i] = rand() % (2 * high) + low;
		// rand() âîçâðàùàåò ñëó÷àéíîå öåëîå ÷èñëî
	}
}

//---ïðîöåäóðà âûâîäà íà ýêðàí ìàññèâà N
// íè÷åãî íå âîçâðàùàåò, ïðîñòî âûâîäèò íà êîíñîëü
template<typename TArray>
void Screen_array(const TArray* a, size_t size)
{
	// ìàññèâ a, size - ôîðìàëüíûå ïàðàìåòðû
	for (size_t i = 0; i < size; i++)
	{
		cout << a[i] << "  ";
		// cout << "a[" << i << "] = " << a[i] << " ";
	}
	cout << endl;
}

//---òåñò ðàáîòû ñ ìàññèâàìè
void Test_Work_array()
{
	// äëÿ ïðîâåðêè øàáëîíà TArray
	cout << "----- Ïðîâåðêà øàáëîííîé ôóíêöèè ïðè ââîäå ìàññèâà ðàíäîìíûìè ýëåìåíòàìè -----" << endl;
	cout << "------- Ìàññèâ Int ----------------------------------" << endl;
	Set_array(Iarr, n, 100, 0); // âûïîëíÿåì ââîä ìàññèâà Int
	Screen_array(Iarr, n); // âûâîäèì íà ýêðàí ìàññèâ Int
	cout << endl;
	// âûçâàòü â ïðîãðàììå îäèí ðàç, ïåðåä âûâîäîì ÷èñåë.
	cout << fixed << setprecision(2); // äâà çíàêà ïîñëå çàïÿòîé
	cout << "------- Ìàññèâ Double -------------------------------" << endl;
	Set_array(Darr, n, 100.00, 0.00); // âûïîëíÿåì ââîä ìàññèâà Double
	Screen_array(Darr, n); // âûâîäèì íà ýêðàí ìàññèâ Double
	cout << endl;
}

template <typename TArray>
/// âûâîäèò ìàññèâ â ôàéë
/// \param a ìàññèâ òèïà TArray
/// \param n ðàçìåð ìàññèâà
/// \param FileName ôàéë, êóäà âûâîäèòñÿ ìàññèâ
/// \return íè÷åãî, íî â ôàéë âûâîäèòüñÿ ìàññèâ
void output_to_file(const TArray* a, unsigned n, const string& file_name, TArray comparisions, TArray nearby) {
    ofstream Fin(file_name, ios::app); 
	if (!Fin.is_open())	  
	{
		throw runtime_error("Файл не найден");
	}

	Fin << "Массив " << endl;
	for (size_t i = 0; i < n; ++i)
	{
		Fin << a[i] << " ";
	}
	Fin << "выполнено " << comparisions << " сравнений" << endl;
	Fin << "Это число " << nearby << endl;
	Fin << endl;
	Fin.close(); 
    //cout << "-----------------------------------------------------" << endl;
}

/// Ôóíêöèÿ ïîèñêà áëèæàéøåãî ýëåìåíòà ê x â ìàññèâå
/// \param n ðàçìåð ìàññèâà
/// \param x ÷èñëî, êîòîðîå íóæíî íàéòè
/// \param arr ÷èñëîâîé ìàññèâ
/// \return ðåçóëüòàò nearby - áëèæíåãî ÷èñëà
template <typename TArray>
TArray find_nearby(const TArray* arr, size_t size, TArray x, TArray comparisions, const string& file_name) // comparisions - сравнение
{
    comparisions = 1; 
    if (size == 1)	return arr[0]; 
    TArray nearby = arr[0];	
    TArray difference = abs(x - arr[0]); 
    for (size_t i = 1; i < size; i++)  
    {
        TArray currentDiff = abs(x - arr[i]); 
        if (currentDiff < difference)		  
        {
            comparisions++; 
            nearby = arr[i];	
            difference = currentDiff; 
        }
    }
    output_to_file(arr, size, file_name, comparisions, nearby);
	return nearby;
}

//---Тест - find_nearby
static void Test_Find_nearby()
{
    int sizemin = 5;
    int comparision1 = 0;
    //double comparision2 = 0.00;
    int* a = new int[sizemin] {1, 2, 3, 4, 5};
    //double* b = new double[sizemin] {1.11, 2.22, 3.33, 4.44, 5.55};
    int* c = new int[sizemin] {5, 3, 2, 67, 34};

    int test1 = find_nearby(a, sizemin, 8, comparision1, file_name);
    assert(test1 == 5);

    //double test2 = find_nearby(b, sizemin, 1.132, comparision2);
    //assert(test2 == 1.11);

    int test3 = find_nearby(c, sizemin, 1, comparision1, file_name);
    assert(test3 == 2);

    delete[] a;
    //delete[] b;
    delete[] c;
    cout << "--- Test_Find_nearby() выполнен успешно -------------" << endl;
}
