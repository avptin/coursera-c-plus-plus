// https://www.coursera.org/learn/c-plus-plus-white/programming/ndSVY/vyvod-s-tochnost-iu

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

int main()
{
    string line;
    int x, y, n;

    ifstream input("input.txt");

    if (input)
    {
        input >> x;
        input >> y;

        for (int i = 0; i < x; i++)
        {
            for (int j = 0; j < y; j++)
            {
                input >> n;
                cout << setfill(' ') << setw(10) << n;
                if (j == y - 1)
                {
                }
                else
                {
                    cout << ' ';
                }

                input.ignore();
            }

            if (i == x - 1)
            {
            }
            else
            {
                cout << endl;
            }
        }
    }

    return 0;
}
