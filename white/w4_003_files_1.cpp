// https://www.coursera.org/learn/c-plus-plus-white/programming/NZTXy/rabota-s-failami

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main()
{
    string line;
    ifstream input("input.txt");

    if (input.is_open())
    {
        while (getline(input, line))
        {
            cout << line << endl;
        }
    }
    return 0;
}
