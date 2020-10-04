// https://www.coursera.org/learn/c-plus-plus-white/programming/PnvtW/struktura-lecturetitle

#include <iostream>
#include <string>

using namespace std;

struct Specialization
{
    string value;

    explicit Specialization(const string &new_specialization)
    {
        value = new_specialization;
    }
};

struct Course
{
    string value;

    explicit Course(const string &new_course)
    {
        value = new_course;
    }
};

struct Week
{
    string value;

    explicit Week(const string &new_week)
    {
        value = new_week;
    }
};

struct LectureTitle
{
    string specialization;
    string course;
    string week;

    LectureTitle(const Specialization &new_specialization, const Course &new_course, const Week &new_week)
    {
        specialization = new_specialization.value;
        course = new_course.value;
        week = new_week.value;
    }
};

int main()
{
    LectureTitle title(
        Specialization("C++"),
        Course("White belt"),
        Week("4th"));

    // Not okay
    //LectureTitle title("C++", "White belt", "4th");

    //LectureTitle title(string("C++"), string("White belt"), string("4th"));

    //LectureTitle title = {"C++", "White belt", "4th"};

    //LectureTitle title = {{"C++"}, {"White belt"}, {"4th"}};

    /*
    LectureTitle title(
        Course("White belt"),
        Specialization("C++"),
        Week("4th"));
*/
    /*
    LectureTitle title(
        Specialization("C++"),
        Week("4th"),
        Course("White belt"));
*/
    return 0;
}