#pragma once
/// \file Spisok_class.h
/// \brief ������ � ���������� �������
/// \author ���������� ������� ���-22
/// \date 29.03.2024

#include "Spisok_one.h"

/// @brief ����� DoublyList ���� ���������� ������
/// @tparam Type ��� ������ ����������� ������
template <typename Type>
class DoublyList
{
private:
    OneList<Type>* head; // ��������� �� ������ ������
    OneList<Type>* tail; // ��������� �� ����� ������
    size_t size; // ������ ������

public:
    /// @brief ����������� �� ���������
    DoublyList()
    {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }
    /// @brief ������� � ��������� ������ ���������� value
    /// @param n ������ ������
    /// @param value ��, ��� ����������� ������
    DoublyList(size_t n, const Type& value)
    {
        for (size_t i = 0; i < n; i++)
        {
            AddBack(value);
        }
    }

    /// @brief ����������� �����������
    /// @param other, ��� ��������
    DoublyList(const DoublyList& other)
    {
        head = nullptr;
        tail = nullptr;
        size = 0;
        // �������� �������� �� ������� ������
        copy(other);
    }

    /// @brief ����������� �����������
    /// @param other, ��� ���������
    DoublyList(DoublyList&& other)
    {
        // ���������� �������� �� ������� ������.
        head = other.head;
        tail = other.tail;
        size = other.size;
        other.Forget();
    }

    /// @brief �������� ������������, �� ��������
    /// @param other ��� ��������
    /// @return �������������
    DoublyList& operator=(const DoublyList& other)
    {
        if (this == &other)
        {
            return *this;
        }
        clearSpisok(); // ������� ������� ������
        copy(other);   // �������� �������� �� ������� ������
        return *this;
    }

    /// @brief �������� ������������, �� ����������
    /// @param other ��� ����������
    /// @return ������������
    DoublyList& operator=(DoublyList&& other)
    {
        if (this == &other)
        {
            return *this;
        }
        clearSpisok(); // ������� ������� ������
        // ���������� �������� �� ������� ������.
        head = other.head;
        tail = other.tail;
        size = other.size;
        other.Forget();
        return *this;
    }

    /// @brief ����������
    ~DoublyList()
    {
        clearSpisok();
    }

    /// @brief �������� ����������� ������
    /// @param other, ��� ��������
    void copy(const DoublyList<Type>& other)
    {
        clearSpisok();
        // ������������ ����
        OneList<Type>* current = other.head;
        while (current != nullptr)
        {
            AddBack(current->data);
            current = current->next;
        }
    }

    /// @brief ���������� ������ ������
    /// @return ������ ������
    size_t length() const
    {
        return size;
    }

    /// @brief ������� ������ � ������
    /// @return ������ � ������� ����
    string to_string() const
    {
        // ������� ��������� �����, ��� ������ ������
        stringstream spisok_stroka;
        spisok_stroka << "begin ";

        // �������� ���� � ������ ������
        OneList<Type>* current = head;
        // ���� ������ �� �����
        while (current != nullptr)
        {
            // ����� ����������
            spisok_stroka << current->data;
            // ����� �����������
            if (current->next != nullptr)
            {
                spisok_stroka << " ";
            }
            current = current->next;
        }
        spisok_stroka << " end";
        // ����������� ����� ���� � ������
        return spisok_stroka.str();
    }

    /// @return ���� ������ OneList
    OneList<Type>* get_OneList(size_t place)
    {
        if (place < 0 || place >= size)
        {
            throw out_of_range("�������� ������");
        }
        OneList<Type>* current = head;
        for (size_t i = 0; i < place; i++)
        {
            current = current->next;
        }
        return current;
    }

    /// @brief ���������� ������ �� ����������� ���������
    void sort()
    {
        if (size <= 1) { return; }
        //������ ��� ���� ��� ���������
        OneList<Type>* current = head;
        OneList<Type>* nextNode = nullptr;
        while (current != nullptr)
        {
            nextNode = current->next;
            while (nextNode != nullptr)
            {
                // ��������� �������� �������� � ��������� ���������
                if (current->data > nextNode->data)
                {
                    // ����� ���������� �������� � ���������� ���������
                    swap(current->data, nextNode->data);
                }
                // ��������� � ���� ����
                nextNode = nextNode->next;
            }
            // ����� ��������� � ���� ����
            current = current->next;
        }
    }

    /// @brief ������� ���� � ��������� value
    /// @param value 
    /// @return ��������� ���� �� ��������� value
    OneList<Type>* find(Type value)
    {
        OneList<Type>* current = head;
        while (current != nullptr)
        {
            if (current->data == value)
            {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    /// @brief ������ ������
    void clearSpisok()
    {
        // ������� ��� ���� �� ������
        while (head != nullptr)
        {
            OneList<Type>* nextNode = head->next;
            delete head;
            head = nextNode;
        }
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    /// @brief ������� �������� � ������
    /// @param value 
    void AddFront(Type value)
    {
        // ������� ����� ����
        OneList<Type>* newList = new OneList<Type>(value);
        // ���� ������ ������, �� ����� ���� ���������� ����� ������
        if (head == nullptr)
        {
            head = tail = newList;
        }
        // ����� ��������� ����� ���� � ������ ������
        else
        {
            newList->next = head; // � next ������ ������� head
            head->prev = newList; // � pred ������ ������� newList
            head = newList;       // ������������� ������
        }
        // ����������� ������ �� 1
        size++;
    }

    /// @brief ������� �������� � �����
    /// @param value ��, ��� ���������
    void AddBack(Type value)
    {
        // ������� ��, ��� ����� ���������
        OneList<Type>* newList = new OneList<Type>(value);
        // ���� ������ ������, �� ����� ���� ���������� ������� � �������
        if (tail == nullptr)
        {
            head = tail = newList;
        }
        else // ����� ��������� ��� � ����� ������
        {
            newList->prev = tail; // � ���������� ������ newList ������� ����� tail
            tail->next = newList; // � ��������� ������ ������� newList
            tail = newList;       // ����������� �����
        }
        // ����������� ������ �� 1
        size++;
    }

    /// @brief ������� ����� ����, ���������� value
    /// @param value ��, ��� �������� ����
    /// @param node ����� ���� �������� ����
    void AddInList(Type value, OneList<Type>* node)
    {
        // ���� ��������� ������ ����� nullptr, ������ ��� � ����� ������
        if (node == nullptr)
        {
            AddBack(value);
            return;
        }
        // ������� ����
        OneList<Type>* newList = new OneList<Type>(value);
        // ��������� ������ ����� ����������
        newList->next = node->next;
        if (node->next != nullptr)
        {
            node->next->prev = newList;
        }
        else { tail = newList; }
        node->next = newList;
        newList->prev = node;
        // ����������� ������ ������ �� 1
        size++;
    }

    /// @brief ������� ���� ������ � ��� ������
    void DelFront()
    {
        // ���� ������ ����, �� ������
        if (head == nullptr)
        {
            throw out_of_range("������ ����!");
            return;
        }
        // ���������� ���� temp ����������� ������ head
        OneList<Type>* temp = head;
        // ������ ������
        head = head->next;
        if (head != nullptr)
        {
            head->prev = nullptr;
        }
        else { tail = nullptr; }
        delete temp;
        // ��������� ������ �� 1
        size--;
    }

    /// @brief ������� ���� node �� ������ ������
    /// @param node ��, ��� ���� �������
    void DelInList(Type value)
    {
        if (head == nullptr)
        {
            throw out_of_range("������ ����!");
            return;
        }
        // ��������� ����
        OneList<Type>* temp = this->find(value);
        // ���� ��������� ���� ����
        if (temp != nullptr)
        {
            // �������, ���� ������, ������� ������
            if (temp == head)
            {
                this->DelFront();
            }
            // �������, ���� �����, ������� �����
            else if (temp == tail)
            {
                this->DelBack();
            }
            else
            {
                // ����� ������� ��������� ���� �� �������� ������
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
            }
        }
        else
        {
            throw invalid_argument("� ���� ������ ��� ����� ��������!");
        }
        // ���������
        size--;
    }

    /// @brief ������� ���� ������ � ��� �����
    void DelBack()
    {
        // ���� ������ ����, ������
        if (tail == nullptr)
        {
            throw out_of_range("������ ����!");
            return;
        }
        // ����� �������� ����������
        OneList<Type>* temp = tail;
        // ������ �����
        tail = tail->prev;
        if (tail != nullptr)
        {
            tail->next = nullptr;
        }
        else { head = nullptr; }
        delete temp;
        size--;
    }

    void ConcatenateLists(DoublyList<Type> other)
    {
        // ���������, �������� �� ������ "other" ������
        if (other.head == nullptr)
        {
            return;
        } // ���� ������ "other" ����, ������� �� �������
      // ���� ������� ������ ����, ����������� ��� �������� �� ������ "other"
        if (head == nullptr)
        {
            head = other.head;
            tail = other.tail;
        }
        else
        {
            // ���� ������� ������ �� ����, ��������� �������� �� "other" � ����� �������� ������
            tail->next = other.head; // ������������� ��������� �� ��������� ������� ���������� �������� �������� ������
            other.head->prev = tail; // ������������� ��������� �� ���������� ������� ������� �������� ������ "other"
            tail = other.tail;       // ��������� ��������� �� ����� �������� ������
        }
        size += other.size; // ����������� ������ �������� ������ �� ������ ������ "other"
        // �������� ��������� � ������ ������ "other" 
        other.head = nullptr;
        other.tail = nullptr;
        other.size = 0;
    }
};
