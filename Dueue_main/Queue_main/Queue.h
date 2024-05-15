#pragma once
#include "Spisok_one.h"    // ����������� ������ � �������� �������
#include "Spisok_class.h"  // ���������� ������ � �������� �������
#include <iostream> //��������� cin cout
#include <sstream>  //��������� ������ �� �������� ����� ������
#include <cassert>  //��� assert
#include <locale>   //���������� ������� setlocale ��� ��������� ������� ������


// ����� Queue ���� ������������� ��������� ������ - ������� (FIFO)
// param Type ��� ��������� �������
// ������������ �� ����������� ������ DoublyList
template <typename Type>
class Queue : public DoublyList<Type>
{
public:

    // ����������� �� ���������
    Queue() {}

    // ����������
    ~Queue() {}

    // ���������� �������� � �������
    // param element ����������� �������
    void AddQueue(Type element)
    {
        this->AddFront(element);
    }

    // �������� �������� �� �������, �������� ������ ��������, �������� �������� �� ��������� ��� Type
    Type DelQueue()
    {
        // ���� ���� ����
        if (this->isEmpty())
        { return Type(); } //�������� �������� �� ��������� ��� Type
         
        Type val = this->get_OneList(this->length() - 1)->data;
        this->DelBack();
        return val;
    }

    // ��������� ����� �� �������
    // return �������� true||false
    bool isEmpty() const {
        bool empty = false;
        if (this->length() == 0)
            empty = true;
        return empty;
    }

    // ������ ������ �������
    // return size_t - ������
    size_t size() const {
        return this->length();
    }

    // ������ �������� ����� �������
    // return Type
    Type getTailData() {
        return this->get_OneList(0)->data;
    }

    // ������ �������� ������ �������
    // return Type
    Type getHeadData() {
        return this->get_OneList(this->size() - 1)->data;
    }

    // ��������� ������� �������, ������� � ������ �� ���
    // return �������, ���� ������ ����, �� 0
    Type peek() {
        if (this->isEmpty())
        {
            return 0;
        }
        return this->get_OneList(this->length() - 1)->data;
    }

    // ������� ������� � ����������� �����.
    void print() const {
        cout << this->to_string() << endl;
    }

    // ���������� ������ ������� �������.
    Type front() const {
        if (!this->isEmpty()) {
            return this->first();
        }
        return Type();
    }

    // ���������� ��������� ������� �������.
    Type back() const {
        if (!this->isEmpty()) {
            return this->last();
        }
        return Type();
    }
};

// ������� ������������ ������ AddQueue
void Test_AddQueue() {
    Queue<int> queue;

    queue.AddQueue(1);
    assert(queue.getTailData() == 1);

    queue.AddQueue(2);
    assert(queue.getTailData() == 2);
    
    queue.AddQueue(3);
    assert(queue.getHeadData() == 1);
    assert(queue.getTailData() == 3);
    cout << "-- ������������ AddQueue ��������� ������� -------" << endl;
}

// ������� ������������ ������ DelQueue
void Test_DelQueue() {
    Queue<int> queue;

    //���������
    queue.AddQueue(1);
    queue.AddQueue(2);
    queue.AddQueue(3);

    //���������
    queue.DelQueue();
    assert(queue.size() == 2);
    assert(queue.getHeadData() == 2);
    assert(queue.getTailData() == 3);

    queue.DelQueue();
    assert(queue.size() == 1);
    assert(queue.getHeadData() == 3);
    assert(queue.getTailData() == 3);

    assert(queue.DelQueue() == 3);
    assert(queue.size() == 0);

    //�������� �� ������ ������ ������� double
    Queue<double> queueEmpty;
    assert(queueEmpty.DelQueue() == 0.0);

    //�������� �� ������ ������ ������� �����
    Queue<string> queueEmpty2;
    assert(queueEmpty2.DelQueue() == "");

    //��������� �� ������ �������� �� ������� �������
    //Queue<string> queueEmpty2;
    //assert(queueEmpty2.DelQueue() == "");

    cout << "-- ������������ DelQueue ��������� ������� -------" << endl;
}

// ������������ ������� Peek
void Test_Peek() {
    Queue<int> queue;

    queue.AddQueue(1);
    queue.AddQueue(2);
    queue.AddQueue(3);

    assert(queue.peek() == 1);

    queue.DelQueue();
    assert(queue.peek() == 2);

    queue.AddQueue(123);
    assert(queue.peek() == 2);
    cout << "-- ������������ Peek ��������� ������� -----------" << endl;
}

// ������������ ������� isEmpty
void Test_IsEmpty() {
    Queue<int> queue;
    assert(queue.isEmpty());

    queue.AddQueue(123);
    assert(!queue.isEmpty());

    queue.DelQueue();
    assert(queue.isEmpty());
    cout << "-- ������������ isEmpty ��������� ������� --------" << endl;
}

// ������� ������������ ������ Stack
void Test_Queue() 
{
    Test_AddQueue();
    Test_DelQueue();
    Test_Peek();
    Test_IsEmpty();
}
