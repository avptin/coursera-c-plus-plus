// https://www.coursera.org/learn/c-plus-plus-yellow/programming/AhGVS/gruppirovka-strok-po-priefiksu

#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin,
                                        RandomIt range_end, char prefix) {
  auto f = lower_bound(
      range_begin, range_end, string(1, prefix),
      [](const string &lhs, const string &rhs) { return rhs[0] > lhs[0]; });
  auto s = upper_bound(
      range_begin, range_end, string(1, prefix),
      [](const string &lhs, const string &rhs) { return rhs[0] > lhs[0]; });

  return make_pair(f, s);
}

int main() {
  const vector<string> sorted_strings = {"moscow", "murmansk", "vologda"};

  const auto m_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), 'm');
  for (auto it = m_result.first; it != m_result.second; ++it) {
    cout << *it << " ";
  }
  cout << endl;

  const auto p_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), 'p');
  cout << (p_result.first - begin(sorted_strings)) << " "
       << (p_result.second - begin(sorted_strings)) << endl;

  const auto z_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), 'z');
  cout << (z_result.first - begin(sorted_strings)) << " "
       << (z_result.second - begin(sorted_strings)) << endl;

  return 0;
}
