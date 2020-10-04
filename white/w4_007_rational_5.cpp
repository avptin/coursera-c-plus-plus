#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

int gcd(int a, int b)
{
    // пока оба числа положительны, будем их уменьшать, не меняя их НОД
    while (a > 0 && b > 0)
    {
        // возьмём большее из чисел и заменим его остатком от деления на второе
        // действительно, если a и b делятся на x, то a - b и b делятся на x
        // тогда и a % b и b делятся на x, так что можно a заменить на a % b
        if (a > b)
        {
            a %= b;
        }
        else
        {
            b %= a;
        }
    }

    // если одно из чисел оказалось равно нулю, значит, на последней итерации
    // большее число разделилось на меньшее
    return a + b;
}

int lcm(int a, int b)
{
    return (a / gcd(a, b)) * b;
}

class Rational
{
public:
    Rational()
    {
        num = 0;
        den = 1;
    }

    Rational(int numerator, int denominator)
    {
        // При конструировании объека класса Rational с параметрами p и q должно
        // выполняться сокращение дроби p / q(здесь вам может пригодиться решение
        // задачи «Наибольший общий делитель»).
        num = numerator / gcd(numerator, denominator);
        den = denominator / gcd(numerator, denominator);

        // Если числитель дроби равен нулю, то знаменатель должен быть равен 1.
        den = (num == 0) ? 1 : den;

        // Если дробь p / q отрицательная, то объект Rational(p, q) должен иметь
        // отрицательный числитель и положительный знаменатель.

        // Если дробь p/q положительная, то объект Rational(p, q) должен иметь
        // положительные числитель и знаменатель (обратите внимание на случай Rational(-2, -3)).
        if (den < 0)
        {
            num *= -1;
            den *= -1;
        }
    }

    int Numerator() const
    {
        return num;
    }

    int Denominator() const
    {
        return den;
    }

    friend bool operator==(const Rational &lhs, const Rational &rhs);
    friend ostream &operator<<(ostream &os, const Rational &rtnl);
    friend istream &operator>>(istream &is, const Rational &rtnl);
    friend bool operator<(const Rational &lhs, const Rational &rhs);
    friend Rational operator+(const Rational &lhs, const Rational &rhs);
    friend Rational operator-(const Rational &lhs, const Rational &rhs);
    friend Rational operator*(const Rational &lhs, const Rational &rhs);
    friend Rational operator/(const Rational &lhs, const Rational &rhs);

private:
    int num;
    int den;
};

Rational operator+(const Rational &lhs, const Rational &rhs)
{
    return Rational(lhs.num * (lcm(lhs.den, rhs.den) / lhs.den) + rhs.num * (lcm(lhs.den, rhs.den) / rhs.den), lcm(lhs.den, rhs.den));
}

Rational operator-(const Rational &lhs, const Rational &rhs)
{
    return Rational(lhs.num * (lcm(lhs.den, rhs.den) / lhs.den) - rhs.num * (lcm(lhs.den, rhs.den) / rhs.den), lcm(lhs.den, rhs.den));
}

Rational operator*(const Rational &lhs, const Rational &rhs)
{
    return Rational(lhs.num * rhs.num, lhs.den * rhs.den);
}

Rational operator/(const Rational &lhs, const Rational &rhs)
{
    return Rational(lhs.num * rhs.den, lhs.den * rhs.num);
}

bool is_number(const std::string &s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it))
        ++it;
    return !s.empty() && it == s.end();
}

ostream &operator<<(ostream &os, const Rational &rtnl)
{
    os << rtnl.Numerator() << '/' << rtnl.Denominator();
    return os;
}

istream &operator>>(istream &is, Rational &rtnl)
{
    string elem;
    string num, den;

    is >> elem;
    stringstream ss(elem);
    getline(ss, num, '/');
    getline(ss, den, '/');

    if (is_number(num) && is_number(den))
    {
        rtnl = Rational(stod(num), stod(den));
    }

    return is;
}

bool operator==(const Rational &lhs, const Rational &rhs)
{
    return ((lhs.Denominator() == rhs.Denominator()) && (lhs.Numerator() == rhs.Numerator())) ? true : false;
}

bool operator<(const Rational &lhs, const Rational &rhs)
{
    int num_lhs, num_rhs;

    num_lhs = lhs.Numerator() * (lcm(lhs.Denominator(), rhs.Denominator()) / lhs.Denominator());
    num_rhs = rhs.Numerator() * (lcm(lhs.Denominator(), rhs.Denominator()) / rhs.Denominator());

    if (num_lhs < num_rhs)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Реализуйте для класса Rational оператор(ы), необходимые для использования его
// в качестве ключа map'а и элемента set'а

int main()
{
    {
        Rational a(2, 3);
        Rational b(5, 7);

        if (a < b)
        {
            cout << "a < b" << endl;
        }
        else
        {
            cout << "a >= b" << endl;
        }
    }
    {
        const set<Rational> rs = {{1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2}};
        if (rs.size() != 3)
        {
            cout << "Wrong amount of items in the set" << endl;
            return 1;
        }

        vector<Rational> v;
        for (auto x : rs)
        {
            v.push_back(x);
        }
        if (v != vector<Rational>{{1, 25}, {1, 2}, {3, 4}})
        {
            cout << "Rationals comparison works incorrectly" << endl;
            return 2;
        }
    }

    {
        map<Rational, int> count;
        ++count[{1, 2}];
        ++count[{1, 2}];

        ++count[{2, 3}];

        if (count.size() != 2)
        {
            cout << "Wrong amount of items in the map" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}
