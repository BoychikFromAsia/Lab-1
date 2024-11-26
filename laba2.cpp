#include <iostream>

int amount, i, input, min, k = 2, g, k1, k2, k3, max, a, b, divv, c;
float arif, sum;
int main(int argc, char* argv[])
{
	bool isHuman = false;
	if (argc <= 1 || strcmp(argv[1], "false") != 0)
		isHuman = true;
	if (isHuman) {
		setlocale(LC_ALL, "");
		std::wcout << L"Введите количетсво чиесел последовательности: ";
	}
	std::cin >> amount;
	for (i = 0;i < amount;i++)
	{
		if (i != amount)
		{
			if (isHuman)
			{
				std::wcout << i + 1 << L" Число " << ": ";
			}
		}
		std::cin >> input;
		if (input == 1)
			std::wcout << 1 << L" Число  не простое" << std::endl;
		else
		{
			while (input % k != 0)
				k++;
			if (input == k)
				std::wcout << input << L" - число простое " << std::endl;
			else
				std::wcout << input << L" - число не простое " << std::endl;
		}
		if (i == 0) {
			min = input;
		}
		sum += input;
		if (min > input)
		{
			min = input;
		}
		if (max < input)
		{
			max = input;
		}
		if (input % 5 == 0)
		{
			k1 += 1;
		}
		divv = input;
		while (divv % 2 == 0)
		{
			divv = divv / 2;
		}
		if (divv == 1)
		{
			k2 += 1;
		}
		a = b;
		b = c;
		c = input;
		if (g >= 2)
		{
			if ((a + b) < c)
			{
				k3++;
			}
		}
	}
	if (isHuman)
	{
		std::wcout << L"Среднее арифметическое введенных чисел:" << std::endl;
	}
	arif = round((sum / amount) * 100) / 100;
	std::cout << arif << std::endl;
	if (isHuman)
	{
		std::wcout << L"Разница между максимумом и минимумом:" << std::endl;
	}
	std::wcout << max - min << std::endl;
	if (isHuman)
	{
		std::wcout << L"Количество чисел, кратных числу 5:" << std::endl;
	}
	std::wcout << k1 << std::endl;
	if (isHuman)
	{
		std::wcout << L"Количество чисел, являющихся степенью двойки:" << std::endl;
	}
	std::wcout << k2 << std::endl;

	if (isHuman)
	{
		std::wcout << L"Количество чисел, превышающих сумму двух предшествующих членов последовательности:" << std::endl;
	}
	std::wcout << k3 << std::endl;
	return 0;
}