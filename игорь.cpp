#include <iostream>
#include <iomanip>

using namespace std;
void deleteMatrix(int** matrix, int size) {
	for (int i = 0; i < size; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
}
void inputMatrix(int** matrix, int n, int m) {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			cin >> matrix[i][j];
		}
	}
}
void printMatrix(int** matrix, int n, int m) {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			cout << fixed << setprecision(0) << matrix[i][j] << (j < m - 1 ? " " : "");
		}
		cout << endl;
	}
}
void multiplyMatrix(int** A1, int** A2, int** result, int N, int M, int K) {
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < K; ++j) {
			result[i][j] = 0;
			for (int k = 0; k < M; ++k) {
				result[i][j] += A1[i][k] * A2[k][j];
			}
		}
	}
}
void matrixPower(int** A, int** result, int x, int n) {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			result[i][j] = (i == j) ? 1 : 0;
		}
	}
	int** base = new int* [n];
	for (int i = 0; i < n; ++i) {
		base[i] = new int[n];
		for (int j = 0; j < n; ++j) {
			base[i][j] = A[i][j];
		}
	}
	while (x > 0) {
		if (x % 2 == 1) {
			int** temp1 = new int* [n];
			for (int i = 0; i < n; ++i) {
				temp1[i] = new int[n];
			}
			multiplyMatrix(result, base, temp1, n, n, n);
			for (int i = 0; i < n; ++i) {
				for (int j = 0; j < n; ++j) {
					result[i][j] = temp1[i][j];
				}
			}
			deleteMatrix(temp1,n)
		}
		int** temp2 = new int* [n];
		for (int i = 0; i < n; ++i) {
			temp2[i] = new int[n];
		}
		multiplyMatrix(base, base, temp2, n, n, n);
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				base[i][j] = temp2[i][j];
			}
		}
		deleteMatrix(temp2, n)
		x /= 2;
	}
	deleteMatrix(base, n)
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
	int** A1 = new int* [N];
	for (int i = 0; i < N; ++i) {
		A1[i] = new int[M];
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
			int** A2 = new int* [M];
			for (int i = 0; i < M; ++i) {
				A2[i] = new int[K];
			}
			if (isHuman)
				cout << "Введите элементы матрицы A2 размером " << M << " x " << K << " построчно:\n";
			inputMatrix(A2, M, K);
			if (N != K) {
				if (isHuman)
					cout << "Невозможно произвести операцию" << endl;
				else
					cout << "NO" << endl;
			}
			else {
				// Результирующая матрица
				int** result = new int* [N];
				for (int i = 0; i < N; ++i) {
					result[i] = new int[K];
				}
				multiplyMatrix(A1, A2, result, N, M, K);
				for (int i = 0; i < N; ++i) {
					for (int j = 0; j < K; ++j) {
						A1[i][j] = result[i][j];
						M = K;
					}
				}
				// Освобождение памяти
				deleteMatrix(result, N);
			// Освобождение памяти
				deleteMatrix(A2, M);
		else if (command == 3) {
			if (N != M) {
				if (isHuman)
					cout << "Невозможно произвести операцию" << endl;
				else
					cout << "NO" << endl;
			}
			else {
				int x;
				if (isHuman)
					cout << "Введите натуральное число x: ";
				cin >> x;
				// Результирующая матрица
				int** result = new int* [N];
				for (int i = 0; i < N; ++i) {
					result[i] = new int[N];
				}
				matrixPower(A1, result, x, N);
				for (int i = 0; i < N; ++i) {
					for (int j = 0; j < N; ++j) {
						A1[i][j] = result[i][j];
					}
				}
				// Освобождение памяти
				deleteMatrix(result, N);
		}
		else {
			if (isHuman)
				cout << "Некорректная команда." << endl;
		}
	}
	// Освобождение памяти матрицы А1
	deleteMatrix(A1, N);	
	return 0;
}