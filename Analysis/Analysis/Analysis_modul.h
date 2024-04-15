/// \file Analysis_modul.h
/// \brief ������ � ���������
/// \author ���������� ������� ���-22
/// \date 04.03.2024

#pragma once
#include <string>    // ��� ������������� �����
#include <iomanip>   // ��� setw setprecision
#include <cassert>   // ��� assert
#include <iostream>  // ��������� cin cout
#include <ctime>     // ����� ��� ��������� ��������� �������
#include <fstream>   // ��� ������ � �������
#include <exception> // ��������� ����������
#include <locale>    // ��������� ������� setlocale ��� ������� ������ 
using namespace std; // ������������� ���� std::

int result;
int x = 0, n = 200;
string str_n, str_x, file_name;
int* Iarr = new int[n] {0}; // ��������� ������������ ������ Int
double* Darr = new double[n] {0}; // ��������� ������������ ������ double
string fileTxt = "TxtArray.txt";

//---��������� ����� ������� ����������� n ���������� �������
// ������������ ������� � ������� ���������� ��� �������
// ������ �� ����������, ������ ������ ������ � ������
template <typename TArray>
void Set_array(TArray* a, size_t size, int high, int low)
//void Set_array(TArray* a, size_t size, TArray high, TArray low)
{
	// ������ a, size, high, low - ���������� ���������
	// ���������� ������� ���������� ������� �� low �� high ������������
	TArray delta = high - low; // �������� �������
	for (size_t i = 0; i < size; ++i) // ��������� � ��� �� size-1
	{
		a[i] = (((TArray)rand() / RAND_MAX) * delta) + low;
		a[i] = rand() % (2 * high) + low;
		// rand() ���������� ��������� ����� �����
	}
}

//---��������� ������ �� ����� ������� N
// ������ �� ����������, ������ ������� �� �������
template<typename TArray>
void Screen_array(const TArray* a, size_t size)
{
	// ������ a, size - ���������� ���������
	for (size_t i = 0; i < size; i++)
	{
		cout << a[i] << "  ";
		// cout << "a[" << i << "] = " << a[i] << " ";
	}
	cout << endl;
}

//---���� ������ � ���������
void Test_Work_array()
{
	// ��� �������� ������� TArray
	cout << "----- �������� ��������� ������� ��� ����� ������� ���������� ���������� -----" << endl;
	cout << "------- ������ Int ----------------------------------" << endl;
	Set_array(Iarr, n, 100, 0); // ��������� ���� ������� Int
	Screen_array(Iarr, n); // ������� �� ����� ������ Int
	cout << endl;
	// ������� � ��������� ���� ���, ����� ������� �����.
	cout << fixed << setprecision(2); // ��� ����� ����� �������
	cout << "------- ������ Double -------------------------------" << endl;
	Set_array(Darr, n, 100, 0); // ��������� ���� ������� Double
	Screen_array(Darr, n); // ������� �� ����� ������ Double
	cout << endl;
}

template <typename TArray>
/// ������� ������ � ����
/// \param a ������ ���� TArray
/// \param n ������ �������
/// \param FileName ����, ���� ��������� ������
/// \return ������, �� � ���� ���������� ������
void output_to_file(const TArray* a, unsigned n, const string& file_name) {
	// ����� �������� ����� �� ������ ios::out
	// �������������� ��� �������� �����
	ofstream Fin(file_name, ios::out); //�������� ������ � ����� ����� ������
	if (!Fin.is_open())	  // ���� �� ������ ����
	{
		throw runtime_error("���� �� ������");
	}
	// ����� � ���� ������������ ������
	for (size_t i = 0; i < size; ++i)
	{
		Fin << a[i] << " " << endl;
	}
	Fin.close(); // ������� close() ��������� ����� �����
	cout << "����� � ��������� ����. ����� ������ � ����." << endl;
	cout << "-----------------------------------------------------" << endl;
}

/// ������� ������ ���������� �������� � x � �������
/// (n-1)*4+3 =  => Big-O(n), �.�. ��������� ��������
/// \param n ������ �������
/// \param x �����, ������� ����� �����
/// \param arr �������� ������
/// \return ��������� nearby - �������� �����
template <typename TArray>
TArray find_nearby(const TArray* arr, size_t size, TArray x, TArray comparisions) // comparisions - ���������
{
    comparisions = 1; // ���������� ��������� ����������� ������������� 1
    if (size == 1)	return arr[0]; // ���� ������ � 1 ���������, �� ��������� �������� �������� arr[0]
    TArray nearby = arr[0];	// ������������, ��� ������ ������� �������� ������  - �����
    TArray difference = abs(x - arr[0]); // ������� ������� ����� x � ������ ��������� �� ������
    for (size_t i = 1; i < size; i++)  // BigO(n-1)
    {
        TArray currentDiff = abs(x - arr[i]); // ������� ������� � ������ ��������
        if (currentDiff < difference)		  // ��� ���������
        {
            comparisions++; // ������� ���������
            nearby = arr[i];	// ������������ �� �������
            difference = currentDiff; // �������� ���������� ������� �� ������� � ������ ��������
        }
    }
	//ofstream Fin("TxtArray.txt", ios::app); //�������� ������ � ����� ����� ������
	ofstream Fin(file_name, ios::app); //�������� ������ � ����� ����� ������
	if (!Fin.is_open())	  // ���� �� ������ ����
	{
		throw runtime_error("���� �� ������");
	}
	// ����� � ���� ������������ ������
	Fin << "������ " << endl;
	for (size_t i = 0; i < size; ++i)
	{
		Fin << arr[i] << " ";
	}
	Fin << endl;
	Fin << "��������� " << comparisions << " ���������" << endl;
	Fin << "��� ����� " << nearby << endl;
	Fin << endl;
	Fin.close(); // ������� close() ��������� ����� �����
	return nearby;
}

//---���� ������� find_nearby  ///**** ������� �������� ������
static void Test_Find_nearby()
{
    int sizemin = 5;
    int comparision1 = 0;
    //double comparision2 = 0.00;
    int* a = new int[sizemin] {1, 2, 3, 4, 5};
    //double* b = new double[sizemin] {1.11, 2.22, 3.33, 4.44, 5.55};
    int* c = new int[sizemin] {5, 3, 2, 67, 34};

    int test1 = find_nearby(a, sizemin, 8, comparision1);
    assert(test1 == 5);

    //double test2 = find_nearby(b, sizemin, 1.132, comparision2);
    //assert(test2 == 1.11);

    int test3 = find_nearby(c, sizemin, 1, comparision1);
    assert(test3 == 2);

    delete[] a;
    //delete[] b;
    delete[] c;
    cout << "--- Test_Find_nearby() �������� ������� -------------" << endl;
}