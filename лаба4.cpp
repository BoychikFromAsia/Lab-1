#include <iostream>
#include <iomanip>
using namespace std;

void inputMatrix(double** matrix, int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> matrix[i][j];
        }
    }
}
void printMatrix(double** matrix, int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << fixed << setprecision(2) << matrix[i][j] << (j < m - 1 ? " " : "");
        }
        cout << endl;
    }
}
void multiplyMatrix(double** A1, double** A2, double** result, int N, int M, int K) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < K; ++j) {
            result[i][j] = 0;
            for (int k = 0; k < M; ++k) {
                result[i][j] += A1[i][k] * A2[k][j];
            }
        }
    }
}
void matrixPower(double** A, double** result, int x, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            result[i][j] = (i == j) ? 1 : 0; 
        }
    }
    double** base = new double* [n];
    for (int i = 0; i < n; ++i) {
        base[i] = new double[n];
        for (int j = 0; j < n; ++j) {
            base[i][j] = A[i][j];
        }
    }
    while (x > 0) {
        if (x % 2 == 1) {
            double** temp = new double* [n];
            for (int i = 0; i < n; ++i) {
                temp[i] = new double[n];
            }
            multiplyMatrix(result, base, temp, n, n, n);
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    result[i][j] = temp[i][j];
                }
            }
            for (int i = 0; i < n; ++i) {
                delete[] temp[i];
            }
            delete[] temp;
        }
        double** temp = new double* [n];
        for (int i = 0; i < n; ++i) {
            temp[i] = new double[n];
        }
        multiplyMatrix(base, base, temp, n, n, n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                base[i][j] = temp[i][j];
            }
        }
        for (int i = 0; i < n; ++i) {
            delete[] temp[i];
        }
        delete[] temp;
        x /= 2;
    }

    for (int i = 0; i < n; ++i) {
        delete[] base[i];
    }
    delete[] base;
}
int main(int argc, const char* argv[]) {
    setlocale(LC_ALL, "RU");
    bool isHuman = (argc <= 1 || strcmp(argv[1], "false") != 0);
    int N, M;
    if (isHuman)
        cout << "Введите N: ";
    cin >> N;
    if (isHuman)
        cout << "Введите M: ";
    cin >> M;
    // Выделяение памяти для матрицы A1
    double** A1 = new double* [N];
    for (int i = 0; i < N; ++i) {
        A1[i] = new double[M];
    }
    if (isHuman)
        cout << "Введите элементы матрицы A1 построчно:\n";
    inputMatrix(A1, N, M);
    while (true) {
        int command;
        if (isHuman)
            cout << "Введите команду (0 - завершить, 1 - вывести A1, 2 - умножить на A2, 3 - возвести в степень): ";
        cin >> command;

        if (command == 0) {
            break;
        }
        else if (command == 1) {
            printMatrix(A1, N, M);
        }
        else if (command == 2) {
            int K;
            if (isHuman)
                cout << "Введите K: ";
            cin >> K;
            // Выделение памяти для матрицы А2
            double** A2 = new double* [M];
            for (int i = 0; i < M; ++i) {
                A2[i] = new double[K];
            }
            if (isHuman)
                cout << "Введите элементы матрицы A2 размером " << M << " x " << K << " построчно:\n";
            inputMatrix(A2, M, K);
            if (M != M) { 
                if (isHuman)
                    cout << "Невозможно произвести операцию" << endl;
                else
                    cout << "NO" << endl;
            }
            else {
                // Результирующая матрица
                double** result = new double* [N];
                for (int i = 0; i < N; ++i) {
                    result[i] = new double[K];
                }
                multiplyMatrix(A1, A2, result, N, M, K);
                for (int i = 0; i < N; ++i) {
                    for (int j = 0; j < K; ++j) {
                        A1[i][j] = result[i][j];
                    }
                }
                // Освобождение памяти
                for (int i = 0; i < N; ++i) {
                    delete[] result[i];
                }
                delete[] result;
            }
            // Освобождение памяти
            for (int i = 0; i < M; ++i) {
                delete[] A2[i];
            }
            delete[] A2;
        }
        else if (command == 3) {
            int x;
            if (isHuman)
                cout << "Введите натуральное число x: ";
            cin >> x;

            if (N != M) {
                if (isHuman)
                    cout << "Невозможно произвести операцию" << endl;
                else
                    cout << "NO" << endl;
            }
            else {
                // Результирующая матрица
                double** result = new double* [N];
                for (int i = 0; i < N; ++i) {
                    result[i] = new double[N];
                }
                matrixPower(A1, result, x, N);
                for (int i = 0; i < N; ++i) {
                    for (int j = 0; j < N; ++j) {
                        A1[i][j] = result[i][j];
                    }
                }
                // Освобождение памяти
                for (int i = 0; i < N; ++i) {
                    delete[] result[i];
                }
                delete[] result;
            }
        }
        else {
            if (isHuman)
                cout << "Некорректная команда." << endl;
        }
    }
    // Освобождение памяти матрицы А1
    for (int i = 0; i < N; ++i) {
        delete[] A1[i];
    }
    delete[] A1;
    return 0;
}