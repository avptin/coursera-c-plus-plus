// https://www.coursera.org/learn/c-plus-plus-white/programming/c3YTB/otsortirovannyie-stroki

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;


class SortedStrings {
public:
    void AddString(const string& s) {
    msg.push_back(s);
    }
    vector<string> GetSortedStrings() {
        sort(begin(msg), end(msg));
        return msg;
    }
private:
    vector<string> msg;
};


void PrintSortedStrings(SortedStrings& strings) {
    for (const string& s : strings.GetSortedStrings()) {
        cout << s << " ";
    }
    cout << endl;
}

int main() {
    SortedStrings strings;

    strings.AddString("first");
    strings.AddString("third");
    strings.AddString("second");
    PrintSortedStrings(strings);

    strings.AddString("second");
    PrintSortedStrings(strings);

    return 0;
}

