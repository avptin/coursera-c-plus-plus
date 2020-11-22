#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator<<(ostream& os, const vector<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class T>
ostream& operator<<(ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream& operator<<(ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template <class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
      os << " hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}

void Assert(bool b, const string& hint) { AssertEqual(b, true, hint); }

class TestRunner {
 public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (exception& e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    } catch (...) {
      ++fail_count;
      cerr << "Unknown exception caught" << endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

 private:
  int fail_count = 0;
};

/*
// 4x^2 + 3 = 0
// a = 4, b = 0, c = 3
int GetDistinctRealRootCount(double A, double B, double C) {
  // найдём дискриминант
  double D = B * B - 4 * A * C;
  int result = 0;

  // если A равно нулю, то уравнение линейное: Bx + C = 0
  if (A == 0) {
    // Bx = -C => x = -C / B
    if (B != 0) {
      // cout << -C / B << endl;
      result = 1;
    }
    // если B равно нулю, корней нет

  } else if (D == 0) {  // случай с нулевым дискриминантом

    // корень ровно один
    // cout << -B / (2 * A) << endl;
    result = 1;

  } else if (D > 0) {  // в случае с положительным дискриминантом корня два

    double r1 = (-B + sqrt(D)) / (2 * A);
    double r2 = (-B - sqrt(D)) / (2 * A);

    // cout << r1 << " " << r2 << endl;
    result = (r1 != r2) ? 2 : 1;
  }

  return result;
}
*/

void TestFunction(void) {
  // double D = B * B - 4 * A * C;
  // D = 0
  AssertEqual(GetDistinctRealRootCount(2, 4, 2), 1,
              "a = 2, b = 4, where c = 2 has 1 real root(s).");
  AssertEqual(GetDistinctRealRootCount(-2, 4, -2), 1,
              "a = -2, b = 4, where c = -2 has 1 real root(s).");

  // D < 0
  AssertEqual(GetDistinctRealRootCount(4, 2, 2), 0,
              "a = 4, b = 2, where c = 2 has 0 real root(s).");

  // D > 0
  AssertEqual(GetDistinctRealRootCount(4, 1, 0), 2,
              "a = 4, b = 1, where c = 0 has 2 real root(s).");
  AssertEqual(GetDistinctRealRootCount(4, 4, 0), 2,
              "a = 4, b = 4, where c = 0 has 2 real root(s).");

  AssertEqual(GetDistinctRealRootCount(0, 2, 1), 1,
              "a = 0, b = 2, where c = 1 has 1 real root(s).");
  AssertEqual(GetDistinctRealRootCount(0, 2, 10000), 1,
              "a = 0, b = 2, where c = 10000 has 1 real root(s).");

  AssertEqual(GetDistinctRealRootCount(4, 0, 3), 0,
              "a = 4, b = 0, where c = 3 has 0 real root(s).");
  AssertEqual(GetDistinctRealRootCount(-4, 0, 36), 2,
              "a = -4, b = 0, where c = 36 has 2 real root(s).");
  AssertEqual(GetDistinctRealRootCount(-4, 0, -36), 0,
              "a = -4, b = 0, where c = -36 has 0 real root(s).");

  AssertEqual(GetDistinctRealRootCount(0, 0, 1), 0,
              "a = 0, b = 0, where c = 1 has 0 real roots.");
  AssertEqual(GetDistinctRealRootCount(0, 0, -10), 0,
              "a = 0, b = 0, where c = -10 has 0 real roots.");
  AssertEqual(GetDistinctRealRootCount(0, 0, 189238910), 0,
              "a = 0, b = 0, where c = 189238910 has 0 real roots.");
}

int main() {
  TestRunner runner;
  runner.RunTest(TestFunction, "TestFunction");
  return 0;
}
