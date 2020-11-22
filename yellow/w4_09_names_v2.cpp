// https://www.coursera.org/learn/c-plus-plus-yellow/programming/ye10B/imiena-i-familii-4

#include <algorithm>
#include <iostream>
#include <map>

using namespace std;

class Person {
public:
    void ChangeFirstName(int year, const string& first_name) {
        fn[year] = first_name;
    }
    void ChangeLastName(int year, const string& last_name) {
        ln[year] = last_name;
    }

    string GetByYear(const map<int, string> m, int y) {
        auto itr = m.upper_bound(y);
        string r;

        if (itr != m.begin()) {
            r = (--itr)->second;
        }

        return r;
    }

    string GetFullName(int year) {
        string sfn = GetByYear(fn, year);
        string sln = GetByYear(ln, year);

        if ((sfn.empty()) && (sln.empty())){
            return "Incognito";
        } else if (sln.empty()) {
            return sfn + " with unknown last name";
        } else if (sfn.empty()){
            return sln + " with unknown first name";
        } else {
            return sfn + " " + sln;
        }
    }

private:
    map<int, string> fn;
    map<int, string> ln;
};

int main() {
    Person person;

    person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1967, "Sergeeva");
    for (int year : {1900, 1965, 1990}) {
        cout << person.GetFullName(year) << endl;
    }

    person.ChangeFirstName(1970, "Appolinaria");
    for (int year : {1969, 1970}) {
        cout << person.GetFullName(year) << endl;
    }

    person.ChangeLastName(1968, "Volkova");
    for (int year : {1969, 1970}) {
        cout << person.GetFullName(year) << endl;
    }

    return 0;
}