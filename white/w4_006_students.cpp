// https://www.coursera.org/learn/c-plus-plus-white/programming/ndSVY/vyvod-s-tochnost-iu

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

struct Student
{
    string name;
    string surname;
    int day;
    int month;
    int year;
};

/*
    Далее идут N строк, каждая из которых содержит две строки длиной от 1 до 15 символов — имя и фамилию
    очередного студента, и три целых числа от 0 до 1000000000 — день, месяц и год рождения.
*/
bool CheckDbInput(const Student &std)
{
    bool result = true;

    if ((std.name.size() < 1) || ((std.name.size() > 15)))
    {
        result = false;
    }

    if ((std.day < 0) || (std.month < 0) || (std.year < 0))
    {
        result = false;
    }

    if ((std.day > 1000000000) || (std.month > 1000000000) || (std.year > 1000000000))
    {
        result = false;
    }

    return result;
}

bool CheckReqInput(const string &request, const int &std_num)
{
    bool result = true;

    if ((request.size() < 1) || ((request.size() > 15)))
    {
        result = false;
    }

    if ((std_num < 0) || (std_num > 1000000000))
    {
        result = false;
    }

    return result;
}

string GetSurname(const int &n, const vector<Student> &db)
{
    string surname = "bad request";

    if ((n - 1 < db.size()) && (n > 0))
    {
        surname = db[n - 1].name + " " + db[n - 1].surname;
    }
    return surname;
}

string GetDate(const int &n, const vector<Student> &db)
{
    string date = "bad request";

    if ((n - 1 < db.size()) && (n > 0))
    {
        date = to_string(db[n - 1].day) + "." + to_string(db[n - 1].month) + "." + to_string(db[n - 1].year);
    }

    return date;
}

bool is_number(const std::string &s)
{
    return !s.empty() && all_of(s.begin(), s.end(), ::isdigit);
}

int main()
{
    vector<Student> db;
    string db_size;
    string req_num;
    string line;
    Student new_student;

    /*
        1. Первая строка содержит одно целое число N от 0 до 10000 — число
        студентов
    */
    do
    {
        cin >> db_size;
    } while ((stod(db_size) < 0) || (stod(db_size) > 10000));

    /*
        2. Далее идут N строк, каждая из которых содержит две строки длиной
        от 1 до 15 символов — имя и фамилию очередного студента, и три целых
        числа от 0 до 1000000000 — день, месяц и год рождения.
    */
    for (int i = 0; i < stod(db_size); i++)
    {
        cin >> new_student.name;
        cin >> new_student.surname;
        cin >> new_student.day;
        cin >> new_student.month;
        cin >> new_student.year;

        if (CheckDbInput(new_student))
        {
            db.push_back(new_student);
        }
    }

    /*
        3. Следующая строка содержит одно целое число M от 0 до 10000 — число запросов.
    */
    do
    {
        cin >> req_num;
        //is_number(req_num)
    } while ((stod(req_num) < 0) || (stod(req_num) > 10000));

    /*
        4. Следующие M строк содержат строку длиной от 1 до 15 символов — запрос,
        и целое число от 0 до 1000000000 — номер студента (нумерация начинается с 1).
    */
    for (int i = 0; i < stod(req_num); i++)
    {
        string request;
        string number;
        string result = "bad request";

        cin >> request;
        cin >> number;

        if (is_number(number))
        {
            if (CheckReqInput(request, stod(number)))
            {
                // Для запроса вида name K, где K от 1 до N,
                // выведите через пробел имя и фамилию K-го студента.
                if (request == "name")
                {
                    result = GetSurname(stod(number), db);
                }
                else if (request == "date")
                {
                    result = GetDate(stod(number), db);
                }
            }
        }
        cout << result << endl;
    }

    return 0;
}
