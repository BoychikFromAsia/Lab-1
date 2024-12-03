#include <iostream>
#include <iomanip>

using namespace std;
void inputMatrix(double matrix[][10], int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> matrix[i][j];
        }
    }
}
void printMatrix(double matrix[][10], int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << fixed << setprecision(2) << matrix[i][j] << " ";
        }
        cout << endl;
    }
}
void multiplyMatrix(double A1[][10], double A2[][10], double result[][10], int N, int M, int K) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < K; ++j) {
            result[i][j] = 0;
            for (int k = 0; k < M; ++k) {
                result[i][j] += A1[i][k] * A2[k][j];
            }
        }
    }
}
void matrixPower(double A[][10], double result[][10], int x, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            result[i][j] = (i == j) ? 1 : 0;
        }
    }
    double base[10][10];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            base[i][j] = A[i][j];
        }
    }
    while (x > 0) {
        if (x % 2 == 1) {
            double temp[10][10];
            multiplyMatrix(result, base, temp, n, n, n);
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    result[i][j] = temp[i][j];
                }
            }
        }
        double temp[10][10];
        multiplyMatrix(base, base, temp, n, n, n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                base[i][j] = temp[i][j];
            }
        }
        x /= 2;
    }
}
int main(int argc, const char* argv[]) {
    setlocale(LC_ALL, "RU");
    bool isHuman = (argc <= 1 || strcmp(argv[1], "false") != 0);
    const int MAX_SIZE = 10;
    int N, M;
    if (isHuman)
        cout << "Введите N: ";
    cin >> N;
    if (isHuman)
        cout << "Введите M: ";
    cin >> M;
    double A1[MAX_SIZE][MAX_SIZE];
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

            double A2[MAX_SIZE][MAX_SIZE];
            if (isHuman)
                cout << "Введите элементы матрицы A2 размером " << M << " x " << K << " построчно:\n";
            inputMatrix(A2, M, K);

            if (M != K) {
                if (isHuman)
                    cout << "Невозможно произвести операцию" << endl;
                else
                    cout << "NO" << endl;
            }
            else {
                double result[MAX_SIZE][MAX_SIZE];
                multiplyMatrix(A1, A2, result, N, M, K);
                for (int i = 0; i < N; ++i) {
                    for (int j = 0; j < K; ++j) {
                        A1[i][j] = result[i][j];
                    }
                }
            }
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
                double result[MAX_SIZE][MAX_SIZE];
                matrixPower(A1, result, x, N);
                for (int i = 0; i < N; ++i) {
                    for (int j = 0; j < N; ++j) {
                        A1[i][j] = result[i][j];
                    }
                }
            }
        }
        else {
            if (isHuman)
                cout << "Некорректная команда." << endl;
        }
    }
    return 0;
}