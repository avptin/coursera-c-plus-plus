// https://www.coursera.org/learn/c-plus-plus-white/programming/4FQn4/imiena-i-familii-1

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

class Person
{
public:
    void ChangeFirstName(int year, const string &first_name)
    {
        first[year] = first_name;
    }

    void ChangeLastName(int year, const string &last_name)
    {
        last[year] = last_name;
    }

    string GetFullName(int year)
    {
        string result;
        string name, surname;
        int key;

        for (auto &key : first)
        {
            if (year >= key.first)
            {
                name = first[key.first];
            }
        }

        for (auto &key : last)
        {
            if (year >= key.first)
            {
                surname = last[key.first];
            }
        }

        if (name.empty() && surname.empty())
        {
            result = "Incognito";
        }
        else if (name.empty())
        {
            result = surname + " with unknown first name";
        }
        else if (surname.empty())
        {
            result = name + " with unknown last name";
        }
        else
        {
            result = name + " " + surname;
        }

        return result;
    }

    string GetFullNameWithHistory(int year)
    {
        string r;
        int fy;
        int sy;

        fy = GetRecentYear(first, year);
        sy = GetRecentYear(last, year);

        if ((fy == -1) && (sy == -1))
        {
            r = "Incognito";
        }
        else if (fy == -1)
        {
            r = GetFullList(last, sy) + " with unknown first name";
        }
        else if (sy == -1)
        {
            r = GetFullList(first, fy) + " with unknown last name";
        }
        else
        {
            r = GetFullList(first, fy) + " " + GetFullList(last, sy);
        }

        return r;
    }

private:
    map<int, string> first;
    map<int, string> last;

    int GetRecentYear(map<int, string> el, int year)
    {
        int result = -1;

        for (auto &key : el)
        {
            if (year >= key.first)
            {
                result = key.first;
            }
        }

        return result;
    }

    string GetFullList(map<int, string> el, int year)
    {
        bool fall = false;
        string result;
        bool open = false;
        bool opened = false;
        string prev;

        for (auto it = el.rbegin(); it != el.rend(); it++)
        {
            if ((year == it->first) || (fall))
            {
                fall = true;
                if ((prev != el[it->first]) || prev.empty())
                {
                    if (open && !opened)
                    {
                        result += "(";
                        opened = true;
                    }

                    result += el[it->first] + " ";
                    prev = el[it->first];

                    if (opened)
                    {
                        result = result.substr(0, result.size() - 1);
                        result += ", ";
                    }

                    open = true;
                }
            }
        }
        fall = false;

        if (opened)
        {
            result = result.substr(0, result.size() - 2);
            result += ") ";
        }

        result.erase(find_if(result.rbegin(), result.rend(), [](int ch) {
                         return !isspace(ch);
                     }).base(),
                     result.end());

        return result;
    }
};

int main()
{
    Person person;

    person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1967, "Sergeeva");
    for (int year : {1900, 1965, 1990})
    {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeFirstName(1970, "Appolinaria");
    for (int year : {1969, 1970})
    {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeLastName(1968, "Volkova");
    for (int year : {1969, 1970})
    {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeFirstName(1990, "Polina");
    person.ChangeLastName(1990, "Volkova-Sergeeva");
    cout << person.GetFullNameWithHistory(1990) << endl;

    person.ChangeFirstName(1966, "Pauline");
    cout << person.GetFullNameWithHistory(1966) << endl;

    person.ChangeLastName(1960, "Sergeeva");
    for (int year : {1960, 1967})
    {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeLastName(1961, "Ivanova");
    cout << person.GetFullNameWithHistory(1967) << endl;

    return 0;
}
