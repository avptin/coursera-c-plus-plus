#include <iostream>
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

int main()
{
    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a * b;
        bool equal = c == Rational(8, 9);
        if (!equal)
        {
            cout << "2/3 * 4/3 != 8/9" << endl;
            return 1;
        }
    }

    {
        Rational a(5, 4);
        Rational b(15, 8);
        Rational c = a / b;
        bool equal = c == Rational(2, 3);
        if (!equal)
        {
            cout << "5/4 / 15/8 != 2/3" << endl;
            return 2;
        }
    }

    cout << "OK" << endl;
    return 0;
}