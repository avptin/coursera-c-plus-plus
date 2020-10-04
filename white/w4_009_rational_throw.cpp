#include <exception>
#include <iostream>

using namespace std;

int gcd(int a, int b) {
  if (b == 0) {
    return a;
  } else {
    return gcd(b, a % b);
  }
}

class Rational {
 public:
  Rational() {
    num = 0;
    den = 1;
  }

  Rational(int numerator, int denominator) {
    if ((denominator == 0) || gcd(numerator, denominator) == 0) {
      throw invalid_argument("Denominator equals zero!");
    }

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
    // положительные числитель и знаменатель (обратите внимание на случай
    // Rational(-2, -3)).
    if (den < 0) {
      num *= -1;
      den *= -1;
    }
  }
  int Numerator() const { return num; }
  int Denominator() const { return den; }
  friend Rational operator/(const Rational &lhs, const Rational &rhs);

 private:
  int num;
  int den;
};

Rational operator/(const Rational &lhs, const Rational &rhs) {
  if (rhs.num == 0) {
    throw domain_error("No division by zero!");
  }

  return Rational(lhs.num * rhs.den, lhs.den * rhs.num);
}

int main() {
  try {
    Rational r(1, 0);
    cout << "Doesn't throw in case of zero denominator" << endl;
    // return 1;
  } catch (invalid_argument &) {
  }

  try {
    auto x = Rational(1, 2) / Rational(0, 1);
    cout << "Doesn't throw in case of division by zero" << endl;
    // return 2;
  } catch (domain_error &) {
  }

  cout << "OK" << endl;
  return 0;
}
