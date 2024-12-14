#include <iostream>
#include <fstream>
#include <windows.h>

using namespace std;
// Функция для динамического выделения памяти под матрицу
double** createMatrix(int size) {
    double** matrix = new double* [size];
    for (int i = 0; i < size; i++) {
        matrix[i] = new double[size];
    }
    return matrix;
}
// Функция для освобождения памяти, выделенной под матрицу
void deleteMatrix(double** matrix, int size) {
    for (int i = 0; i < size; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}
// Функция для ввода матрицы с консоли
void inputMatrix(double** matrix, int size) {
    cout << "Введите элементы матрицы " << endl;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cin >> matrix[i][j];
        }
    }
}
// Функция для вывода матрицы
void printMatrix(double** matrix, int size) {
    cout << "Матрица: " << endl;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}
// Функция для чтения матрицы из файла
void readMatrixFromFile(double** matrix, int size, const string& filename) {
    ifstream infile(filename);
    if (!infile.is_open()) {
        cerr << "Ошибка открытия файла!" << endl;
        return;
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            infile >> matrix[i][j];
        }
    }
    infile.close();
}
// Функция для записи матрицы в файл
void writeMatrixToFile(double** matrix, int size, const string& filename) {
    ofstream outfile(filename);
    if (!outfile.is_open()) {
        cerr << "Ошибка открытия файла для записи!" << endl;
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            outfile << matrix[i][j] << " ";
        }
        outfile << endl;
    }
    outfile.close();
}
// Функция для копирования элементов из матрицы A в матрицу C
void copyMatchingElements(double** A, double** B, double** C, int size) {
    for (int i = 0; i < size; i++) {
        double diagonalElement = B[i][i]; // Диагональный элемент матрицы B
        for (int j = 0; j < size; j++) {
            if (A[i][j] == diagonalElement) {
                C[i][j] = A[i][j]; // Копируем элемент из A в C
            }
        }
    }
}
// Функция для интерактивного редактирования элементов матрицы
void editMatrix(double** matrix, int size) {
    int row, col;
    double newValue;
    char choice;
    cout << "Вы хотите изменить элемент матрицы? (y/n): ";
    cin >> choice;
    while (choice == 'y') {
        cout << "Введите номер строки (0-" << size - 1 << ") и номер столбца (0-" << size - 1 << "): ";
        cin >> row >> col;
        if (row >= 0 && row < size && col >= 0 && col < size) {
            cout << "Введите новое значение: ";
            cin >> newValue;
            matrix[row][col] = newValue;
            cout << "Элемент изменен." << endl;
        }
        else {
            cout << "Неверный индекс!" << endl;
        }
        cout << "Хотите изменить еще один элемент? (y/n): ";
        cin >> choice;
    }
}
int main() 
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    setlocale(LC_ALL, "RU");
    int size;
    int choice;
    cout << "Введите размерность квадратных матриц: ";
    cin >> size;
    // Динамическое выделение памяти для матриц
    double** A = new double* [size];
    double** B = new double* [size];
    double** C = new double* [size];
    for (int i = 0; i < size; i++) {
        A[i] = new double[size];
        B[i] = new double[size];
        C[i] = new double[size];
    }
    do {
        cout << "\nВыберите действие:" << endl
            << "1. Ввод матриц" << endl
            << "2. Вывод матриц" << endl
            << "3. Редактировать матрицы" << endl
            << "4. Копировать совпадающие элементы" << endl
            << "5. Записать матрицы в файл" << endl
            << "6. Прочитать матрицу из файла" << endl
            << "0. Выход" << endl;
        cin >> choice;
        switch (choice) {
        case 1:
            inputMatrix(A, size);
            inputMatrix(B, size);
            inputMatrix(C, size);
            break;
        case 2:
            printMatrix(A, size);
            printMatrix(B, size);
            printMatrix(C, size);
            break;
        case 3:
            editMatrix(A, size);
            editMatrix(B, size);
            editMatrix(C, size);
            break;
        case 4:
            copyMatchingElements(A, B, C, size);
            break;
        case 5:
            writeMatrixToFile(A, size, "matrixA.txt");
            writeMatrixToFile(B, size, "matrixB.txt");
            writeMatrixToFile(C, size, "matrixC.txt");
            break;
        case 6:
            readMatrixFromFile(A, size, "matrixA.txt");
            cout << "Матрица A (из файла):" << endl;
            printMatrix(A, size);
            readMatrixFromFile(B, size, "matrixB.txt");
            cout << "Матрица B (из файла):" << endl;
            printMatrix(B, size);
            readMatrixFromFile(C, size, "matrixC.txt");
            cout << "Матрица C (из файла):" << endl;
            printMatrix(C, size);
            break;
        case 0:
            deleteMatrix(A, size);
            deleteMatrix(B, size);
            deleteMatrix(C, size);
            break;
        }
        }while (choice != 0);

        deleteMatrix(A, size);
        deleteMatrix(B, size);
        deleteMatrix(C, size);
        SetConsoleOutputCP(866);
        SetConsoleCP(866);
        return 0;
 }
