#pragma once
/// \file Spisok_one.h
/// \brief ������ � ����������� �������
/// \author ���������� ������� ���-22
/// \date 29.03.2024

#include <iostream> //��������� cin cout
#include <sstream>  //��������� ������ �� �������� ����� ������
#include <cassert>  //��� assert
#include <locale>   //���������� ������� setlocale ��� ��������� ������� ������

using namespace std;

// ������ ��� ������ 
template <typename Type>
class OneList // ����������� ������
{
public: // ��������� ���� ������ OneList
    Type data; // ������ ������
    OneList<Type>* prev; // ��������� �� ���������� ���� � ������
    OneList<Type>* next; // ��������� �� ��������� ���� � ������

    // ����������� �� ���������
    OneList() : prev(nullptr), next(nullptr), data(Type()) {}

    // ����������� � ������� � ������ �����������
    /// @param data_ - ������ ����
    /// @param prev_ - ��������� �� ���������� ����
    /// @param next_ - ��������� �� ��������� ����
    OneList(const Type& data_, OneList<Type>* prev_, OneList<Type>* next_) : data(data_), prev(prev_), next(next_) {}

    /// @brief ����������� ������ � �������, ��������� prev � next ������� � null
    /// @param data_ - ������ ����
    OneList(const Type& data_) : data(data_), prev(nullptr), next(nullptr) {}

    /// @brief ����������� �����������
    OneList(const OneList<Type>& other)
        : data(other.data), prev(nullptr), next(nullptr) // ���� ��� nullptr
    {
        if (other.prev != nullptr)
        {   // ������ ����� ���������, ��� �����������
            prev = new OneList(other.prev->data);
        }
        if (other.next != nullptr)
        {   // ������ ����� ���������, ��� �����������
            next = new OneList(other.next->data);
        }
    }

    /// @brief ����������� �����������
/// @param other ��, ��� ����������
    OneList(OneList<Type>&& other)
        : data(other.data), prev(other.prev), next(other.next) // ���������� ��������� �� ���� � ����
    {
        // ������ 
        other.prev = nullptr;
        other.next = nullptr;
    }

    /// @brief �������� �����������
    /// @param other ��, ��� ��������
    OneList<Type>& operator=(const OneList<Type>& other)
    {
        if (this != &other) // �������� �� ����������������
        {
            delete prev;
            delete next;

            // ��������
            data = other.data;
            if (other.prev != nullptr)
            {
                // ������ ����� ���������, ��� �����������
                prev = new OneList(other.prev->data);
            }
            if (other.next != nullptr)
            {
                // ������ ����� ���������, ��� �����������
                next = new OneList(other.next->data);
            }
        }
        return *this;
    }

    /// @brief �������� �����������
    OneList<Type>& operator=(OneList<Type>&& other)
    {
        if (this != &other) // �������� �� ����������������
        {
            data = other.data;
            prev = other.prev;
            next = other.next;

            other.prev = nullptr;
            other.next = nullptr;
        }
        return *this;
    }

    /// @brief ����������
    ~OneList()
    {
        /// ������� ��������� �� ���������� � ��������� ����
        if (prev != nullptr && next != nullptr)
        {
            prev = nullptr;
            next = nullptr;
        }
    }
};
