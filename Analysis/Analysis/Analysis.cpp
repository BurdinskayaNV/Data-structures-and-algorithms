int main(int argc, char* argv[])
{
    system("chcp 65001 > nul"); //подключение русского языка 
    // «RUSSIAN» локализация произойдёт на русский язык
    setlocale(LC_ALL, "RUSSIAN");
    // Генерирует случайное число, используя текущею дату, для непредсказуемости результата
    srand(time(0));

    // Аргументы командной строки cmd arg для функции main
    // argv[0] - имя файла Analysis.exe
    // значит начинаем argv[1], argv[2] и argv[3]
    // в нашем случае argc = 4
    // (argv[0] имя самого проекта, argv[1] размерность массива n,
    // argv[2] число x, argv[3] имя файла для ввода и сохранения данных)
    string str_n, str_x;
    int k = argc;
    if (k == 1)
    {
        cout << "Введите размерность массива" << endl;
        cout << "n = "; cin >> n;
        cout << "\n";
        cout << "Введите число x " << endl;
        cout << "x = "; cin >> x;
        cout << "\n";
        cout << "Введите имя файла " << endl;
        cout << "file_name = "; cin >> file_name;
        cout << "\n";
    }
    else if ((k == 2) || (k == 3) || (k > 4))
    {
        str_n = argv[1];
        if (str_n == "help")	// Если введут help
        {
            cout << "Чтобы программа работала корректно, введите первый аргумент число: <размерность массива n>" << endl;
            cout << "Далее через пробел введите второй аргумент число: <число x> " << endl;
            cout << "Далее <имя файла для ввода и сохранения данных> " << endl;
            return 0;
        }
        else
        {
            cout << "Чтобы программа работала корректно, нужно ввести три аргумента числа n и x, а так же имя файла" << endl;
            cout << "Если нужна помощь введите 'help' в качестве аргумента" << endl;
            return 0;
        }
        cout << "\n";
    }
    else if (k == 4)
    {
        try {
            n = stoi(argv[1]); // преобразовать строку в int 
            x = stoi(argv[2]); // преобразовать строку в int 
        }
        catch (const std::invalid_argument& error) {
            std::cout << error.what(); // выводим сообщение об ошибке
        }
        file_name = argv[3];
    }
    // Тестирование процедуры Work_array
    Test_Work_array();
    // открытие файла для записи
    ofstream F(file_name);
    F << "Начало " << endl;
    F << endl;
	F.close(); 
	
    int* arr1 = new int[n] {1, 2, 3, 4};
    int* arr2 = new int[n] {1, 2, 4, 3};
    int* arr3 = new int[n] {1, 3, 2, 4}; 
    //int* arr = new int[n] {1, 3, 4, 2};
    //int* arr = new int[n] {1, 4, 2, 3};
    //int* arr = new int[n] {1, 4, 3, 2};
    //int* arr = new int[n] {2, 1, 3, 4};
    //int* arr = new int[n] {2, 1, 4, 3};
    //int* arr = new int[n] {2, 3, 1, 4};
    //int* arr = new int[n] {2, 3, 4, 1};
    //int* arr = new int[n] {2, 4, 1, 3};
	int near1 = find_nearby(Iarr, n, x, 10, file_name);
	//double near2 = find_nearby(Darr, n, x, 10);
    int near3 = find_nearby(arr1, n, x, 10, file_name);
    int near4 = find_nearby(arr2, n, x, 10, file_name);
    int near5 = find_nearby(arr3, n, x, 10, file_name);
    cout << "Ближайший элемент к X в массиве Int  " << near1 << endl;
	//cout << "Ближайший элемент к X в массиве Double " << near2 << endl;
	cout << "Ближайший элемент к X в массиве arr1  " << near3 << endl;
	cout << "Ближайший элемент к X в массиве arr2  " << near4 << endl;
	cout << "Ближайший элемент к X в массиве arr3  " << near5 << endl;
	
    Test_Find_nearby(); // Тестирование процедуры поиска ближайшего числа
    return 0;
}
