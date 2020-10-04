// https://www.coursera.org/learn/c-plus-plus-white/programming/ndSVY/vyvod-s-tochnost-iu

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

int main()
{
    string line;
    ifstream input("input.txt");

    if (input.is_open())
    {
        cout << fixed << setprecision(3);
        while (getline(input, line))
        {
            cout << stod(line) << endl;
        }
    }

    return 0;
}
