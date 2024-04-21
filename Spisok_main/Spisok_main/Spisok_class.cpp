/// \file Spisok_class.cpp
/// \brief ������ � ���������� �������
/// \author ���������� ������� ���-22
/// \date 29.03.2024

#include "Spisok_one.h"
#include "Spisok_class.h"

void Test_AddFront()
{
    DoublyList<int> list;
    assert(list.length() == 0);
    // ������������ ���������� �������� � ������ ������
    list.AddFront(1);
    assert(list.length() == 1);
    assert(list.get_OneList(0)->data == 1);
    // ��������� �������� � ������
    list.AddFront(2);
    list.AddFront(3);
    // ������������ ���������� ��������� � ������ ������
    assert(list.length() == 3);
    assert(list.get_OneList(1)->data == 2);
    cout << "-- ������������ AddFront ��������� ������� --------" << endl;
}

void Test_AddBack()
{
    DoublyList<int> list;
    assert(list.length() == 0);
    // ������������ ���������� �������� � ������ ������
    list.AddBack(1);
    assert(list.length() == 1);
    assert(list.get_OneList(0)->data == 1);
    // ��������� ��� �������� � ������
    list.AddBack(2);
    list.AddBack(3);
    // ������������ ���������� ��������� � ����� ������
    assert(list.length() == 3);
    assert(list.get_OneList(1)->data == 2);
    assert(list.get_OneList(2)->data == 3);
    cout << "-- ������������ Test_AddBack ��������� ������� ----" << endl;
}

void Test_AddInList()
{
    DoublyList<int> list;
    assert(list.length() == 0);
    // ������������ ���������� �������� � ������ ������
    list.AddBack(1);
    assert(list.length() == 1);
    assert(list.get_OneList(0)->data == 1);
    // ��������� ��� �������� � ������
    list.AddBack(3);
    list.AddInList(2, list.get_OneList(0));
    // ������������ ���������� ��������� � �������� ������
    assert(list.length() == 3);
    assert(list.get_OneList(1)->data == 2);
    assert(list.get_OneList(2)->data == 3);
    cout << "-- ������������ Test_AddInList ��������� ������� --" << endl;
}

void Test_DelFront() {
    DoublyList<int> list;
    assert(list.length() == 0);
    // ��������� �������� � ������
    list.AddBack(1);
    list.AddBack(2);
    list.AddBack(3);
    assert(list.length() == 3);
    list.DelFront();
    // ������������ �������� ��������� �� ������ ������
    assert(list.length() == 2);
    //assert(list.find(1)->data == 1);
    assert(list.find(2)->data == 2);
    assert(list.find(3)->data == 3);
    cout << "-- ������������ Test_DelFront ��������� ������� ---" << endl;
}

void Test_DelBack() {
    DoublyList<int> list;
    assert(list.length() == 0);
    // ��������� �������� � ������
    list.AddBack(1);
    list.AddBack(2);
    list.AddBack(3);
    assert(list.length() == 3);
    list.DelBack();
    // ������������ �������� ��������� � ����� ������
    assert(list.length() == 2);
    assert(list.find(1)->data == 1);
    assert(list.find(2)->data == 2);
    //assert(list.find(3)->data == 3);
    cout << "-- ������������ Test_DelBack ��������� ������� ----" << endl;
}

void Test_DelInList() {
    DoublyList<int> list;
    assert(list.length() == 0);
    // ��������� �������� � ������
    list.AddBack(1);
    list.AddBack(2);
    list.AddBack(3);
    assert(list.length() == 3);
    list.DelInList(2);
    // ������������ �������� ��������� � �������� ������
    assert(list.length() == 2);
    assert(list.find(1)->data == 1);
    assert(list.find(3)->data == 3);
    //assert(list.find(3)->data == 3);
    cout << "-- ������������ Test_DelInList ��������� ������� --" << endl;
}

void Test_Find() {
    DoublyList<int> list;
    assert(list.length() == 0);
    // ��������� �������� � ������
    list.AddBack(1);
    list.AddBack(2);
    list.AddBack(3);
    // ������������ ������ ������������� ��������
    assert(list.find(2) != nullptr);
    // ������������ ������ ��������������� ��������
    assert(list.find(5) == nullptr);
    cout << "-- ������������ Test_Find ��������� ������� -------" << endl;
}

void Test_Sort() {
    DoublyList<int> list;
    // ������������ ���������� ������� ������
    list.sort();
    assert(list.length() == 0);
    // ��������� �������� � ������
    list.AddBack(3);
    list.AddBack(1);
    list.AddBack(2);
    // ������������ ���������� ������
    list.sort();
    assert(list.find(1)->data == 1);
    assert(list.find(2)->data == 2);
    assert(list.find(3)->data == 3);
    cout << "-- ������������ Test_Sort ��������� ������� -------" << endl;
}

// ������������ ������
void Test_Assert()
{
    // ����������� �� ��������� ������ ����
    DoublyList<int> list1;
    assert(list1.length() == 0);

    // �����������, ����������� ������ n ���������� � ��������� value
    DoublyList<int> list2(5, 10);
    assert(list2.length() != 0);
    assert(list2.length() == 5);
    assert(list2.get_OneList(2)->data == 10);

    
    // ������� ������ ����, ����������� data, ����� ���������� ���� node
    list1.AddFront(2);
    list1.AddInList(8, list1.find(2));
    assert(list1.length() == 2);

    // ���������� ���� �������
    list1.ConcatenateLists(list2);
    assert(list1.length() == 7);
    cout << "-- ������������ Test_Assert ��������� ������� -----" << endl;
 }

