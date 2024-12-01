#include <iostream>

using namespace std;
int amount, matter, i, j, divv, divv1, divv2, divv3, input, maxx, minn, a, b, c;
float summ, avg;
int main(int argc, char* argv[])
{
	bool isHuman = false;
	if (argc <= 1 || strcmp(argv[1], "false") != 0)
	{
		isHuman = true;
	}
	if (isHuman)
	{
		setlocale(LC_ALL, "");
		cout << "Введите количество чисел последовательности:" << endl;
	}
	cin >> amount;
	for (matter = 0; matter < amount; matter++)
	{
		if (isHuman)
		{
			cout << "Число "  << matter + 1 <<": " << endl;
		}
		cin >> input;
		if (matter == 0)
		{
			minn = input;
		}
		divv = 0;
		if (input % 2 != 0)
		{
			int sqr = sqrt(input);
			for (j = 3; j <= sqr; j += 2)
			{
				if (input % j == 0)
				{
					divv++;
					break;
				}
			}
		}
		else
		{
			divv++;
		}
		if (divv == 0 and input != 1 or input == 2)
		{
			if (isHuman)
			{
				cout << input << " - простое число" <<endl;
			}
			else
			{
				cout << input << endl;
			}
		}
		summ += input;
		if (minn > input)
		{
			minn = input;
		}
		if (maxx < input)
		{
			maxx = input;
		}
		if (input % 5 == 0)
		{
			divv1 += 1;
		}
		i = input;
		while (i % 2 == 0)
		{
			i = i / 2;
		}
		if (i == 1)
		{
			divv2 += 1;
		}
		a = b;
		b = c;
		c = input;
		if (matter >= 2)
		{
			if ((a + b) < c)
			{
				divv3++;
			}
		}
	}
	if (isHuman)
	{
		cout << "Cреднее арифметическое введенных чисел (с округленное до двух знаков после запятой):" << endl;
	}
	avg = round((summ / amount) * 100) / 100;
	cout << avg << endl;
	if (isHuman)
	{
		cout << "Разница между максимумом и минимумом : " << endl;
	}
	cout << maxx - minn <<endl;
	if (isHuman)
	{
		cout << "Количество чисел, кратных числу 5:" << endl;
	}
	cout << divv1 << endl;
	if (isHuman)
	{
		cout << "Количество чисел, являющихся степенью двойки:" <<endl;
	}
	cout << divv2 << endl;
	if (isHuman)
	{
		cout << "Количество чисел, превышающих сумму двух предшествующих членов последовательности:" << endl;
	}
	cout << divv3 << endl;
	if (isHuman)
	{
		system("pause");
	}
	return 0;
}