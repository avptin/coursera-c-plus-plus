// https://www.coursera.org/learn/c-plus-plus-white/programming/zzTXi/stroka

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

class ReversibleString
{
public:
    ReversibleString() {}
    ReversibleString(const string &str)
    {
        intString = str;
    }

    string Reverse()
    {
        reverse(intString.begin(), intString.end());
        return intString;
    }

    string ToString() const
    {
        return intString;
    }

private:
    string intString;
};

int main()
{
    ReversibleString s("live");
    s.Reverse();
    cout << s.ToString() << endl;

    s.Reverse();
    const ReversibleString &s_ref = s;
    string tmp = s_ref.ToString();
    cout << tmp << endl;

    ReversibleString empty;
    cout << '"' << empty.ToString() << '"' << endl;

    return 0;
}
