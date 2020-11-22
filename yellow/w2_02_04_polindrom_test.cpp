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

// bool IsPalindrom(const string& str) {
// Вы можете вставлять сюда различные реализации функции,
// чтобы проверить, что ваши тесты пропускают корректный код
// и ловят некорректный
//}

void TestFunction(void) {
  AssertEqual(IsPalindrom("madam"), true, "madam");
  AssertEqual(IsPalindrom("MadaM"), true, "MadaM");
  AssertEqual(IsPalindrom("MaddaM"), true, "MaddaM");
  AssertEqual(IsPalindrom("level"), true, "level");
  AssertEqual(IsPalindrom("77777"), true, "77777");
  AssertEqual(IsPalindrom("777777"), true, "777777");
  AssertEqual(IsPalindrom("wasitacaroracatisaw"), true, "wasitacaroracatisaw");
  AssertEqual(IsPalindrom(""), true, "Empty string");
  AssertEqual(IsPalindrom("a"), true, "Single symbol");
  AssertEqual(IsPalindrom(""), true, "Empty string");
  AssertEqual(IsPalindrom("m ada m"), true, "Whitespace");
  AssertEqual(IsPalindrom("m  ada  m"), true, "Whitespace");
  AssertEqual(IsPalindrom("  "), true, "2 Whitespaces");
  AssertEqual(IsPalindrom("mam"), true, "mam");
  AssertEqual(IsPalindrom("maam"), true, "maam");

  AssertEqual(IsPalindrom("madax"), false, "madax");
  AssertEqual(IsPalindrom("wasitacaxoracatisaw"), false, "wasitacaxoracatisaw");
  AssertEqual(IsPalindrom("xadam"), false, "xadam");
  AssertEqual(IsPalindrom("Hello"), false, "Hello");
  AssertEqual(IsPalindrom("Hello"), false, "Hello1");
  AssertEqual(IsPalindrom("Hello "), false, "Hello_");
  AssertEqual(IsPalindrom("mad am"), false, "mad am");
  AssertEqual(IsPalindrom("masdam"), false, "masdam");
  // AssertEqual(IsPalindrom("77777"), false, "77778");
  // AssertEqual(IsPalindrom("777777"), false, "777778");
  AssertEqual(IsPalindrom("Madam"), false, "Madam");
  AssertEqual(IsPalindrom("adaM"), false, "madaM");
  AssertEqual(IsPalindrom("  ada "), false, "  ada ");
}

int main() {
  TestRunner runner;
  runner.RunTest(TestFunction, "TestFunction");
  return 0;
}
