/// \file Deque.h
/// \brief ���� �������� ���������
/// \author ���������� ������� ���-22
/// \date 10.05.2024
/// ����� ����������� ��� ���.����������� ������� ���������� � ������ � � �����, 
/// �������� �� ������ � �� �����, �������� �� �� ������ �� ��� (isEmpty), 
/// ����������� �������(size), ����������� �������� �������� �� ������ � ����� ����,
/// ������� ���� (clear)
/// ���������� �� ������ ������ ���������� ������ DoublyList

#pragma once
#include "Queue.h"
#include "Spisok_one.h"    // ����������� ������ � �������� �������
#include "Spisok_class.h"  // ���������� ������ � �������� �������
#include <iostream>
#include <cassert>
#include <string>
using namespace std;

// ����� Deque ������������ �������, ����������� �� ������� �������
template <class Type>
class Deque : private Queue<Type>
{
public:
    // ���������� �������� � ������ �������
    // element ����������� �������
    void pushFront(Type element)
    {
        this->AddQueue(element);
    }

    /// @brief ���������� �������� � ����� ������� E
    /// @param element ����������� �������
    /// BigO: O(1)
    void pushBack(Type element)
    {
        this->AddBack(element);
    }

    /// @brief �������� �������� �� ����� ������� F
    /// @return �������� ���������� ��������, ��� �������� �� ��������� ��� Type, ���� ������� �����
    /// BigO: O(1)
    Type popBack()
    {
        if (this->isEmpty())
        {
            return Type(); // �������� �������� �� ��������� ��� Type
        }
        return this->DelQueue(); 
    }

    /// @brief �������� �������� �� ������ ������� E
    /// @return �������� ���������� ��������, ��� �������� �� ��������� ��� Type, ���� ������� �����
    /// BigO: O(1)
    Type popFront()
    {
        // ���� �����
        if (this->isEmpty())
        {
            return Type(); // �������� �������� �� ��������� ��� Type
        }

        Type val = this->get_OneList(0)->data;
        this->DelFront();
        return val;
    }

    /// @brief ��������� ����� �� �������
    /// @return �������� true||false
    /// BigO: O(1)
    bool isEmpty()
    {
        return this->Queue<Type>::isEmpty();
    }

    /// @brief ������ ������ �������
    /// @return size_t - ������
    size_t size() {
        return this->Queue<Type>::size();
    }

    /// @brief ������� �������
    /// BigO: O(n)
    void clear()
    {
        while (!this->isEmpty())
        {
            this->DelQueue();
        }
    }

    /// @brief ������ �������� ����� �������
    /// @return Type
    Type getBackData() {
        return this->getTailData();
    }

    /// @brief ������ �������� ������ �������
    /// @return Type
    Type getFrontData() {
        return this->getHeadData();
    }

    string to_string() const {
        return this->to_string();
    }
};

// ������������ ������ pushFront
void testPushFront() {
    Deque<int> queue1;
    //���������
    queue1.pushFront(1); assert(queue1.getBackData() == 1);
    queue1.pushFront(2); assert(queue1.getBackData() == 2);
    queue1.pushFront(3); assert(queue1.getBackData() == 3);
    assert(queue1.getFrontData() == 1);
    cout << "-- ������������ pushFront ��������� ������� -------" << endl;
}

// ������������ ������ pushBack
void testPushBack() {
    Deque<int> queue2;
    //���������
    queue2.pushBack(1); assert(queue2.getFrontData() == 1);
    queue2.pushBack(2); assert(queue2.getFrontData() == 2);
    queue2.pushBack(3); assert(queue2.getFrontData() == 3);
    assert(queue2.getBackData() == 1);
    cout << "-- ������������ pushBack ��������� ������� --------" << endl;
}

// ������������ ������ popBack
void testPopBack() {
    Deque<int> queue3;
    //���������
    queue3.pushFront(1); assert(queue3.getBackData() == 1);
    queue3.pushFront(2); assert(queue3.getBackData() == 2);
    queue3.pushFront(3); assert(queue3.getBackData() == 3);
    assert(queue3.getFrontData() == 1);
    //�������
    queue3.popBack(); assert(queue3.size() == 2);
    assert(queue3.getBackData() == 3);

    queue3.popBack(); assert(queue3.size() == 1);
    assert(queue3.getBackData() == 3);

    assert(queue3.popBack() == 3); assert(queue3.size() == 0);

    //�������� �� ������ ������ ������� double
    Deque<double> queueEmpty1;
    assert(queueEmpty1.popBack() == 0.0);

    //�������� �� ������ ������ ������� �����
    Deque<string> queueEmpty2;
    assert(queueEmpty2.popBack() == "");

    cout << "-- ������������ popBack ��������� ������� ---------" << endl;
}

// ������������ ������ popFront
void testPopFront() {
    Deque<int> queue4;
    //���������
    queue4.pushBack(1);
    queue4.pushBack(2);
    queue4.pushBack(3);
    //�������
    queue4.popFront(); assert(queue4.size() == 2);
    assert(queue4.getFrontData() == 3);

    queue4.popFront(); assert(queue4.size() == 1);
    assert(queue4.getFrontData() == 3);

    assert(queue4.popFront() == 3);	assert(queue4.size() == 0);

    //�������� �� ������ ������ ������� double
    Deque<double> queueEmpty1;
    assert(queueEmpty1.popFront() == 0.0);

    //�������� �� ������ ������ ������� �����
    Deque<string> queueEmpty2;
    assert(queueEmpty2.popFront() == "");
    cout << "-- ������������ popFront ��������� ������� --------" << endl;
}

// ������������ isEmpty
void testIsEmpty() {
    Deque<int> queue5;
    assert(queue5.isEmpty());

    queue5.pushFront(123);	assert(!queue5.isEmpty());

    queue5.popBack(); assert(queue5.isEmpty());
    cout << "-- ������������ isEmpty ��������� ������� ---------" << endl;
}