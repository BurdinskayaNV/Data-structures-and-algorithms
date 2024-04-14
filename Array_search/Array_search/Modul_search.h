/// \file Modul_search.h
/// \brief ������ � ������� � �������
/// \author ���������� ������� ���-22
/// \date 18.02.2024
#pragma once
/// *** Poisk ������������ � Search

#include "Modul_array.h" // ����� ������������� ����� Modul_array

//---���������������� ����� �� �������,
// BigO(n)-������ ������, Big0(n) - ������� ������, BigO(1)-������ ������
// 
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

//---���� ������ ������� Search_sequential
/// *** �������� ����� �������� �� �������� 
void Test_Search_sequential()
{
	size_t sizemin = 3;
	// ��� �������� ������� TArray
	int* a = new int[sizemin] {1, 2, 3};
	double* b = new double[sizemin] {1.11, 2.22, 3.33};
	string* c = new string[sizemin]{ "Sunday", "Monday", "Tuesday" };

	long long test1 = Search_sequential(a, sizemin, 3);
	assert(test1 == 2); // ����� �������� � ����� �������
	long long test2 = Search_sequential(b, sizemin, 1.11);
	assert(test2 == 0); // ����� �������� � ������ �������
	string str = "Wednesday";
	long long temp3 = Search_sequential(c, sizemin, str);
	assert(temp3 == -1); // ���� ������� �����������
	/// *** 
	long long temp4 = Search_sequential(a, sizemin, 2);
	assert(temp4 == 1);	/// *** �������� ����� �������� �� ��������  

	delete[] a;
	delete[] b;
	delete[] c;
	cout << "--- Test_Search_sequential() �������� ������� -------" << endl;
}

//---�������� ����� � ������� 
// ������� ��� �� ������ ��������� �� 2, ������ ��� ��������� ������ ���� �������? 
// n / (2 * 2 * 2 * ... * 2) = 1 ['2' ����������� x ���], ��� n = 2 ^ x
// ����, ��������������� ���� 2 �� n ���� ��� x, �� ���� ���������� ����������� �������.
// BigO(logn)-������ ������, Big0(logn) - ������� ������, BigO(1)-������ ������
// 
// ���� key ����� ������, �� �������� ��� ������,
// ���� ���, �� �������� ����� -1, ���� ������ �� ������������, �� �������� ����� -2
// �������� ����� �������� ������ � ������������ ������� 
/// *** index ������������ � key
/// *** long long: ������������ ����� ����� �������� � ������ 8 ���� (64 ����)
/// *** ����� ���������� long long int
template <typename TArray>
long long Search_binary(TArray* arr, size_t size, TArray key)
{
	// ���� ������ �� ������������, ��������� -2
	if (sortArr(arr, size) == false) { return -2; }

	size_t low = 0;     // ������ �������, ��������� �������� = 0
	size_t high = size; // ������� �������, ��������� �������� = ����������� �������
	size_t middle;	     // c������� [low,high]

	while (low <= high)
	{
		middle = (low + high) / 2; // ��������� ������ [low,high]
		if (arr[middle] == key) // ���� �������� ����� �������� ��������
			return middle;
		if (arr[middle] > key) // � ����� ����� ��������� ������� �������
			high = middle - 1;	// � ������� �������
		else
			low = middle + 1;    // � ������ �������
	}
	return -1; // �������� �� �������, ��������� -1
}

//---���� ������ ������� Poisk_binary
/// *** ��������� 3 ������
void Test_Search_binary()
{
	size_t sizemin = 5;
	// ��� �������� ������� TArray
	int* a = new int[sizemin] {1, 2, 3, 4, 5}; // ������������
	double* b = new double[sizemin] {1.11, 2.22, 3.33, 4.44, 5.55}; // ������������
	int* c = new int[sizemin] {5, 3, 2, 1, 4}; // �� ������������

	long long test1 = Search_binary(a, sizemin, 5);
	assert(test1 == 4); // ����� �������� � ����� �������
	long long test2 = Search_binary(b, sizemin, 1.11);
	assert(test2 == 0); // ����� �������� � ������ �������
	long long test3 = Search_binary(c, sizemin, 2);
	assert(test3 == -2); // ������ �� ������������
	/// *** ��������� �����
	long long test4 = Search_binary(b, sizemin, 6.66);
	assert(test4 == -1); // *** ���� ������� �����������
	long long test5 = Search_binary(a, sizemin, 3);
	assert(test5 == 2); // *** ����� �������� �� ��������
	long long test6 = Search_binary(b, sizemin, 4.44);
	assert(test6 == 3); // *** ����� �������� �� �� ��������, �� � ������, �� � �����

	delete[] a;
	delete[] b;
	delete[] c;
	cout << "--- Test_Search_binary() �������� ������� -----------" << endl;
}

//---���������������� ������ � �������
// BigO(n)-������ ������, Big0(loglogn) - ������� ������, BigO(1)-������ ������
// 
// ���� index ����� ������, �� �������� ��� ������,
// ���� ���, �� �������� ����� -1, ���� ������ �� ������������, �� �������� ����� -2
// �������� ����� �������� ������ � ������������ ������� 
/// *** index ������������ � key
/// *** long long: ������������ ����� ����� �������� � ������ 8 ���� (64 ����)
/// *** ����� ���������� long long int
template <typename TArray>
long long Search_interpolation(TArray* arr, size_t size, TArray key)
{
	// ���� ������ �� ������������, ��������� -2
	if (sortArr(arr, size) == false) { return -2; }

	size_t low = 0;         // ������ �������, ��������� �������� = 0
	size_t high = size - 1; // ������� �������, ��������� �������� = ����������� �������

	while (low <= high && key >= arr[low] && key <= arr[high]) // ���� �� ������ ������ ������ key
	{
		if (low == high) // ���� � ������� 1 �������
		{
			if (arr[low] == key) return low; // ���� ���� ������� ���� key, ��������� ��� ������
			return -1;	// ���� ��� �� -1, ��� ������ key �� ������
		}
		// ������� ������������ ��� ����������� ��������������� ��������� �������� ��������
		size_t pos = low + ((key - arr[low]) * (high - low) / (arr[high] - arr[low]));
		if (arr[pos] == key) return pos; // ���� ������� pos �������� � ���� key, �� ��������� pos
		if (arr[pos] < key) low = pos + 1; // ���� ������� pos �������� ������, ����� ����������� ������ ������� �� pos
		else high = pos - 1; // ����� ����������� ������� ������� �� pos 
	}
	return -1; // �������� �� �������, ��������� -1
}

//---���� ������ ������� Poisk_interpolation
/// *** ��������� 3 ������
void Test_Search_interpolation()
{
	size_t sizemin = 5;
	// ��� �������� ������� TArray
	int* a = new int[sizemin] {1, 2, 3, 4, 5}; // ������������
	double* b = new double[sizemin] {1.11, 2.22, 3.33, 4.44, 5.55}; // ������������
	int* c = new int[sizemin] {5, 3, 2, 1, 4}; // �� ������������

	long long test1 = Search_interpolation(a, sizemin, 5);
	assert(test1 == 4); // ����� �������� � ����� �������
	long long test2 = Search_interpolation(b, sizemin, 1.11);
	assert(test2 == 0); // ����� �������� � ������ �������
	long long test3 = Search_interpolation(c, sizemin, 2);
	assert(test3 == -2); // ������ �� ������������
	/// *** ��������� �����
	long long test4 = Search_interpolation(b, sizemin, 6.66);
	assert(test4 == -1); // *** ���� ������� �����������
	long long test5 = Search_interpolation(a, sizemin, 3);
	assert(test5 == 2); // *** ����� �������� �� ��������
	long long test6 = Search_interpolation(b, sizemin, 4.44);
	assert(test6 == 3); // *** ����� �������� �� �� ��������, �� � ������, �� � �����

	delete[] a;
	delete[] b;
	delete[] c;
	cout << "--- Test_Search_interpolation() �������� ������� ----" << endl;
}