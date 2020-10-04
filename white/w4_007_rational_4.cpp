#include <iostream>
#include <sstream>
#include <string>

using namespace std;

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

    void Set(const int &new_num, const int &new_den)
    {
        Rational(new_num, new_den);
    }

    bool operator==(const Rational &rhs)
    {
        return ((this->den == rhs.den) && (this->num == rhs.num)) ? true : false;
    }

    Rational operator+(const Rational &rhs)
    {
        return Rational(this->num * (lcm(this->den, rhs.den) / this->den) + rhs.num * (lcm(this->den, rhs.den) / rhs.den), lcm(this->den, rhs.den));
    }

    Rational operator-(const Rational &rhs)
    {
        return Rational(this->num * (lcm(this->den, rhs.den) / this->den) - rhs.num * (lcm(this->den, rhs.den) / rhs.den), lcm(this->den, rhs.den));
    }

    Rational operator*(const Rational &rhs)
    {
        return Rational(this->num * rhs.num, this->den * rhs.den);
    }

    Rational operator/(const Rational &rhs)
    {
        return Rational(this->num * rhs.den, this->den * rhs.num);
    }

    friend ostream &operator<<(ostream &os, const Rational &rtnl);
    friend istream &operator>>(istream &is, const Rational &rtnl);

private:
    int num;
    int den;

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
};

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

int main()
{
    {
        ostringstream output;
        output << Rational(-6, 8);
        if (output.str() != "-3/4")
        {
            cout << "Rational(-6, 8) should be written as \"-3/4\"" << endl;
            return 1;
        }
    }

    {
        istringstream input("5/7");
        Rational r;
        input >> r;
        bool equal = r == Rational(5, 7);
        if (!equal)
        {
            cout << "5/7 is incorrectly read as " << r << endl;
            return 2;
        }
    }

    {
        istringstream input("");
        Rational r;
        bool correct = !(input >> r);
        if (!correct)
        {
            cout << "Read from empty stream works incorrectly" << endl;
            return 3;
        }
    }

    {
        istringstream input("5/7 10/8");
        Rational r1, r2;
        input >> r1 >> r2;
        bool correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct)
        {
            cout << "Multiple values are read incorrectly: " << r1 << " " << r2 << endl;
            return 4;
        }

        input >> r1;
        input >> r2;
        correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct)
        {
            cout << "Read from empty stream shouldn't change arguments: " << r1 << " " << r2 << endl;
            return 5;
        }
    }

    {
        istringstream input1("1*2"), input2("1/"), input3("/4");
        Rational r1, r2, r3;
        input1 >> r1;
        input2 >> r2;
        input3 >> r3;
        bool correct = r1 == Rational() && r2 == Rational() && r3 == Rational();
        if (!correct)
        {
            cout << "Reading of incorrectly formatted rationals shouldn't change arguments: "
                 << r1 << " " << r2 << " " << r3 << endl;

            return 6;
        }
    }

    cout << "OK" << endl;
    return 0;
}
