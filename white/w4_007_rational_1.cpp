// https://www.coursera.org/learn/c-plus-plus-white/programming/pZwQ4/klass-rational

#include <cstdlib>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

bool is_number(const std::string &s) {
  std::string::const_iterator it = s.begin();
  while ((it != s.end() && std::isdigit(*it)) || (*it == '-')) ++it;
  return !s.empty() && it == s.end();
}

int gcd(int a, int b) {
  int abs_a, abs_b;

  abs_a = abs(a);
  abs_b = abs(b);

  // пока оба числа положительны, будем их уменьшать, не меняя их НОД
  while (abs_a > 0 && abs_b > 0) {
    // возьмём большее из чисел и заменим его остатком от деления на второе
    // действительно, если a и b делятся на x, то a - b и b делятся на x
    // тогда и a % b и b делятся на x, так что можно a заменить на a % b
    if (abs_a > abs_b) {
      abs_a %= abs_b;
    } else {
      abs_b %= abs_a;
    }
  }

  // если одно из чисел оказалось равно нулю, значит, на последней итерации
  // большее число разделилось на меньшее
  return abs_a + abs_b;
}

int lcm(int a, int b) { return (abs(a) / gcd(abs(a), abs(b))) * abs(b); }

class Rational {
 public:
  Rational() {
    num = 0;
    den = 1;
  }

  Rational(int numerator, int denominator) {
    // При конструировании объека класса Rational с параметрами p и q должно
    // выполняться сокращение дроби p / q(здесь вам может пригодиться решение
    // задачи «Наибольший общий делитель»).
    num = numerator / gcd(abs(numerator), abs(denominator));
    den = denominator / gcd(abs(numerator), abs(denominator));

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

  friend bool operator==(const Rational &lhs, const Rational &rhs);
  friend bool operator!=(const Rational &lhs, const Rational &rhs);
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

Rational operator/(const Rational &lhs, const Rational &rhs) {
  return Rational(lhs.num * rhs.den, lhs.den * rhs.num);
}

ostream &operator<<(ostream &os, const Rational &rtnl) {
  os << rtnl.Numerator() << '/' << rtnl.Denominator();
  return os;
}

istream &operator>>(istream &is, Rational &rtnl) {
  string elem;
  string num, den;

  is >> elem;
  stringstream ss(elem);
  getline(ss, num, '/');
  getline(ss, den, '/');

  if (is_number(num) && is_number(den)) {
    rtnl = Rational(stod(num), stod(den));
  }

  return is;
}

bool operator==(const Rational &lhs, const Rational &rhs) {
  return ((lhs.Denominator() == rhs.Denominator()) &&
          (lhs.Numerator() == rhs.Numerator()))
             ? true
             : false;
}

bool operator!=(const Rational &lhs, const Rational &rhs) {
  return ((lhs.Denominator() != rhs.Denominator()) &&
          (lhs.Numerator() != rhs.Numerator()))
             ? true
             : false;
}

bool operator<(const Rational &lhs, const Rational &rhs) {
  int num_lhs, num_rhs;

  num_lhs = lhs.Numerator() *
            (lcm(lhs.Denominator(), rhs.Denominator()) / lhs.Denominator());
  num_rhs = rhs.Numerator() *
            (lcm(lhs.Denominator(), rhs.Denominator()) / rhs.Denominator());

  if (num_lhs < num_rhs) {
    return true;
  } else {
    return false;
  }
}

int main() {
  {
    const Rational r(3, 10);
    if (r.Numerator() != 3 || r.Denominator() != 10) {
      cout << "Rational(3, 10) != 3/10" << endl;
      return 1;
    }
  }

  {
    const Rational r(8, 12);
    if (r.Numerator() != 2 || r.Denominator() != 3) {
      cout << "Rational(8, 12) != 2/3" << endl;
      return 2;
    }
  }

  {
    const Rational r(-4, 6);
    if (r.Numerator() != -2 || r.Denominator() != 3) {
      cout << "Rational(-4, 6) != -2/3" << endl;
      return 3;
    }
  }

  {
    const Rational r(-4, -6);
    if (r.Numerator() != 2 || r.Denominator() != 3) {
      cout << "Rational(-4, -6) != 2/3" << endl;
      return 3;
    }
  }

  {
    const Rational r(4, -6);
    if (r.Numerator() != -2 || r.Denominator() != 3) {
      cout << "Rational(4, -6) != -2/3" << endl;
      return 3;
    }
  }

  {
    const Rational r(0, 15);
    if (r.Numerator() != 0 || r.Denominator() != 1) {
      cout << "Rational(0, 15) != 0/1" << endl;
      return 4;
    }
  }

  {
    const Rational defaultConstructed;
    if (defaultConstructed.Numerator() != 0 ||
        defaultConstructed.Denominator() != 1) {
      cout << "Rational() != 0/1" << endl;
      return 5;
    }
  }

  {
    istringstream input("5f/7");
    Rational r;
    input >> r;
    bool equal = r == Rational(5, 7);
    if (equal) {
      cout << "5f/7 is incorrectly read as " << r << endl;
      return 2;
    }
  }

  {
    ostringstream output;
    output << Rational(-6, 8);
    if (output.str() != "-3/4") {
      cout << "Rational(-6, 8) should be written as \"-3/4\"" << endl;
      return 1;
    }
  }

  {
    istringstream input("5/7");
    Rational r;
    input >> r;
    bool equal = r == Rational(5, 7);
    if (!equal) {
      cout << "5/7 is incorrectly read as " << r << endl;
      return 2;
    }
  }

  {
    istringstream input("");
    Rational r;
    bool correct = !(input >> r);
    if (!correct) {
      cout << "Read from empty stream works incorrectly" << endl;
      return 3;
    }
  }

  {
    istringstream input("5/7 10/8");
    Rational r1, r2;
    input >> r1 >> r2;
    bool correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
    if (!correct) {
      cout << "Multiple values are read incorrectly: " << r1 << " " << r2
           << endl;
      return 4;
    }

    input >> r1;
    input >> r2;
    correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
    if (!correct) {
      cout << "Read from empty stream shouldn't change arguments: " << r1 << " "
           << r2 << endl;
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
    if (!correct) {
      cout << "Reading of incorrectly formatted rationals shouldn't change "
              "arguments: "
           << r1 << " " << r2 << " " << r3 << endl;

      return 6;
    }
  }

  {
    istringstream input("5/-5 2/3");
    Rational r1, r2;
    input >> r1 >> r2;
    bool correct = r1 == Rational(-5, 5) && r2 == Rational(2, 3);
    if (!correct) {
      cout << "Multiple values are read incorrectly: " << r1 << " " << r2
           << endl;
      return 4;
    }
  }

  cout << "OK" << endl;
  return 0;
}
