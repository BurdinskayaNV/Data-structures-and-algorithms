#pragma once
#include "Spisok_one.h"    // ����������� ������ � �������� �������
#include "Spisok_class.h"  // ���������� ������ � �������� �������
#include <cassert>

// ����� Stack ���� ������������� ��������� ������ - �����
// Type ��� ��������� �����
template <typename Type>
// ������������ �� ����������� ������ DoublyList
class Stack : public DoublyList<Type>
{
public:
    // ���������� �������� � ������� �����
    // element ����������� �������
    void push(Type element)
    {
        this->AddFront(element);
    }

    // �������� �������� �� ������� �����
    Type pop()
    {
        // ���� ���� ����
        if (this->isEmpty())
        { return 0; }
        
        Type val = this->get_OneList(0)->data;
        this->DelFront();
        return val;
    }

    // ��������� ������ �� ����
    // return �������� true||false ��� 1||0
    bool isEmpty() {
        bool b = false;
        if (this->length() == 0)
            b = true;
        return b;
    }

    // ��������� ��������� ������� �����
    // return �������, ���� ������ ����, �� 0
    Type peek() {
        if (this->isEmpty())
        { return 0; }
        return this->get_OneList(0)->data;
    }
};

// ������������ ������ Push
void Test_Push() {
    Stack<int> stack;
    // ���������� �������� � ������� �����
    stack.push(1);
    assert(stack.get_OneList(0)->data == 1);
    stack.push(2);
    assert(stack.get_OneList(0)->data == 2);
    
    stack.push(3);
    assert(stack.get_OneList(1)->data == 2);
    assert(stack.get_OneList(0)->data == 3);

    cout << "-- ������������ Push ��������� ������� -------" << endl;
}

// ������������ ������ Pop
void Test_Pop() {
    Stack<int> stack;
    // ���������� �������� � ������� �����
    stack.push(1);
    stack.push(2);
    stack.push(3);
    assert(stack.get_OneList(0)->data == 3);

    // �������� �������� �� ������� �����
    stack.pop();
    assert(stack.length() == 2);
    assert(stack.get_OneList(0)->data == 2);

    stack.pop();
    assert(stack.length() == 1);
    assert(stack.get_OneList(0)->data == 1);

    stack.pop();
    assert(stack.length() == 0);
    cout << "-- ������������ Pop ��������� ������� --------" << endl;
}

// ������������ ������ Peek
void Test_Peek() {
    Stack<int> stack;
    // ���������� �������� � ������� �����
    stack.push(1);
    stack.push(2);
    stack.push(3);
    assert(stack.peek() == 3); // ��������� ��������� ������� �����
    
    // �������� �������� �� ������� �����
    stack.pop();
    assert(stack.peek() == 2); // ��������� ��������� ������� �����
    
    // ���������� �������� � ������� �����
    stack.push(123);
    assert(stack.peek() == 123); // ��������� ��������� ������� �����
    cout << "-- ������������ Peek ��������� ������� -------" << endl;
}

// ������������ ������ isEmpty
void Test_IsEmpty() {
    Stack<int> stack;
    assert(stack.isEmpty()); // �����

    stack.push(123); // ���������� �������� � ������� �����
    assert(!stack.isEmpty()); // �� �����
    cout << "-- ������������ isEmpty ��������� ������� ----" << endl;
}

// ������������ ������ Stack
void Test_Stack()
{
    Test_Push();
    Test_Pop();
    Test_Peek();
    Test_IsEmpty();
}