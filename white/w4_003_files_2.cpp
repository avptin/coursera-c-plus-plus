// https://www.coursera.org/learn/c-plus-plus-white/programming/NZTXy/rabota-s-failami

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main()
{
    string line;
    ifstream input("input.txt");
    ofstream output("output.txt");

    if (input.is_open())
    {
        while (getline(input, line))
        {
            output << line << endl;
        }
    }
    return 0;
}
