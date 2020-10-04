#include <exception>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

using namespace std;

int gcd(int a, int b) {
  if (b == 0) {
    return a;
  } else {
    return gcd(b, a % b);
  }
}

int lcm(int a, int b) { return (a / gcd(a, b)) * b; }

class Rational {
 public:
  Rational() {
    num = 0;
    den = 1;
  }

  Rational(int numerator, int denominator) {
    if ((denominator == 0) || gcd(numerator, denominator) == 0) {
      throw invalid_argument("Invalid argument");
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

  friend Rational operator+(const Rational &lhs, const Rational &rhs);
  friend Rational operator-(const Rational &lhs, const Rational &rhs);
  friend Rational operator*(const Rational &lhs, const Rational &rhs);
  friend Rational operator/(const Rational &lhs, const Rational &rhs);

 private:
  int num;
  int den;
};

Rational operator/(const Rational &lhs, const Rational &rhs) {
  if (rhs.num == 0) {
    throw domain_error("Division by zero");
  }

  return Rational(lhs.num * rhs.den, lhs.den * rhs.num);
}

Rational operator+(const Rational &lhs, const Rational &rhs) {
  return Rational(lhs.num * (lcm(lhs.den, rhs.den) / lhs.den) +
                      rhs.num * (lcm(lhs.den, rhs.den) / rhs.den),
                  lcm(lhs.den, rhs.den));
}

Rational operator-(const Rational &lhs, const Rational &rhs) {
  return Rational(lhs.num * (lcm(lhs.den, rhs.den) / lhs.den) -
                      rhs.num * (lcm(lhs.den, rhs.den) / rhs.den),
                  lcm(lhs.den, rhs.den));
}

Rational operator*(const Rational &lhs, const Rational &rhs) {
  return Rational(lhs.num * rhs.num, lhs.den * rhs.den);
}

int main() {
  string s;
  Rational lhs, rhs;
  char op;
  int num, den;

  getline(cin, s);
  stringstream stream(s);

  try {
    stream >> num;

    if (stream.peek() != '/') {
      throw invalid_argument("Invalid argument");
    } else {
      stream.ignore(1);
    }

    stream >> den;

    // cout << "Input was: " << num << " / " << den << endl;
    lhs = Rational(num, den);

    // Skip whitespace(s)
    while (stream.peek() == ' ') {
      stream.ignore(1);
    }

    // Get operation
    stream.get(op);
    // cout << "Operation: " << op << endl;

    // Skip whitespace(s)
    while (stream.peek() == ' ') {
      stream.ignore(1);
    }

    stream >> num;
    if (stream.peek() != '/') {
      throw invalid_argument("Invalid argument");
    } else {
      stream.ignore(1);
    }
    stream >> den;

    // cout << "Input was: " << num << " / " << den << endl;
    rhs = Rational(num, den);

    if (op == '+') {
      lhs = lhs + rhs;
    } else if (op == '-') {
      lhs = lhs - rhs;
    } else if (op == '*') {
      lhs = lhs * rhs;
    } else {
      lhs = lhs / rhs;
    }

    cout << lhs.Numerator() << '/' << lhs.Denominator() << endl;

  } catch (exception &ex) {
    cout << ex.what() << endl;
  }
}
