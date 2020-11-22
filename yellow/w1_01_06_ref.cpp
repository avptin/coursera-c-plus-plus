
// https://www.coursera.org/learn/c-plus-plus-yellow/programming/YQJs1/vsio-v-kvadrat

#include <iostream>
#include <map>
#include <stdexcept>
#include <string>

using namespace std;

template <typename K, typename V>
V& GetRefStrict(map<K, V>& m, const K& k) {
  if (m.count(k) == 0) {
    throw runtime_error("Runtime error");
  }

  return m.at(k);
}
/*
int main() {
  try {
    map<int, string> m = {{0, "value"}};
    string& item = GetRefStrict(m, 1);
    item = "newvalue";
    cout << m[0] << endl;  // выведет newvalue
  } catch (std::runtime_error& e) {
    cout << e.what();
  }
  return 0;
}
*/