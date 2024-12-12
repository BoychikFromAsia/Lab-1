#include <iostream>
#include <fstream>

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
    cout << "Введите элементы матрицы: " << endl;
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
        return;
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
    // Инициализация элементов матрицы C нулями
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            C[i][j] = 0;

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
    char choice;
    do {
        int row, col;
        double newValue;
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
    } while (choice == 'y');
}

int main() {
    setlocale(LC_ALL, "RU");
    int size;

    cout << "Введите размерность квадратных матриц: ";
    cin >> size;

    double** A = createMatrix(size);
    double** B = createMatrix(size);
    double** C = createMatrix(size);

    int choice;
    while (true) {
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
            break;
        case 2:
            printMatrix(A, size);
            printMatrix(B, size);
            printMatrix(C, size);
            break;
        case 3:
            editMatrix(A, size);
            editMatrix(B, size);
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
            break;
        case 0:
            deleteMatrix(A, size);
            deleteMatrix(B, size);
            deleteMatrix(C, size);
            return 0;
        default:
            cout << "Неверный выбор, попробуйте снова." << endl;
        }
    }
    return 0;
}