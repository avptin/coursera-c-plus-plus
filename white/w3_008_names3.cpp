// https://www.coursera.org/learn/c-plus-plus-white/programming/4FQn4/imiena-i-familii-1

#include <algorithm>
#include <map>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Incognizable
{
public:
    Incognizable() {}
    Incognizable(int a){i = a;}
    Incognizable(int a, int b){i = a + b;}

private:
    int i;
};

int main()
{
    Incognizable a;
    Incognizable b = {};
    Incognizable c = {0};
    Incognizable d = {0, 1};
    return 0;
}