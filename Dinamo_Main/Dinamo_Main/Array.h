/// \file Array.h
/// \brief ������ � ���������
/// \author ���������� ������� ���-22
/// \date 29.03.2024

#include <string>
#include <iomanip>
#include <cassert>
#include <cstddef>
#include <type_traits>

using namespace std; // ������������� ����

/// ���������������� ����� �� �������, ���� key ����� ������, �� �������� ��� ������, ���� �� ���, �� �������� ����� -1
template <typename Array>
long long sequential_search(const Array arr[], long long size, Array key)
{
	for (long long i = 0; i < size; ++i)
		if (arr[i] == key)
			return i; // �������� �������, ���������� ������
	return -1;		  // �������� �� �������, ��������� -1
}

/// ������� ������� ���� ��������������� ����������� �� merge_sort
template <typename Array>
void merge_mas(Array* arr, size_t left, size_t mid, size_t right)
{
	// ���������� �������� ���� �����������  - ������ � �������, � �� ����� ������� ��?
	size_t leftSize = mid - left + 1;
	size_t rightSize = right - mid;

	// ��� ������ ��� �������
	Array* LeftArr = new Array[leftSize];
	Array* RightArr = new Array[rightSize];

	// �������� �������� ������ ���������� �� ��������� �����
	// memcpy(����, ������, ������ � ������)
	memcpy(LeftArr, &arr[left], sizeof(Array) * leftSize);

	// �������� �������� ������� ���������� �� ��������� ������
	memcpy(RightArr, &arr[mid + 1], sizeof(Array) * rightSize);

	// ��������� ������� ����������� ��� �� �����������, ��� � ����� while ��� �������
	size_t i = 0;
	size_t j = 0;
	size_t k = left;

	// ������� ���� ����������� � �������� ������ arr
	while (i < leftSize && j < rightSize)
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
	if (i < leftSize)
	{
		memcpy(&arr[k], &LeftArr[i], (leftSize - i) * sizeof(Array)); // ���������� ���������� ��������� �� ������ ����������
		k += leftSize - i;
	}

	// ���������� ���������� ��������� �� ������� ����������
	if (j < rightSize)
	{
		memcpy(&arr[k], &RightArr[j], (rightSize - j) * sizeof(Array)); // ���������� ���������� ��������� �� ������� ����������
		k += rightSize - j;
	}

	delete[] LeftArr, RightArr;
}

/// ������� ���������� ������� ������� merge (�������) �� ������� - �� �������� � ��������
/// arr - ��� ������, left - ��������� �� ����� ������� ������� (��� ������� ������ �������� 0),
/// right - ��������� �� ������ ������� ������� (��� ������� ������ �������� n - ��������� �������� �������)
/// Big O::
/// ������ ������: ����� ������ ��� ������������ ��� ����� ������������, ���������� �������� ��� ����� ����������� �� O(n log n) ��������
/// ������ ������: ��� ���������� �������� ������ ������ ����� ���������� O(n log n)
/// ������� ������: ������� ��������� ���������� �������� ����� ���������� O(n log n)
template <typename Array>
void merge_sort(Array& arr, size_t left, size_t right)
{
	// ���� ������ ����� �� �������� ������� 1, �� ������
	if (left < right)
	{
		// ��������� ���������
		size_t mid = left + (right - left) / 2;

		// � ��� �� �������� ��������, ����� ������ ������ ��� ����������� ����� � ������ ����� ������� �� 0 �� �������� � �� �������� �� �����
		merge_sort(arr, left, mid);
		merge_sort(arr, mid + 1, right);

		// ��� �������� �������, ������� ���������� ������� ���� ��������������� ��������
		merge_mas(arr, left, mid, right);
	}
}