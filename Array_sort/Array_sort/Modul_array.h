/// \file Modul_array.h
/// \brief ������ � ���������
/// \author ���������� ������� ���-22
/// \date 18.02.2024

#pragma once
#include <string>    // ��� ������������� �����
#include <iomanip>   // ��� setw setprecision
#include <cassert>   // ��� assert
#include <iostream>  // ��������� cin cout
#include <ctime>     // ����� ��� ��������� ��������� �������
#include <exception> // ��������� ����������
#include <locale>    // ��������� ������� setlocale ��� ������� ������ 
#include <chrono>    // ��������� ������� ������ ����
#include <stack>	 // ��� �����, ������� push � pop
#include <cstdio> 
using namespace std::chrono;
using namespace std; // ������������� ���� std::

size_t Asize = 10; // *** ��� �������� ������� �������, �������� ����� ������������ ��� size_t.
// *** �� ����� ������� ������ ������������� �������� �� �������� ���������.
int* Iarr = new int[Asize] {0}; // ��������� ������������ ������ Int
double* Darr = new double[Asize] {0}; // ��������� ������������ ������ double

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
	cout << "�������� ��������� ������� ��� ����� ������� ���������� ����������" << endl;
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