/// \file Modul_array.h
/// \brief ������ � ���������
/// \author ���������� ������� ���-22
/// \date 18.02.2024

#pragma once
#include <string>    // ��� ������������� �����
#include <iomanip>   // ��� setw setprecision
#include <cassert>   // ��� assert
#include <iostream>  // ��������� cin cout
#include <ctime>    // ����� ��� ��������� ��������� �������
#include <fstream>   // ��� ������ � �������
#include <exception> // ��������� ����������
#include <locale>    // ��������� ������� setlocale ��� ������� ������ 
#include <chrono>    // ��������� ������� ������ ����
using namespace std::chrono;
using namespace std; // ������������� ���� std::

size_t Asize = 10; // *** ��� �������� ������� �������, �������� ����� ������������ ��� size_t.
// *** �� ����� ������� ������ ������������� �������� �� �������� ���������.
int* Iarr = new int[Asize] {0}; // ��������� ������������ ������ Int
double* Darr = new double[Asize] {0}; // ��������� ������������ ������ double
string fileTxt = "TxtArray.txt";
string fileBin = "BinArray.txt";

//---��������� ����� ������� ����������� size ���������� �������
// ������������ ������� � ������� ���������� ��� �������
// ������ �� ����������, ������ ������ ������ � ������
/// *** Vvod_array ������������ � Set_array - ������ ������
/// *** TArray high, TArray low ���������� ��� ��� TArray
template <typename TArray>
void Set_array(TArray* a, size_t size, int high, int low)
//void Set_array(TArray* a, size_t size, TArray high, TArray low)
{
	// ������ a, size, high, low - ���������� ���������
	// ���������� ������� ���������� ������� �� low �� high ������������
	TArray delta = high - low; // �������� �������
	for (size_t i = 0; i < size; ++i) // ��������� � ��� �� size-1
	{
		//a[i] = (((TArray)rand() / RAND_MAX) * delta) + low;
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
/// *** ������� � ��������� ����
void Test_Work_array()
{
	// ��� �������� ������� TArray
	cout << "-- �������� ��������� ������� ��� ����� ������� ���������� ���������� --" << endl;
	cout << "------- ������ Int ----------------------------------" << endl;
	Set_array(Iarr, Asize, 100, -100); // ��������� ���� ������� Int
	Screen_array(Iarr, Asize); // ������� �� ����� ������ Int
	cout << endl;
	// ������� � ��������� ���� ���, ����� ������� �����.
	cout << fixed << setprecision(2); // ��� ����� ����� �������
	cout << "------- ������ Double -------------------------------" << endl;
	Set_array(Darr, Asize, 100.00, -100.00); // ��������� ���� ������� Double
	Screen_array(Darr, Asize); // ������� �� ����� ������ Double
	cout << endl;
}

//--- �������, ������� ���������, ������������ �� ������
// ��� ���� ����������: �� ����������� (�� ���������)
// � �������� (�������� ������� ���������� rule: 'l' �� ��������)
template <typename TArray>
bool sortArr(const TArray* a, size_t size, const char rule = '2')
{
	if (size == 0 || size == 1) return true; // 1 ��� 0 ��������� true
	if (rule == 'l') // ���������� �� ��������
		for (size_t i = 0; i < size - 1; i++)
		{
			// ���� ������ ������ ������� ���������� false
			// ������ ��� ���������
			if (a[i] < a[i + 1]) return false;
		}
	else // ���������� �� ������������
		for (size_t i = 0; i < size - 1; i++)
		{
			// ���� ������ ������ ������� ���������� false
			// ������ ��� ������������
			if (a[i] > a[i + 1]) return false;
		}
	return true;
}

//---���� ������ ������� sortArr
void Test_sortArr()
{
	unsigned* sorInt = new unsigned[3] {1, 2, 3};   // ������������� Int
	unsigned* nosorInt = new unsigned[3] {4, 2, 3}; // ��������������� Int, ���������� �������� � ������
	assert(sortArr(sorInt, 3) == true);
	assert(sortArr(nosorInt, 3) == false);
	delete[] sorInt;		// ������������� Int
	delete[] nosorInt;		// ��������������� Int

	double* sortDob = new double[3] {1.11, 2.22, 3.33};   // ������������� double
	double* nosortDob = new double[3] {1.11, 2.22, 1.33}; // ��������������� double, ���������� �������� � �����
	assert(sortArr(sortDob, 3) == true);
	assert(sortArr(nosortDob, 3) == false);
	delete[] sortDob;		// ������������� Double
	delete[] nosortDob;		// ��������������� Double

	string* sortStr = new string[3]{ "aaa", "bbb", "ccc" };   // ������������� string
	string* nosortStr = new string[5]{ "aaa", "bbb", "eee", "ccc", "ddd" }; // ��������������� string, �������� �������� � ��������
	assert(sortArr(sortStr, 3) == true);
	assert(sortArr(nosortStr, 5) == false);
	delete[] sortStr;		// ������������� String
	delete[] nosortStr;		// ��������������� String

	unsigned* decsortInt = new unsigned[3] {3, 2, 1};		// ������������� Int �������
	assert(sortArr(decsortInt, 3, 'l') == true);
	double* decsortDob = new double[3] {3.33, 2.22, 1.11};	// ������������� Dob �������
	assert(sortArr(decsortDob, 2.22, 'l') == true);
	/// *** ������� �������� � �������� ��� � ����� ��� ������ assert
	delete[] decsortInt;
	delete[] decsortDob;

	cout << "--- Test_sortArr() �������� ������� -----------------" << endl;
}

//---���������������� ����� �� �������,
// ���� key ����� ������, �� �������� ��� ������,
// ���� ���, �� �������� ����� -1
/// *** ��� size_t, index ������������ � key
/// *** ��� �������� ������� �������, �������� ����� ������������ ��� size_t.
/// *** �� ����� ������� ������ ������������� �������� �� �������� ���������.
template <typename TArray>
long long Search_sequential(const TArray* a, size_t size, TArray key) /// *** Poisk ������������ � Search 
{
	for (size_t i = 0; i < size; ++i)
		if (a[i] == key) return i; // �������� �������, ���������� ������
	return -1; // �������� �� �������, ��������� -1
}
