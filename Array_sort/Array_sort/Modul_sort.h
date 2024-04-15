/// \file Modul_sort.h
/// \brief ������ � ����������� � �������
/// \author ���������� ������� ���-22
/// \date 18.02.2024
#pragma once
#include "Modul_array.h" // ����� ������������� ����� Modul_array

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

//---���������� ������� ��������� �� ������� - �� �������� � ��������
/// �.�.���� ���������, �� ��� BigO(n^2)
/// ������  � O(n2), ������� � O(n2), ������  � O(n), ����� 147
/// \param a ������, ��� TArray
/// \param size ������ �������
/// \return ������, ������ ��������� ������ a
template <typename TArray>
void Sorting_bubbles(TArray* a, size_t size)
{
	TArray temporary;	  // temporary - ��������� ��������
	for (size_t i = 0; i < size - 1; i++) // ���� ���� O(n)
	{
		for (size_t j = 0; j < size - i - 1; j++) // ������ ���� O(n*n)
		{
			if (a[j] > a[j + 1]) // ���� ���� > ����
			{
				temporary = a[j]; // ������ �������� �������
				a[j] = a[j + 1];
				a[j + 1] = temporary;
			}
		}
	}
}

//---���� ������ ������� Sorting_bubbles
void Test_Sorting_bubbles()
{
	size_t sizemin = 6;

	int* a = new int[sizemin] {6, 2, 3, 4, 5, 1}; // ��������������� Int
	double* b = new double[sizemin] {1.11, 2.22, 3.33, 4.44, 5.55, 6.66}; // ������������� double
	int* c = new int[sizemin] {5, 3, 1, 5, 3, 1}; // ��������������� Int
	int* d = new int[sizemin] {6, 5, 4, 3, 2, 1}; // ������������� Int � �������� �������

	int* a_result = new int[sizemin] {1, 2, 3, 4, 5, 6}; // ��������� ���������� ������� a
	double* b_result = new double[sizemin] {1.11, 2.22, 3.33, 4.44, 5.55, 6.66}; // ��������� ���������� ������� b
	int* c_result = new int[sizemin] {1, 1, 3, 3, 5, 5}; // ��������� ���������� ������� c
	int* d_result = new int[sizemin] {6, 5, 4, 3, 2, 1}; // ��������� ���������� ������� d

	// ������������ ���������� ����������
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
	cout << "--- Test_Sorting_bubbles() �������� ������� ---------" << endl;
}

//---���������� ������� �������� ���� ��������������� ����������� ��� Sorting_merge
/// \param a ������, ��� TArray
/// \param ��������� ������ �� �������� middle �� ��� �����
/// \param left ������ ����������� ����� �� middle
/// \param right ������ ����������� ������ �� middle
/// \return ������, ������ ��������� ������ a
template <typename TArray>
void Merge(TArray* arr, size_t left, size_t mid, size_t right) // Merge - ������� ///*** int �������� �� size_t
{
	// ���������� �������� ���� ����������� 
	size_t LSize = mid - left + 1;
	size_t RSize = right - mid;
	// ��������� ���������� ��� �������
	TArray* LeftArr = new TArray[LSize];
	TArray* RightArr = new TArray[RSize];
	// �������� �������� ������ ���������� �� ��������� �����
	// memcpy(����, ������, ������ � ������) // ������ ���� ������ TArray
	memcpy(LeftArr, &arr[left], sizeof(TArray) * LSize);
	// �������� �������� ������� ���������� �� ��������� ������
	memcpy(RightArr, &arr[mid + 1], sizeof(TArray) * RSize);
	// ��������� ������� ����������� ��� �� �����������, ��� � ����� while ��� �������
	size_t i = 0; size_t j = 0; size_t k = left;
	// ������� ���� ����������� � �������� ������ arr
	while (i < LSize && j < RSize)
	{
		if (LeftArr[i] <= RightArr[j])
		{
			arr[k] = LeftArr[i];
			i++;
		}
		else
		{
			arr[k] = RightArr[j];
			j++;
		}
		k++;
	}
	// ���������� ���������� ��������� �� ������ ����������
	if (i < LSize)
	{
		memcpy(&arr[k], &LeftArr[i], (LSize - i) * sizeof(TArray)); // ���������� ���������� ��������� �� ������ ����������
		k += LSize - i;
	}
	// ���������� ���������� ��������� �� ������� ����������
	if (j < RSize)
	{
		memcpy(&arr[k], &RightArr[j], (RSize - j) * sizeof(TArray)); // ���������� ���������� ��������� �� ������� ����������
		k += RSize - j;
	}
	delete[] LeftArr, RightArr;
};

//---���������� �������� �� ����������� (�����������)
// BigO(n*logn)-������ ������, Big0(n*logn) - ������� ������,
// BigO(n*logn)-������ ������  ����� 118
/// \param a ������, ��� TArray
/// \param first ������ ��������, � �������� ���������� ����������
/// \param last ������ ��������, �� ������� ������������� ����������
/// \return ������ ��������� ������� 
/// ������ ������: ����� ������ ��� ������������, ���������� �������� ��� ����� ����������� �� O(n log n) ��������
/// ������ ������: ��� ���������� �������� ������ ������ ����� ���������� O(n log n)
/// ������� ������: ������� ��������� ���������� �������� ����� ���������� O(n log n)
template <typename TArray>
void Sorting_merge(TArray* a, size_t left, size_t right)
{
	if (left < right)
	{
		// ��������� mid
		size_t mid = left + (right - left) / 2;
		Sorting_merge(a, left, mid); //���������� ����� �����
		Sorting_merge(a, mid + 1, right); //���������� ������ �����
		Merge(a, left, mid, right); //������� ���� ������
	}
};

//---���� ������ ������� Sorting_merge
void Test_Sorting_merge()
{
	size_t sizemin = 6;

	int* a = new int[sizemin] {6, 2, 3, 4, 5, 1}; // ��������������� Int
	double* b = new double[sizemin] {1.11, 2.22, 3.33, 4.44, 5.55, 6.66}; // ������������� double
	int* c = new int[sizemin] {5, 3, 1, 5, 3, 1}; // ��������������� Int
	int* d = new int[sizemin] {6, 5, 4, 3, 2, 1}; // ������������� Int � �������� �������

	int* a_result = new int[sizemin] {1, 2, 3, 4, 5, 6}; // ��������� ���������� ������� a
	double* b_result = new double[sizemin] {1.11, 2.22, 3.33, 4.44, 5.55, 6.66}; // ��������� ���������� ������� b
	int* c_result = new int[sizemin] {1, 1, 3, 3, 5, 5}; // ��������� ���������� ������� c
	int* d_result = new int[sizemin] {6, 5, 4, 3, 2, 1}; // ��������� ���������� ������� d

	// ������������ ���������� ����������
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
	cout << "--- Test_Sorting_merge() �������� ������� ---------" << endl;
}

//---������� ��� ����������� �������� �������� � ������� 
/// \param a ������, ��� TArray
/// \param left - ��������� �� ����� ������� ������� (��� ������� ������ �������� 0)
/// \param right - ��������� �� ������ ������� ������� (n - ��������� �������� �������)
/// \return ������ ��������� ������� 
/// element ���������� ��������
template <typename TArray>
size_t Search_element(TArray* a, size_t left, size_t right)
{
	size_t Elem_rand = rand() % right;  //**** ��������� ������
	TArray element = a[Elem_rand];
	// �������� ��������� ������� � �������� �������� ///*** ��������� ��

	size_t i = (left - 1); 			// ������������� ������� ������� ���������

	for (size_t j = left; j <= right - 1; j++) {
		if (a[j] < element) {
			i++; 				// ����������� ������ ������� ���������
			swap(a[i], a[j]);   // ������ �������� �������
		}
	}
	swap(a[i + 1], a[right]); 	// ������ ������� ������� � ��������� � ������� i + 1
	return (i + 1); 			// ���������� ������ �������� ��������
}

//---����������� ������� ��� ���������� �������
/// Big O:: ������ ������: O(n2)
/// ������� ������: O(n log n), ������ ������: O(n)
/// \param a ������, ��� TArray
/// \param left - ��������� �� ����� ������� ������� (��� ������� ������ �������� 0)
/// \param right - ��������� �� ������ ������� ������� (n - ��������� �������� �������)
/// \return ������ ��������� ������� 
template <typename TArray>
void Sorting_quick(TArray* a, size_t left, size_t right) {
	if (left < right) {
		size_t element = Search_element(a, left, right);// ������� ������� �������
		if (element > 0) {
			Sorting_quick(a, left, element - 1); 		// ���������� ��������� �������� ����� �������
		}
		Sorting_quick(a, element + 1, right); 			// ���������� ��������� �������� ����� ��������
	}
}

//---���� ������ ������� Sorting_quick ///****�������� ������� �������, ���� ����� ����� ���� ������ ���������� ���������
void Test_Sorting_quick()
{
	size_t sizemin = 6;

	int* a = new int[sizemin] {6, 2, 3, 4, 5, 1};
	double* b = new double[sizemin] {1.04, 1.05, 1.03, 1.01, 1.02, 1.06};
	int* c = new int[9] {5, 3, 2, 5, 3, 2, 5, 9, 8};
	int* d = new int[7] {6, 5, 4, 3, 4, 5, 1};

	int* a_result = new int[sizemin] {1, 2, 3, 4, 5, 6};
	double* b_result = new double[sizemin] {1.01, 1.02, 1.03, 1.04, 1.05, 1.06};
	int* c_result = new int[sizemin] {2, 2, 3, 3, 5, 5};
	int* d_result = new int[sizemin] {6, 5, 4, 3, 2, 1};

	Sorting_quick(a, 0, 5);
	Sorting_quick(b, 0, 5);
	Sorting_quick(c, 0, 9);
	Sorting_quick(d, 0, 7);
	for (size_t i = 0; i > sizemin; i++)
	{
		assert(a[i] == a_result[i]);
		assert(b[i] == b_result[i]);
		assert(c[i] == c_result[i]);
		assert(d[i] == d_result[i]);
	}

	delete[] a, b, c;
	delete[] a_result, b_result, c_result, d_result;
	cout << "--- Test_Sorting_quick() �������� ������� ---------" << endl;
}
///*** Big_O ����� � � ���������� � � ������

//---���� ������ ������� Sorting_Shell
/// ��� ���������� size/2 � ����� ����������� ������ ��� � ��� ����
/// Big O::  ������ ������: O(n^2)
/// ������ ������: O(n log n), ������� ������: O(n^(3/2))
template <typename Array>
void Sorting_Shell(Array arr[], size_t size)
{
	// ������ � �������� step ����, ��� ����������� � ������ ����� �� ���
	for (size_t step = size / 2; step > 0; step /= 2)
	{
		// ������� �������� �� �������, ������� � �������� �� ���������� stepik �� ������
		for (size_t i = step; i < size; i++)
		{
			Array temp = arr[i];
			size_t j;
			// ��������� ���������� � ����� stepik, ��������� � ����� ��
			for (j = i; j >= step && arr[j - step] > temp; j -= step)
			{
				arr[j] = arr[j - step];
			}
			arr[j] = temp;
		}
	}
}

/// ������� ������������ ��� ������� Sorting_Shell
void Test_Sorting_Shell()
{
	long long sizeSmall = 6;

	// a - �������, b - ������, c - � ������������, d - ��������

	int* a = new int[sizeSmall] {6, 2, 3, 4, 5, 1};
	double* b = new double[8] {1.01, 1.02, 1.03, 1.04, 1.05, 1.06, 1.07, 1.08};
	int* c = new int[7] {5, 3, 2, 5, 3, 2, 8};
	int* d = new int[sizeSmall] {6, 5, 4, 3, 2, 1};

	int* a_ = new int[9] {1, 2, 3, 4, 5, 6, 7, 8, 9};
	double* b_ = new double[sizeSmall] {1.01, 1.02, 1.03, 1.04, 1.05, 1.06};
	int* c_ = new int[sizeSmall] {2, 2, 3, 3, 5, 5};
	int* d_ = new int[sizeSmall] {6, 5, 4, 3, 2, 1};

	// ����������, �� ��������
	Sorting_Shell(a, sizeSmall);
	Sorting_Shell(b, sizeSmall);
	Sorting_Shell(c, sizeSmall);
	Sorting_Shell(d, sizeSmall);
	for (int i = 0; i > sizeSmall; i++)
	{
		assert(a[i] == a_[i]);
		assert(b[i] == b_[i]);
		assert(c[i] == c_[i]);
		assert(d[i] == d_[i]);
	}

	delete[] a, b, c;
	delete[] a_, b_, c_;
	cout << "--- Test_Sorting_Shell() �������� ������� ---------" << endl;
}