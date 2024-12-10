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
    // Инициализируем элементы матрицы C нулями
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            C[i][j] = 0;
        }
    }
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
int main() {
    setlocale(LC_ALL, "RU");
    int size;
    cout << "Введите размерность квадратных матриц: ";
    cin >> size;
    double** A = createMatrix(size);
    double** B = createMatrix(size);
    double** C = createMatrix(size);
    // Ввод матриц
    inputMatrix(A, size);
    inputMatrix(B, size);
    // Редактирование элементов матриц
    editMatrix(A, size);
    editMatrix(B, size);
    // Копирование элементов из A в C
    copyMatchingElements(A, B, C, size);
    // Вывод матриц
    cout << "Матрица A:" << endl;
    printMatrix(A, size);
    cout << "Матрица B:" << endl;
    printMatrix(B, size);
    cout << "Матрица C (элементы из A, совпадающие с диагональными элементами B):" << endl;
    printMatrix(C, size);
    // Запись в файл
    writeMatrixToFile(A, size, "matrixA.txt");
    writeMatrixToFile(B, size, "matrixB.txt");
    writeMatrixToFile(C, size, "matrixC.txt");
    // Чтение из файла (пример)
    double** D = createMatrix(size);
    readMatrixFromFile(D, size, "matrixA.txt");
    cout << "Матрица D (из файла):" << endl;
    printMatrix(D, size);
    // Освобождение памяти
    deleteMatrix(A, size);
    deleteMatrix(B, size);
    deleteMatrix(C, size);
    deleteMatrix(D, size);
    return 0;
}