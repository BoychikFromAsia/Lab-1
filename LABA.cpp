#include <iostream>
#include <clocale>
#include <cmath>

using namespace std;

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
    if (isHuman) {
        while ((x != 0 || y != 0))
        {
            cout << "Введите координаты х и у: " << endl;
            cin >> x;
            cin >> y;
            if (x <= 3 && x >= 0)
            {
                double y2 = 0;
                y2 = -4.0/ 3 * x + 4;
                if (y <= y2 && y >= 0) {
                    cout << "Входит в координату" << endl;
                }
                else {
                    cout << "Не входит в координату" << endl;
                }
            }
            else
            {
                cout << "Не входит в координату" << endl;
            }
        }
    }
    else {
        while ((x != 0 || y != 0))
        {
            cin >> x;
            cin >> y;
            if (x <= 3 && x >= 0)
            {
                double y2 = 0;
                y2 = -4.0/ 3 * x + 4;
                if (y <= y2 && y >= 0) {
                    cout << "YES" << endl;
                }
                else {
                    cout << "NO" << endl;
                }
            }
            else
            {
                cout << "NO" << endl;
            }
        }
    }
}
