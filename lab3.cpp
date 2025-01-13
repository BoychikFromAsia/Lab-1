#include <iostream>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <cstring>

using namespace std;
double F(double x, double a, double b, double c)
{
	if (x < 0 && b != 0)
	{
		return a * x * x + b;
	}
	else if (x > 0 && b == 0)
	{
		return (x - a) / (x - c);
	}
	else {
		return x / c;
	}
}
double roundValue(double value, double a, double b, double c)
{
	int a_int = static_cast<int>(a);
	int b_int = static_cast<int>(b);
	int c_int = static_cast<int>(c);
	if (((a_int | b_int) & (a_int | c_int)) == 0)
	{
		return (value - static_cast<int>(value) >= 0.5) ? ceil(value) : floor(value);
	}
	else
	{
		return round(value * 100.0) / 100.0;
	}
}
void tab(int a, char d)
{
	for (int i = 0; i < a; i++)
		cout << d;
}
void printLine(int widthX, int widthF)
{
	cout << " ";
	cout << string(widthX + 2, '-');
	cout << string(widthF + 2, '-')<<endl;
}
void header(int widthX, int widthF)
{
	printLine(widthX, widthF);
	cout << "| " << setw(widthX) << "x" << " | " << setw(widthF) << "F" << " |" << endl;
	printLine(widthX, widthF);
}
void table(double a, double b, int widthX, int widthF)
{
	cout << "| ";
	string num1 = to_string(a);
	num1.erase(num1.length() - 4, 4);
	string num2 = to_string(b);
	num2.erase(num2.length() - 4, 4);
	while (num1.length() < widthX)
		num1 = " " + num1;
	while (num2.length() < widthF)
		num2 = " " + num2;
	cout << setw(widthX) << num1 << " | "
		<< setw(widthF) << num2 << " |" << endl;
}
void findMaxLengths(double arr[], double startX, double endX, int& maxLenX, int& maxLenF)
{
	int n = 15;
	double step = (endX - startX) / (n - 1);
	maxLenX = to_string(startX).length();
	maxLenF = 0;
	for (int i = 0; i < n; ++i) {
		double x = startX + step * i;
		int lenX = to_string(x).length();
		int lenF = to_string(arr[i]).length();
		if (lenX > maxLenX)
		{
			maxLenX = lenX;
		}
		if (lenF > maxLenF)
		{
			maxLenF = lenF;
		}
	}
}
void printTable(double arr[], double startX, double endX)
{
	int n = 15;
	int maxLenX, maxLenF;
	findMaxLengths(arr, startX, endX, maxLenX, maxLenF);
	header(maxLenX, maxLenF);
	double step = (endX - startX) / (n - 1);
	for (int i = 0; i < n; ++i)
	{
		double x = startX + step * i;
		table(x, arr[i], maxLenX, maxLenF);
	}
	printLine(maxLenX, maxLenF);
}
void roundArrays(double array[], double x1, double x2, double a, double b, double c, bool isArray1)
{
	for (int i = 0; i < 15; ++i)
	{
		double x = 0;
		if (isArray1)
		{
			x = x1 + (x2 - x1) * (i / 14.0);
		}
		else
		{
			x = -x2 + (x2 - x1) * (i / 14.0);
		}
		if (x == -0)
		{
			x = 0;
		}
		array[i] = roundValue(F(x, a, b, c), a, b, c);
	}
}
void printarrays(double array[])
{
	for (int i = 0; i < 15; i++)
	{
		if (array[i] == -0) array[i] = 0;
		cout << array[i];
		if (i != 14)
		{
			cout << " ";
		}
	}
	cout << endl;
}
void printminfives(double arr[])
{
	for (int i = 0; i < 3; ++i)
	{
		double min = arr[i * 5];
		for (int j = 1; j < 5; ++j)
		{
			if (arr[i * 5 + j] < min)
			{
				min = arr[i * 5 + j];
			}
		}
		cout << min << endl;
	}
}
void sort(double list[], int listLength)
{
	for (int i = 1; i < listLength; i++)
	{
		int j = i - 1;
		while (j >= 0 && list[j] > list[j + 1])
		{
			swap(list[j], list[j + 1]);
			j--;
		}
	}
}
int countpoftor(double arr[])
{
	int poftor = 0;
	for (int i = 0; i < 15; ++i)
	{
		bool isPoftor = false;
		for (int j = 0; j < i; ++j)
		{
			if (arr[i] == arr[j])
			{
				isPoftor = true;
				break;
			}
		}
		if (isPoftor)
		{
			continue;
		}
		int count = 0;
		for (int j = i; j < 15; ++j)
		{
			if (arr[i] == arr[j])
			{
				count++;
			}
		}
		if (count > 1)
		{
			poftor++;
		}
	}
	return poftor;
}
bool istwo(double a, double b)
{
	double log = log2(a);
	if ((a < b) && (log == round(log)) && (a >= 1) && (log >= 0))
		return true;
	else
		return false;
}
int IndexPowerofTwo(double arr[])
{
	int ind = -1;
	for (int i = 14; i > -1; i--)
	{
		if (i == 14)
		{
			if (istwo(arr[i], arr[i] + 1))
				ind = i;
			else
				break;
		}
		else
		{
			if (istwo(arr[i], arr[i + 1]))
				ind = i;
			else
				break;
		}
	}
	return ind;
}
int main(int argc, char* argv[])
{
	setlocale(LC_CTYPE, "rus");
	bool isHuman = false;
	if (argc <= 1 || strcmp(argv[1], "false") != 0)
	{
		isHuman = true;
	}
	const int size = 15;
	double array1[size], array2[size];
	double sortedarray[size];
	double a, b, c, x1, x2;
	if (isHuman)
	{
		cout << "Введите х1, х2, а, b, c: " << endl;
	}
	cin >> x1 >> x2 >> a >> b >> c;
	roundArrays(array1, x1, x2, a, b, c, true);
	roundArrays(array2, x1, x2, a, b, c, false);
	if (isHuman)
	{
		cout << "Первый массив: " << endl;
		printTable(array1, x1, x2);
		cout << "Второй массив: " << endl;
		printTable(array2, -x2, -x1);
	}
	else
	{
		printarrays(array1);
		printarrays(array2);
	}
	if (isHuman)
	{
		cout << "Минимальные элементы: " << endl;
	}
	printminfives(array1);

	for (int i = 0; i < size; i++)
	{
		sortedarray[i] = array1[i];
	}
	sort(sortedarray, size);
	if (isHuman)
	{
		cout << "Сортированный массив: " << endl;
	}
	printarrays(sortedarray);
	if (isHuman)
	{
		cout << "Количество одинаковых элементов: " << endl;
	}
	cout << countpoftor(array1) << endl;
	if (isHuman)
	{
		cout << "Индекс степени двойки: " << endl;
	}
	cout << IndexPowerofTwo(array1) << endl;
	double negarray[size] = {}, posarray[size] = {};
	int negCount = 0, posCount = 0;
	for (int i = 0; i < 15; i++)
	{
		negarray[i] = 0;
		posarray[i] = 0;
	}
	for (int i = 0; i < 15; ++i)
	{
		if (array2[i] < 0)
		{
			negarray[negCount++] = array2[i];
		}
		if (array2[i] > 0)
		{
			posarray[posCount++] = array2[i];
		}
	}
	for (int i = 0; i < 15; ++i)
	{
		if (array1[i] < 0)
		{
			if (negarray[negCount] == 0)
			{
				negarray[negCount++] = array1[i];
			}
		}
		if (array1[i] > 0)
		{
			if (posarray[posCount] == 0)
			{
				posarray[posCount++] = array1[i];
			}
		}
	}
	if (isHuman)
	{
		cout << "Отрицательный массив: " << endl;
	}
	printarrays(negarray);
	if (isHuman)
	{
		cout << "Положительный массив: " << endl;
	}
	printarrays(posarray);
	return 0;
}