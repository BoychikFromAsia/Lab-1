#include <iostream>
#include <clocale>

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "RU");
    double x = 1;
    double y = 1;
    bool isHuman = false;
    if (argc <= 1 || strcmp(argv[1], "false") != 0)
    {
        isHuman = true;
    }
    while (x != 0 || y != 0)
    {
        if (isHuman)
        {
            std::cout << "Введите координаты: " << std::endl;
        }
        std::cin >> x;
        std::cin >> y;
        if (x == 0 && y == 0)
        {
            break;
        }
        if ((x <= 3 && x >= 0) & (y <= 4 && y >= 0))
        {
            double func = 0;
            func = -4.0 / 3 * x + 4;
            if (y <= func && y >= 0)
            {
                if (isHuman)
                {
                    std::cout << "Входит в координату" << std::endl;
                }
                else
                {
                    std::cout << "YES" << std::endl;
                }
            }
            else
            {
                if (isHuman)
                {
                    std::cout << "Не входит в координату" << std::endl;
                }
                else
                {
                    std::cout << "NO" << std::endl;
                }
            }
        }
        else
        {
            if (isHuman)
            {
                std::cout << "Не входит в координату" << std::endl;
            }
            else
            {
                std::cout << "NO" << std::endl;
            }
        }
    }
}