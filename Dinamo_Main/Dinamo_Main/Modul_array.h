/// \file Modul_array.h
/// \brief ������ � ���������
/// \author ���������� ������� ���-22
/// \date 29.03.2024

#pragma once
#include <cstdlib>   // ������ � ������� memcpy
#include <string>    // ��� ������������� �����
#include <iomanip>   // ��� setw setprecision
#include <cassert>   // ��� assert
#include <iostream>  // ��������� cin cout
#include <ctime>     // ����� ��� ��������� ��������� �������
#include <fstream>   // ��� ������ � �������
#include <exception> // ��������� ����������
#include <locale>    // ��������� ������� setlocale ��� ������� ������ 
#include "Array.h" 
using namespace std; // ������������� ���� std::

// ������ ��� �������
template <typename Type>
class DinamoArray
{
private:   // ��������� ���� ������ DinamoArray
    Type* arr; // ��������� �� ������ ������� ��� ��������� typename Type
    size_t indexLastArr; // ������ ��������� ��������� ������
    size_t size;     // ������ ������� arr
public:

    // ����������� ��� ����������, �������� ������
    DinamoArray()
    {
        size = 0; indexLastArr = 0; arr = nullptr;
    } // nullptr � �������� ��������� �������� ���������


    // ����������� � �����������
    DinamoArray(size_t _size, const Type& value = 0)
    {
        if (_size > 0)
        {
            size = _size;
            // ������ �������� indexLastArr
            indexLastArr = _size; // ������ ����� ���������� �������� _size ����������� ������� arr ///*** 
            arr = new Type[size];
            // ������ ��� ������ arr
            for (size_t i = 0; i < size; i++)
            {
                arr[i] = value; // value = 0
            }

        }
        else
            throw invalid_argument("������������ �������� ������� " + to_string(_size));
    }

    ///*** ������� ���� 
/*
1. ����������.
2. ����������� �����������.
3. �������� ������������ ������������.
4. ����������� �����������.
5. �������� ������������ ������������.
*/

//  1. ����������
    ~DinamoArray() {
        if (arr = nullptr)
        {
            delete arr;
        }
        else
        {
            delete[] arr;
        }
    }

    // 2. ����������� �����������
    DinamoArray(const DinamoArray& other) : arr(new Type(*other.arr)), indexLastArr(new size_t(other.indexLastArr)), size(new size_t(other.size)) {}

    // 3. �������� ������������ ������������  ///*** 
    DinamoArray& operator=(const DinamoArray<Type>& other) {
        if (this != &other) {
            *arr = *other.arr; // �������� �������� arr � � ��� ����������� ��� �� 
            indexLastArr = other.indexLastArr;
            size = other.size;
        }
        return *this;
    }

    // 4. ����������� �����������
    DinamoArray(DinamoArray&& other) noexcept : arr(other.arr), indexLastArr(other.indexLastArr), size(other.size) {
        other.arr = nullptr;
        other.indexLastArr = nullptr;
        other.size = nullptr;
    }

    // 5. �������� ������������ ������������
    DinamoArray& operator=(DinamoArray&& other) noexcept {
        if (this != &other) {
            delete arr;
            arr = other.arr;
            other.arr = nullptr;
            delete indexLastArr;
            indexLastArr = other.indexLastArr;
            other.indexLastArr = nullptr;
            delete size;
            size = other.size;
            other.size = nullptr;
        }
        return *this;
    }

    //***
    // ���������� ��������� [] ��� ������� � ������������ ��������� �������
    // �������: O(1)
    Type& operator[](size_t index)
    {
        if (index < size)
        {
            return arr[index];
        }
        else
            // ����������, ���� �� index < size
            throw invalid_argument("������������ �������� �������");
    }
    
    // ��������� �������� ����������� ������� � ������� ������� � �������
    // new_size ����� ����������� �������, (-/+) size
    /// �������: O(n)
    void Resized(size_t new_size)
    {
        Type* new_arr = new Type[new_size]; // �������� ������ �� ����� ������
        // ����������� ��������� �� ������� ������� � �����
        size_t elementsToCopy = min(new_size, size);
        //size_t elementsToCopy = new_size;
        copy(arr, arr + elementsToCopy, new_arr);
        delete[] arr; // ������������ ������ ������� �������
        arr = new_arr; // ���������� ����� �������� � ������
        //indexLastArr = new_size;
        size = new_size; ///---*** ������ � �� ������ ������ ����������
    }
        
    // ������� ����� �������
    // return ���������� ������ ������� ���� size_t
    /// �������: O(1)
    size_t lenght() const
    {
        return indexLastArr;
    }
    
    // ��������� ��������� ������� � ������ � �����
    // new_element �������, ������� ����� �������� � ����� �������
    /// �������: �(1) | ������: O(n)
    void Add_Back(Type new_element)
    {
        if (indexLastArr < size)
        {
            arr[indexLastArr] = new_element;
            indexLastArr++;
        }
        else
        {
            Resized(indexLastArr);
            arr[indexLastArr] = new_element;
            indexLastArr = indexLastArr + 1;
        }
    }
    
    // ��������� ��������� ������� � ������ � ������
    // new_element �������, ������� ����� �������� � ������ �������
    /// �������: �(n)
    void Add_Front(Type new_element)
    {
        // ���� ���� ����� ������, ����� ���� ��������� ����������� ������� �������
        if (indexLastArr < size)
        {
            // �������� ��� �������� "������" � ����������� �����
            copy(arr, arr + size - 1, arr + 1);
            arr[0] = new_element; // ��������� ����� ������� � ������
            size++; // ����������� ����������� �� 1
            indexLastArr++; // ����������� �������� ���������� ������� �� 1
        }
        // ����� ���� ��������� ����������� ������� �������
        else
        {
            Resized(indexLastArr);
            // �������� ��� �������� "������"
            copy(arr, arr + size - 1, arr + 1);
            arr[0] = new_element; // ��������� ����� ������� � ������
            size++; // ����������� ����������� �� 1
            indexLastArr++; // ����������� �������� ���������� ������� �� 1        }
        }
    }

    // ��������� ������� ��������� ������� �������
    /// �������: O(1)
    void Delete_Last()
    {
        if (indexLastArr >= 0) // ������, ���� �� �����
        {
            copy(arr, arr - indexLastArr, arr);
            indexLastArr -= 1; // ��������� �������� ���������� ������� �� 1 
        }
        else
        {
            throw invalid_argument("���� ������ ��� ����!");
        }
    }

    // ��������� ������� ������ ������� �������
    /// �������: O(n)
    void Delete_Firts()
    {
        if (indexLastArr >= 0) // ������, ���� �� �����
        {
            copy(arr + 1, arr + indexLastArr, arr);
            indexLastArr -= 1; // ��������� �������� ���������� ������� �� 1
        }
        else // ���� ������ ������
        {
            throw invalid_argument("���� ������ ��� ����!");
        }
    }
    
    // ��������� ���� ������� findThis � ������� � ������� Sequatial_search
    // findThis �������, ������� ����
    // ��������� ������ ���������� �������� ��� -1, ���� �� �����
    /// �������: O(n)
    long long Search(Type findThis) const
    {
        return sequential_search(arr, indexLastArr, findThis);
    }

    // ��������� ���������� ������� ������� Merge_sort
    /// �������: O(n log n)
    void Sort()
    {
        // ����������
        merge_sort(arr, 0, indexLastArr - 1);
    }
    
    // ���������� ��������� ������������� �� �������� �����������
    /// O(n)
    /*DinamoArray&
        operator=(const DinamoArray<Type>& other)
    {
        if (this != &other)
        {
            if (arr != nullptr)
                delete[] arr; // ������������ ������
            // �����������
            size = other.size;
            indexLastArr = other.indexLastArr;
            arr = new Type[indexLastArr];
            memcpy(arr, other.arr, other.size * sizeof(Type));
        }
        return *this;
    }*/
   
    // ���������� �������
    /*~DinamoArray()
    {
        if (arr = nullptr)
        { delete arr; }
        else
        { delete[] arr; }
    }*/
};

// ���� Add_Back � Add_Front
void testAdd()
{
    DinamoArray<int> arr(2); // ������ �� ���� ��������� = 2
    arr.Add_Back(321);       // + ���� � ������ = 3
    arr.Add_Front(123);      // + ���� � ������ = 4
    arr.Add_Back(654);       // + ��� ���� � ������ = 5
    assert(arr.lenght() == 5);

    assert(arr[0] == 123);
    assert(arr[3] == 321);
    assert(arr[4] == 654);
    cout << "================================================";
    cout << "���� Add_Back � Add_Front �������� �������" << endl;
}

// ���� Resized ��������� ����������� �������
void testResized()
{
    DinamoArray<int> arr(3);
    arr.Resized(6); // ������ ����������� 3 �� 6
    assert(arr.lenght() == 6);

    arr[0] = 123;
    arr[1] = 321;
    // �������� ��������� ������� �� ������� ��������
    arr.Resized(2); // ������ ����������� 6 �� 2
    assert(arr.lenght() == 2);
    assert(arr[0] == 123); // ��������, ��� ������ ������� �� ���������
    assert(arr[1] == 321); // ��������, ��� ������ ������� �� ���������
    cout << "================================================";
    cout << "���� Resize �������� �������" << endl;
}

// ���� Delete_Firts � Delete_Last
void testDelete()
{
    DinamoArray<int> arr(3);
    arr.Delete_Last();
    assert(arr.lenght() == 2);
    arr.Delete_Firts(); 
    assert(arr.lenght() == 1);
    cout << "================================================";
    cout << "���� Delete_Firts � Delete_Last �������� �������" << endl;
}

// ���� Search
void testSearch()
{
    DinamoArray<int> arr(5); // ��� Int
    for (int i = 0; i < 5; i++)
    {
        arr[i] = i;
    }
    assert(arr.Search(3) == 3);  // �������� ����� �������� � �������
    assert(arr.Search(6) == -1); // ��� �������� ���������� -1

    DinamoArray<double> arrD(5); // ��� Double
    for (size_t i = 0; i < 5; i++)
    { arrD[i] = i * 1.1; }
    assert(arrD.Search(1.1) == 1); // �������� ����� �������� � ������� [1]

    // �������� ������, ����� ������� ��������� � �������� �������
    DinamoArray<int> middle(5); // ��� Int
    middle[0] = 1; middle[1] = 2; middle[2] = 3; middle[3] = 4; middle[4] = 5;
    assert(middle.Search(3) == 2); // �������� ����� �������� � �������� �������

    // �������� ������, ����� ������� ��������� �� ������� �������
    DinamoArray<int> border(5); // ��� Int
    border[0] = 1; border[1] = 2; border[2] = 3; border[3] = 4; border[4] = 5;
    assert(border.Search(5) == 4); // �������� ����� �������� �� ������� �������
    cout << "================================================";
    cout << "���� Search �������� �������" << endl;
}

// ���� Sort
void testSort()
{
    DinamoArray<int> arr(5);
    arr[0] = 1; arr[1] = 4; arr[2] = 2; arr[3] = 3; arr[4] = 5;
    arr.Sort();
    assert(arr[0] == 1);
    assert(arr[1] == 2);
    assert(arr[2] == 3);
    assert(arr[3] == 4);
    assert(arr[4] == 5);
    // �������� ��� ���������� ������� � ����� ���������
    DinamoArray<int> arrOne(1);
    arrOne[0] = 1000;
    arrOne.Sort();
    assert(arrOne[0] == 1000);
    // �������� ��� ���������� �������, ��� ��� �������� �����
    DinamoArray<int> arrEqual(3);
    arrEqual[0] = 2;
    arrEqual[1] = 2;
    arrEqual[2] = 2;
    arrEqual.Sort();
    assert(arrEqual[0] == 2);
    assert(arrEqual[1] == 2);
    assert(arrEqual[2] == 2);
    cout << "================================================";
    cout << "���� Sort �������� �������" << endl;
    cout << endl;
}

