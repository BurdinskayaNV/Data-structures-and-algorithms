/// \file Modul_file.h
/// \brief ������ � �������
/// \author ���������� ������� ���-22
/// \date 18.02.2024
#pragma once

#include "Modul_array.h" // ����� ������������� ����� Modul_array

//---��������a ������ � ��������� ���� TxtArray.txt
// ������ a, size, file_name - ���������� ���������
// ������ �� ����������, ������ ����� ������ � ����
template <typename TArray>
void WriteFile(const string& file_name, const TArray* a, size_t size)
{
	// ����� �������� ����� �� ������ ios::out
	// �������������� ��� �������� �����
	ofstream Fin(file_name, ios::out); //�������� ������ � ����� ����� ������
	if (!Fin.is_open())	  // ���� �� ������ ����
	{
		throw runtime_error("���� �� ������");
	}
	// ����� � ���� ������������ ������
	for (size_t i = 0; i < size; ++i)
	{
		Fin << a[i] << " " << endl;
	}
	Fin.close(); // ������� close() ��������� ����� �����
	cout << "����� � ��������� ����. ����� ������ � ����." << endl;
	cout << "-----------------------------------------------------" << endl;
}

//-----��������a ������ �� ���������� ����� TxtArray.txt
// ������ a, size, file_name - ���������� ���������
// ���������� ����������� ������ a �� �����
template <typename TArray>
void ReadFile(const string& file_name, TArray* a, size_t size)
{
	ifstream Fout; // ��������� ��� Fout ��� ������
	//����� ������� ���� ��� ������ ios::in ����� ���������� ���
	//������ ������ open(), ������������� ��� �������� �����(��������� ����)
	Fout.open(file_name, ios::in); //��������� ���� ��� ������ �� ������
	//�������� �� ������� �����
	if (!Fout.is_open())	  // ���� �� ������ ����
	{
		throw runtime_error("���� �� ������");
	}
	if (!Fout.eof()) // ������ ���� �� ����� �����
	{
		for (size_t i = 0; i < size; ++i) { Fout >> a[i]; }
	}
	Fout.close(); // ������� close() ��������� ����� �����
	cout << "������ �� ���������� �����. ����� �����." << endl;
}

//---������� ������ ���������� ��������� ������� � ��������� ����� TxtArray.txt
size_t SizeFile(const string& file_name)
{
	size_t res = 0; // ���������� ��� ����� ���������� �����
	ifstream file(file_name); // �������� ����� 
	if (!file.is_open()) // ���� �� ������ ����
	{
		throw runtime_error("���� �� ������!"); // ���� ���, �� � ������
	}
	// ���� ����� ���������� ����� -> ���������� ��������� �������
	while (!file.eof()) // ������ ���� �� ����� �����
	{
		char c;
		file >> c;
		res++; // ���� ����� ����, ���� getline ������ ��������
	}
	file.close(); // ������� ����
	if (res == 0) // ������, ���� ���� ����
		throw runtime_error("������ �� ������ � ��������� ����� - ���� ����");
	return res;
}

//---��������a ������ � �������� ���� BinArray.txt // �������������
//// �������� ������� ��� ��� 
template <typename TArray>
void WriteFileBin(const string& file_name, const TArray* arr, size_t size)
{
	ofstream file(file_name, ios::binary);
	// �������� ���������� reinterpret_cast ������������ ��� ���������� ������������� �����
	file.write(reinterpret_cast<const char*>(&size), sizeof(size));
	file.write(reinterpret_cast<const char*>(arr), sizeof(TArray) * size);
	file.close();
	cout << "����� � �������� ����. ����� ������ � ����." << endl;
	cout << "-----------------------------------------------------" << endl;
}

//-----��������a ������ �� ��������� ����� BinArray.txt
template <typename TArray>
void ReadFileBin(const string& file_name, TArray*& arr, size_t& size)
{
	// �������� ���������� reinterpret_cast ������������ ��� ���������� ������������� �����
	ifstream file(file_name, ios::binary);
	file.read(reinterpret_cast<char*>(&size), sizeof(size));
	arr = new TArray[size];
	file.read(reinterpret_cast<char*>(arr), sizeof(TArray) * size);
	file.close();
	cout << "������ �� ��������� �����. ����� �����." << endl;
}

//---���� ������ � �������
/// *** ������� � ��������� ����
void Test_Work_files()
{
	cout << "------- ������ � ��������� ������ -------------------" << endl;
	// ��������� ������ ������� � ��������� ���� TxtArray.txt
	try { WriteFile(fileTxt, Iarr, Asize); }
	catch (const invalid_argument& error) {
		cout << error.what();
	}
	// ������ �� ���������� ����� TxtArray.txt ������ � ������ �� �������
	try   // �������� �� ����������
	{
		// ������� ���������� ��������� ������� �� ����� TxtArray.txt
		size_t size_1 = SizeFile(fileTxt);
	}
	catch (const exception& error) // ���� TxtArray.txt �� ������ ��� ����
	{
		// ���, ������� ����������� ��� ������������� ���������� ����
		// Exception ������������ � ����� try
		cout << error.what() << endl; // ���������
	}
	// ������� �� ����� ������ �������� �������������
	int* arrtxt = new int[Asize] {0}; // ��������� ������������ ������ Int
	try { ReadFile(fileTxt, arrtxt, Asize); }
	catch (const invalid_argument& error) {
		cout << error.what();
	}
	Screen_array(arrtxt, Asize); // ������� �� ����� ������ �������� �������������
	cout << endl;

	cout << "------- ������ � �������� ������ --------------------" << endl;
	// ��������� ������ ������� � ��������� ���� TxtArray.txt
	try { WriteFileBin(fileBin, Iarr, Asize); }
	catch (const invalid_argument& error) {
		cout << error.what();
	}
	// ������� �� ����� ������ �������� �������������
	int* arrbin = new int[Asize] {0}; // ��������� ������������ ������ Int
	try { ReadFileBin(fileBin, arrbin, Asize); }
	catch (const invalid_argument& error) {
		cout << error.what();
	}
	Screen_array(arrbin, Asize); // ������� �� ����� ������ �������� �������������
	cout << endl;
	cout << "-----------------------------------------------------" << endl;
	delete[] arrtxt;
	delete[] arrbin;
}