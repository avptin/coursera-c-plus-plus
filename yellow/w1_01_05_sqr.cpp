
// https://www.coursera.org/learn/c-plus-plus-yellow/programming/YQJs1/vsio-v-kvadrat

#include <iostream>
#include <map>
#include <sstream>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

// Declaration
template <typename First, typename Second>
pair<First, Second> operator*(const pair<First, Second>& p1,
                              const pair<First, Second>& p2);

template <typename F>
vector<F> operator*(const vector<F>& lhs, const vector<F>& rhs);

template <typename K, typename V>
map<K, V> operator*(const map<K, V>& lhs, const map<K, V>& rhs);

// Definition
template <typename First, typename Second>
pair<First, Second> operator*(const pair<First, Second>& p1,
                              const pair<First, Second>& p2) {
  First f = p1.first * p2.first;
  Second s = p1.second * p2.second;
  return make_pair(f, s);
}

template <typename F>
vector<F> operator*(const vector<F>& lhs, const vector<F>& rhs) {
  vector<F> vr;
  for (size_t i = 0; i < lhs.size(); i++) {
    vr.push_back(lhs[i] * rhs[i]);
  }
  return vr;
}

template <typename K, typename V>
map<K, V> operator*(const map<K, V>& lhs, const map<K, V>& rhs) {
  map<K, V> mr;
  for (auto [k, v] : lhs) {
    mr[k] = lhs.at(k) * rhs.at(k);
  }
  return mr;
}

template <typename T>
T Sqr(T n) {
  return n * n;
}

/*
int main() {
  // Пример вызова функции
  vector<int> v = {1, 2, 3};
  cout << "vector:";
  for (int x : Sqr(v)) {
    cout << ' ' << x;
  }
  cout << endl;

  map<int, pair<int, int>> map_of_pairs = {{4, {2, 2}}, {7, {4, 3}}};
  cout << "map of pairs:" << endl;
  for (const auto& x : Sqr(map_of_pairs)) {
    cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
  }

  auto p = make_pair(5, 3);
  p = Sqr(p);
  cout << "Pair: " << p.first << ' ' << p.second << endl;
}
*/